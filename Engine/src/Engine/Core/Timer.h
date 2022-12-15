#pragma once

struct TimeFormat
{
    double microseconds;
    double milliseconds;
};

namespace Engine
{
    class Timer
    {
    public:
        Timer();
        ~Timer();

        TimeFormat GetDuration();

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    };
}