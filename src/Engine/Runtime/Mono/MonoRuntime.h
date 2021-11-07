#pragma once

#include "Engine/Runtime/RuntimeManager.h"
#include "Engine/Runtime/Mono/RuntimeData.h"

namespace Shell::Runtime::Mono {

    class MonoRuntime : public Runtime {
    public:
        MonoRuntime(RuntimeData * data);

        MonoObject * CreateSimpleEngineObject(const char * clsNamespaceStr, const char * clsStr);

    private:
        RuntimeData * m_Data;
    };
}


