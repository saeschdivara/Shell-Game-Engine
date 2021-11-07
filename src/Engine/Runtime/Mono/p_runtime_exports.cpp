// this file contains only c exports for the mono runtime
#include "p_runtime_exports.h"

#include "Engine/Core/Profiling.h"
#include "Engine/Runtime/RuntimeManager.h"
#include "Engine/Runtime/Mono/MonoRuntime.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

inline Shell::Runtime::Mono::MonoRuntime * ShellGetRuntime() {
    return dynamic_cast<Shell::Runtime::Mono::MonoRuntime *>(Shell::Runtime::RuntimeManager::Instance()->GetRuntime());
}

// Expose function to mono runtime
extern "C"
{
    MonoObject * GameObject_GetComponent(MonoObject * self, MonoString * monoClsNamespace, MonoString * monoCls) {
        OPTICK_EVENT(Optick::Category::Script)

        char* clsNamespace = mono_string_to_utf8(monoClsNamespace);
        char* cls = mono_string_to_utf8(monoCls);

#ifdef SHELL_CORE_DEBUG
        SHELL_CORE_INFO("GameObject_GetComponent is called {0}", (long)(self));
        SHELL_CORE_INFO("clsNamespace: {0}", clsNamespace);
        SHELL_CORE_INFO("cls: {0}", cls);
#endif

        auto * runtime = ShellGetRuntime();
        MonoObject * obj = runtime->CreateSimpleEngineObject(clsNamespace, cls);

        return obj;
    }
}

void Shell::Runtime::Mono::RegisterInternalCallbacks() {
    mono_add_internal_call("Shell.Core.GameObject::InternalGetComponent", (const void*) GameObject_GetComponent);
}

