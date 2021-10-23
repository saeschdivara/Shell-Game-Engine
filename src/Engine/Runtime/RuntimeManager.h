#pragma once

#include "Engine/Core/shellpch.h"

namespace Shell::Runtime {

    struct RuntimeData;

    class RuntimeManager {
    public:
        static Ref<RuntimeManager> Instance();

        RuntimeManager();

        virtual ~RuntimeManager();

        void Init();
        void LoadEngineLibrary();

    private:
        static Ref<RuntimeManager> m_Instance;
        RuntimeData * m_Data;
    };
}
