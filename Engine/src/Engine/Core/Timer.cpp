#include "Timer.h"

namespace Engine
{
    Timer::Timer(const std::string &name)
        : m_Name(name)
    {
        m_Start = std::chrono::high_resolution_clock::now();
    }

    Timer::~Timer()
    {
    }

    double Timer::GetDuration() const
    {
        auto now = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_Start).time_since_epoch();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch();

        auto duration = end - start;
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

        return duration.count();
    }
}