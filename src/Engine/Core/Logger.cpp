#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Shell {

    std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Logger::s_AppLogger;

    void Logger::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("CORE");
        s_CoreLogger->set_level(spdlog::level::trace);
        s_AppLogger = spdlog::stdout_color_mt("APP");
        s_AppLogger->set_level(spdlog::level::trace);
    }
}