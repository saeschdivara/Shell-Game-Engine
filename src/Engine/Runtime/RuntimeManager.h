#pragma once

#include "Engine/Core/shellpch.h"
#include "Engine/Project/SceneBlueprint.h"

namespace Shell {
    class SceneEntity;
}

namespace Shell::Runtime {

    struct RuntimeData;

    class RuntimeManager {
    public:
        static Ref<RuntimeManager> Instance();

        RuntimeManager();

        virtual ~RuntimeManager();

        void Init();
        void LoadEngineLibrary();
        void LoadAppLibrary(const std::string & appLibraryPath);

        void InstantiateScene(Ref<SceneBlueprint> scene);
        void RunLifecycleMethod(Ref<SceneBlueprint> scene, const char * methodName);

    private:
        void RunLifecycleMethod(std::vector<SceneEntity *> & entities, const char * methodName);
        void RunLifecycleMethod(SceneEntity * entity, const char * methodName);

    private:
        static Ref<RuntimeManager> m_Instance;
        RuntimeData * m_Data;
    };
}
