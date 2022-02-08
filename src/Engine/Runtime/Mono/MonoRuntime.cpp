#include "MonoRuntime.h"

#include "Engine/Core/Profiling.h"

namespace Shell::Runtime::Mono {

    MonoRuntime::MonoRuntime(RuntimeData *data) : m_Data(data) {
    }

    MonoObject *MonoRuntime::CreateSimpleEngineObject(const char * clsNamespaceStr, const char * clsStr) {
        OPTICK_EVENT(Optick::Category::Script)

        MonoClass * cls = mono_class_from_name(m_Data->EngineLibraryImage, clsNamespaceStr, clsStr);
        SHELL_CORE_ASSERT(cls)

        MonoObject * obj = mono_object_new(m_Data->Jit, cls);
        mono_runtime_object_init(obj);

        return obj;
    }

    MonoObject *MonoRuntime::CreateVec2(float x, float y) {
        OPTICK_EVENT(Optick::Category::Script)

        MonoClass * cls = mono_class_from_name(m_Data->EngineLibraryImage, "Shell.Core", "Vec2");
        SHELL_CORE_ASSERT(cls)

        MonoObject * obj = mono_object_new(m_Data->Jit, cls);

        MonoMethod * gameObjectConstructor = mono_class_get_method_from_name(cls, ".ctor", 2);

        void * constructorArguments[2];
        constructorArguments[0] = static_cast<void *>(&x);
        constructorArguments[1] = static_cast<void *>(&y);

        mono_runtime_invoke(gameObjectConstructor, obj, constructorArguments, nullptr);

        return obj;
    }

    MonoObject *MonoRuntime::GetObjectField(MonoObject *obj, const char *fieldName) {
        MonoClass * cls = mono_object_get_class(obj);
        MonoClassField  * field = mono_class_get_field_from_name(cls, fieldName);

        return mono_field_get_value_object(m_Data->Jit, field, obj);
    }

    void MonoRuntime::SetObjectField(MonoObject *obj, const char *fieldName, MonoObject *value) {
        MonoClass * cls = mono_object_get_class(obj);
        MonoClassField  * field = mono_class_get_field_from_name(cls, fieldName);

        mono_field_set_value(obj, field, value);
    }

    MonoObject *MonoRuntime::GetObjectProperty(MonoObject *obj, const char *propertyName) {
        MonoClass * cls = mono_object_get_class(obj);
        MonoProperty * property = mono_class_get_property_from_name(cls, propertyName);

        return mono_property_get_value(property, obj, nullptr, nullptr);
    }

    template<typename T>
    T MonoRuntime::GetSimpleObjectProperty(MonoObject *obj, const char *propertyName) {
        return *(T *) GetObjectProperty(obj, propertyName);
    }

    void MonoRuntime::SetObjectProperty(MonoObject *obj, const char *propertyName, MonoObject *value) {
        MonoClass * cls = mono_object_get_class(obj);
        MonoProperty * property = mono_class_get_property_from_name(cls, propertyName);

        void * args[1];
        args[0] = value;

        mono_property_set_value(property, obj, args, nullptr);
    }
}