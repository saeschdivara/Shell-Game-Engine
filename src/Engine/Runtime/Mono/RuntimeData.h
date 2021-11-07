#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>

namespace Shell::Runtime {

    struct EngineData {
        MonoClass * BehaviourClass;
        MonoClass * GameObjectClass;
    };

    struct RuntimeData {
        MonoDomain * Jit;
        MonoImage * EngineLibraryImage;
        MonoImage * AppLibraryImage;

        EngineData EngineData;
    };
}


