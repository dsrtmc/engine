#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace Engine
{
    class Log
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger> &GetLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
};

// Client log macros
#define ENG_TRACE(...) ::Engine::Log::GetLogger()->trace(__VA_ARGS__)
#define ENG_INFO(...) ::Engine::Log::GetLogger()->info(__VA_ARGS__)
#define ENG_WARN(...) ::Engine::Log::GetLogger()->warn(__VA_ARGS__)
#define ENG_ERROR(...) ::Engine::Log::GetLogger()->error(__VA_ARGS__)
#define ENG_FATAL(...) ::Engine::Log::GetLogger()->fatal(__VA_ARGS__)