#include "MonoRuntime.h"

#include "Engine/Core/Profiling.h"

namespace Shell::Runtime::Mono {

    MonoRuntime::MonoRuntime(RuntimeData *data) : m_Data(data) {
    }

    MonoObject *MonoRuntime::CreateSimpleEngineObject(const char * clsNamespaceStr, const char * clsStr) {
        OPTICK_EVENT(Optick::Category::Script);

        MonoClass * cls = mono_class_from_name(m_Data->EngineLibraryImage, clsNamespaceStr, clsStr);
        SHELL_CORE_ASSERT(cls)

        MonoObject * obj = mono_object_new(m_Data->Jit, cls);
        mono_runtime_object_init(obj);

        return obj;
    }
}