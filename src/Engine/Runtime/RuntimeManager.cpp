#include "RuntimeManager.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>

#define ENGINE_LIB_PATH "../engine/Shell-Engine.dll"

namespace Shell::Runtime {

    struct RuntimeData {
        MonoDomain * Jit;
        MonoImage * EngineLibraryImage;
        MonoImage * AppLibraryImage;
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
        m_Data->Jit = mono_jit_init_version("app", "v4.0.30319");

        // needed to find mono libraries e.g. to print out to console
        mono_config_parse(NULL);
    }

    void RuntimeManager::LoadEngineLibrary() {
        MonoAssembly * assembly = mono_domain_assembly_open(m_Data->Jit, ENGINE_LIB_PATH);

        if (!assembly) {
            SHELL_CORE_ERROR("Could not open engine library {0}", ENGINE_LIB_PATH);
            return;
        }

        m_Data->EngineLibraryImage = mono_assembly_get_image(assembly);
    }

    void RuntimeManager::LoadAppLibrary(const std::string & appLibraryPath) {
        MonoAssembly * assembly = mono_domain_assembly_open(m_Data->Jit, appLibraryPath.c_str());

        if (!assembly) {
            SHELL_CORE_ERROR("Could not open app library {0}", appLibraryPath.c_str());
            return;
        }

        m_Data->EngineLibraryImage = mono_assembly_get_image(assembly);
    }
}