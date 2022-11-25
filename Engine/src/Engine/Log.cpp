#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine
{
    std::shared_ptr<spdlog::logger> Log::s_Logger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[[%T] %n: %v%$");

        Log::s_Logger = spdlog::stdout_color_mt("ENGINE");
        Log::s_Logger->set_level(spdlog::level::trace);
    }

    std::shared_ptr<spdlog::logger> &Log::GetLogger()
    {
        if (!s_Logger)
        {
            Init();
        }
        return s_Logger;
    }
}