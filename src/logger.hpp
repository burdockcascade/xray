#pragma once
#include <spdlog/spdlog.h>
#include <memory>

class Log {
public:
    static void Init();
    static std::shared_ptr<spdlog::logger>& GetLogger();
    static void SetLevel(spdlog::level::level_enum level);

private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};

// Macros for ease of use
#define LOG_TRACE(...)    Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    Log::GetLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)     Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)     Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Log::GetLogger()->critical(__VA_ARGS__)