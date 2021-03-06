#include "RuntimeManager.h"

#include "Engine/Core/Profiling.h"
#include "Engine/Project/Entities/Components.h"
#include "Engine/Project/Entities/EntityManager.h"
#include "Engine/Project/Entities/SceneEntity.h"
#include "Engine/Runtime/Mono/helpers.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>

#define ENGINE_LIB_PATH "../engine/Shell-Engine.dll"

namespace Shell::Runtime {

    struct EngineData {
        MonoClass * BehaviourClass;
    };

    struct RuntimeData {
        MonoDomain * Jit;
        MonoImage * EngineLibraryImage;
        MonoImage * AppLibraryImage;

        EngineData EngineData;
    };

    Ref<RuntimeManager> RuntimeManager::m_Instance = nullptr;

    Ref <RuntimeManager> RuntimeManager::Instance() {

        if (!m_Instance) {
            m_Instance = Shell::CreateRef<RuntimeManager>();
        }

        return m_Instance;
    }

    RuntimeManager::RuntimeManager() : m_Data(new RuntimeData) {}

    RuntimeManager::~RuntimeManager() {
        // clean up engine parts
        mono_jit_cleanup(m_Data->Jit);

        // delete objects
        delete m_Data;
    }

    void RuntimeManager::Init() {
        OPTICK_EVENT();

        m_Data->Jit = mono_jit_init_version("app", "v4.0.30319");

        // needed to find mono libraries e.g. to print out to console
        mono_config_parse(NULL);
    }

    void RuntimeManager::LoadEngineLibrary() {
        OPTICK_EVENT();

        MonoAssembly * assembly = mono_domain_assembly_open(m_Data->Jit, ENGINE_LIB_PATH);

        if (!assembly) {
            SHELL_CORE_ERROR("Could not open engine library {0}", ENGINE_LIB_PATH);
            return;
        }

        m_Data->EngineLibraryImage = mono_assembly_get_image(assembly);

        // load extra data from loaded library
        m_Data->EngineData.BehaviourClass = mono_class_from_name(m_Data->EngineLibraryImage, "Shell.Core.Behaviours", "ShellBehaviour");
    }

    void RuntimeManager::LoadAppLibrary(const std::string & appLibraryPath) {
        OPTICK_EVENT();

        MonoAssembly * assembly = mono_domain_assembly_open(m_Data->Jit, appLibraryPath.c_str());

        if (!assembly) {
            SHELL_CORE_ERROR("Could not open app library {0}", appLibraryPath.c_str());
            return;
        }

        m_Data->AppLibraryImage = mono_assembly_get_image(assembly);
    }

    void RuntimeManager::InstantiateScene(Ref<SceneBlueprint> scene) {
        OPTICK_EVENT();
        RunLifecycleMethod(scene, "OnCreate");
    }

    void RuntimeManager::RunLifecycleMethod(Ref<SceneBlueprint> scene, const char *methodName) {
        OPTICK_EVENT();
        RunLifecycleMethod(scene->GetEntityTree(), methodName);
    }

    void RuntimeManager::RunLifecycleMethod(std::vector<SceneEntity *> &entities, const char *methodName) {
        for (const auto &entity: entities) {
            RunLifecycleMethod(entity, methodName);

            if (entity->HasChildren()) {
                RunLifecycleMethod(entity->GetChildren(), methodName);
            }
        }
    }

    void RuntimeManager::RunLifecycleMethod(SceneEntity *entity, const char *methodName) {
        OPTICK_EVENT();
        if (!EntityManager::Instance()->HasComponent<ScriptingComponent>(entity)) {
            return;
        }

        auto& scriptComponent = EntityManager::Instance()->GetComponent<ScriptingComponent>(entity);

        MonoClass * cls = mono_class_from_name(m_Data->AppLibraryImage, scriptComponent.Path.c_str(), scriptComponent.ClassName.c_str());

        if ( mono_class_is_subclass_of(cls, m_Data->EngineData.BehaviourClass, false) ) {

            if (!scriptComponent.RuntimeObj) {
                scriptComponent.RuntimeObj = mono_object_new(m_Data->Jit, cls);

                // call its default constructor
                mono_runtime_object_init(scriptComponent.RuntimeObj);
            }

            auto method = GetMethodInClassHierarchy(cls, methodName, 0);
            SHELL_CORE_ASSERT(method);

            auto virtualOnCreateMethod = mono_object_get_virtual_method(scriptComponent.RuntimeObj, method);

            mono_runtime_invoke(virtualOnCreateMethod, scriptComponent.RuntimeObj, nullptr, nullptr);
        }
    }
}