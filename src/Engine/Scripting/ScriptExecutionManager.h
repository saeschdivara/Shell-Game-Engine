#pragma once

#ifndef SHELL_PLATFORM_WINDOWS
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

namespace Shell {

    class ScriptExecutionManager {
    public:
        void simpleExecute();
    };

}
#endif