#include "ScriptExecutionManager.h"

#ifndef SHELL_PLATFORM_WINDOWS
#include "Engine/Core/Logger.h"

#include <mono/jit/jit.h>
#include <mono/metadata/object.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>

// Expose function to mono runtime
extern "C"
{
    void DoSomething() {
        SHELL_CORE_INFO("DoSomething is called");
    }
}


namespace Shell {

    void ScriptExecutionManager::simpleExecute() {
        MonoDomain *domain = mono_jit_init_version("myapp", "v4.0.30319");

        MonoAssembly * assembly = mono_domain_assembly_open(domain, "../game-data/SandboxApp.dll");

        if (!assembly) {
            SHELL_CORE_ERROR("Could not open assembly");
            mono_jit_cleanup(domain);
            return;
        }

        MonoImage * image = mono_assembly_get_image(assembly);

        // needed to find mono libraries e.g. to print out to console
        mono_config_parse(NULL);

        MonoClass * class1 = mono_class_from_name (image, "SandboxApp", "Class1");

        MonoObject *classInstance = mono_object_new (domain, class1);
        mono_runtime_object_init (classInstance);

        MonoMethodDesc * methodDesc = mono_method_desc_new("SandboxApp.Class1:getSampleResult", true);

        MonoMethod * method = mono_method_desc_search_in_image(methodDesc, image);

        MonoObject * result = mono_runtime_invoke(method, classInstance, NULL, NULL);
        MonoString  * resultStr = mono_object_to_string(result, NULL);
        char* str = mono_string_to_utf8(resultStr);
        SHELL_CORE_INFO("Result string: {0}", str);

        mono_jit_cleanup(domain);
    }
}
#endif