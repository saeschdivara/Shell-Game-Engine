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

    private:
        void InstantitateEntities(std::vector<SceneEntity *> & entities);
        void InstantitateEntity(SceneEntity * entity);

    private:
        static Ref<RuntimeManager> m_Instance;
        RuntimeData * m_Data;
    };
}
