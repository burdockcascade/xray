#include "logger.hpp"
#include <raylib.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Log::s_Logger;

void RaylibLogCallback(int logLevel, const char *text, va_list args) {
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), text, args);

    // Map Raylib levels to spdlog levels
    switch (logLevel) {
        case LOG_TRACE:   Log::GetLogger()->trace(buffer); break;
        case LOG_DEBUG:   Log::GetLogger()->debug(buffer); break;
        case LOG_INFO:    Log::GetLogger()->info(buffer); break;
        case LOG_WARNING: Log::GetLogger()->warn(buffer); break;
        case LOG_ERROR:   Log::GetLogger()->error(buffer); break;
        case LOG_FATAL:   Log::GetLogger()->critical(buffer); break;
        default:          Log::GetLogger()->info(buffer); break;
    }
}

void Log::Init() {
    // Set pattern: [Time] [Level] Message
    // %^ and %$ denote the start/end of color range
    spdlog::set_pattern("%^[%T] [%l] %v%$");

    s_Logger = spdlog::stdout_color_mt("APP");

    // DEFAULT: Only show Warnings and Errors
    s_Logger->set_level(spdlog::level::warn);

    // (Optional) If you integrated Raylib callback, set Raylib to Warning too
    SetTraceLogLevel(LOG_WARNING);

    SetTraceLogCallback(RaylibLogCallback);
}

void Log::SetLevel(spdlog::level::level_enum level) {
    if (s_Logger) {
        s_Logger->set_level(level);

        // Update Raylib's internal filter too
        if (level == spdlog::level::debug || level == spdlog::level::trace) {
            SetTraceLogLevel(LOG_INFO); // Raylib is noisy, INFO is usually enough for debug
        } else {
            SetTraceLogLevel(LOG_WARNING);
        }
    }
}

std::shared_ptr<spdlog::logger>& Log::GetLogger() {
    return s_Logger;
}