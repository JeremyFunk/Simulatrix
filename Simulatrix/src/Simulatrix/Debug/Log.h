#pragma once

#include "Simulatrix/Core/Core.h"
#include "spdlog/spdlog.h"
namespace Simulatrix {
    class Log
    {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr < spdlog::logger> s_CoreLogger;
        static std::shared_ptr < spdlog::logger> s_ClientLogger;
         
    };
}

#define SIMIX_CORE_FATAL(...) ::Simulatrix::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define SIMIX_CORE_ERROR(...) ::Simulatrix::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SIMIX_CORE_WARN(...)  ::Simulatrix::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SIMIX_CORE_INFO(...)  ::Simulatrix::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SIMIX_CORE_TRACE(...) ::Simulatrix::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define SIMIX_FATAL(...)      ::Simulatrix::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define SIMIX_ERROR(...)      ::Simulatrix::Log::GetClientLogger()->error(__VA_ARGS__)
#define SIMIX_WARN(...)       ::Simulatrix::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SIMIX_INFO(...)       ::Simulatrix::Log::GetClientLogger()->info(__VA_ARGS__)
#define SIMIX_TRACE(...)      ::Simulatrix::Log::GetClientLogger()->trace(__VA_ARGS__)
