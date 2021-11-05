#pragma once

#ifdef SHELL_PROFILING
    #include <optick.h>
#else
    #define OPTICK_START_CAPTURE
    #define OPTICK_STOP_CAPTURE
    #define OPTICK_SAVE_CAPTURE
    #define OPTICK_FRAME
#endif