#pragma once

#ifdef SHELL_PLATFORM_WINDOWS
    #ifdef _EXPORTING
    #define SHELL_API    __declspec(dllexport)
    #else
    #define SHELL_API    __declspec(dllimport)
    #endif
#else
    #define SHELL_API
#endif