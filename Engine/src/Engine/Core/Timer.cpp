#include "Timer.h"

namespace Engine
{
    Timer::Timer()
    {
        m_Start = std::chrono::high_resolution_clock::now();
    }

    Timer::~Timer()
    {
    }

    TimeFormat Timer::GetDuration()
    {
        auto now = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_Start).time_since_epoch();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch();

        auto duration = end - start;
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

        return (TimeFormat){ (double)duration.count(), (double)duration.count() * 0.001 };
    }
}