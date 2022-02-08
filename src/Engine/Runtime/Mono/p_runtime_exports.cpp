// this file contains only c exports for the mono runtime
#include "p_runtime_exports.h"

#include "Engine/Core/Profiling.h"
#include "Engine/Project/Entities/Components.h"
#include "Engine/Project/Entities/EntityManager.h"
#include "Engine/Runtime/RuntimeManager.h"
#include "Engine/Runtime/Mono/MonoRuntime.h"

#include <entt/entt.hpp>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

inline Shell::Runtime::Mono::MonoRuntime * ShellGetRuntime() {
    return dynamic_cast<Shell::Runtime::Mono::MonoRuntime *>(Shell::Runtime::RuntimeManager::Instance()->GetRuntime());
}

inline entt::entity ShellGetEntityFromGameObject(MonoObject * obj) {
    auto runtime = ShellGetRuntime();
    long entityId = *(long *)mono_object_unbox(runtime->GetObjectField(obj, "_internalId"));
    return Shell::EntityManager::Instance()->GetEntityFromValue(entityId);
}

// Expose function to mono runtime
extern "C"
{
    MonoObject * GameObject_GetComponent(MonoObject * self, MonoString * monoClsNamespace, MonoString * monoCls) {
        OPTICK_EVENT(Optick::Category::Script)

        char* clsNamespace = mono_string_to_utf8(monoClsNamespace);
        char* cls = mono_string_to_utf8(monoCls);

        auto * runtime = ShellGetRuntime();
        MonoObject * obj = runtime->CreateSimpleEngineObject(clsNamespace, cls);

        entt::entity entity = ShellGetEntityFromGameObject(self);
        auto entityManager = Shell::EntityManager::Instance();

        if (std::strcmp(cls, "TransformComponent") == 0 && entityManager->HasComponent<Shell::TransformComponent>(entity)) {
            auto cmp = entityManager->GetComponent<Shell::TransformComponent>(entity);

            MonoObject * translation = runtime->CreateVec2(cmp.Translation.x, cmp.Translation.y);
            runtime->SetObjectProperty(obj, "Translation", translation);

            MonoObject * rotation = runtime->CreateVec2(cmp.Rotation.x, cmp.Rotation.y);
            runtime->SetObjectProperty(obj, "Rotation", rotation);

            MonoObject * scale = runtime->CreateVec2(cmp.Scale.x, cmp.Scale.y);
            runtime->SetObjectProperty(obj, "Scale", scale);
        }

        return obj;
    }

    void ObjectManager_SetComponentValue(MonoObject * obj, MonoObject * component, MonoString * propertyNameObj, MonoObject * value) {
        auto * runtime = ShellGetRuntime();

        entt::entity entity = ShellGetEntityFromGameObject(obj);
        auto entityManager = Shell::EntityManager::Instance();

        MonoClass * componentCls = mono_object_get_class(component);
        const char * clsName = mono_class_get_name(componentCls);

        char* propertyName = mono_string_to_utf8(propertyNameObj);

        if (std::strcmp(clsName, "TransformComponent") == 0 && entityManager->HasComponent<Shell::TransformComponent>(entity)) {
            auto & cmp = entityManager->GetComponent<Shell::TransformComponent>(entity);

            if (std::strcmp(propertyName, "Translation") == 0) {
//                auto x = runtime->GetSimpleObjectProperty<float>(value, "X");
//                auto y = runtime->GetSimpleObjectProperty<float>(value, "Y");
//
//                cmp.Translation = glm::vec3(x, y, 0);
            }
        }
    }
}

void Shell::Runtime::Mono::RegisterInternalCallbacks() {
    mono_add_internal_call("Shell.Core.GameObject::InternalGetComponent", (const void*) GameObject_GetComponent);
    mono_add_internal_call("Shell.Core.ObjectManager::SetComponentValue", (const void*) ObjectManager_SetComponentValue);
}

