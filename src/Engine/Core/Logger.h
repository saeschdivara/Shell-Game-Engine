#pragma once

#include <spdlog/spdlog.h>

namespace Shell {
    class Logger {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_AppLogger;
    };
}

// core log macros
#define SHELL_CORE_ERROR(...) ::Shell::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define SHELL_CORE_WARN(...)  ::Shell::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define SHELL_CORE_INFO(...)  ::Shell::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define SHELL_CORE_DEBUG(...) ::Shell::Logger::GetCoreLogger()->debug(__VA_ARGS__)

// app log macros
#define SHELL_ERROR(...) ::Shell::Logger::GetAppLogger()->error(__VA_ARGS__)
#define SHELL_WARN(...)  ::Shell::Logger::GetAppLogger()->warn(__VA_ARGS__)
#define SHELL_INFO(...)  ::Shell::Logger::GetAppLogger()->info(__VA_ARGS__)
#define SHELL_DEBUG(...) ::Shell::Logger::GetAppLogger()->debug(__VA_ARGS__)

