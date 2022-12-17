#include "Timer.h"

namespace Engine
{
    Timer::Timer(const std::string &name, const UpdateFunction &lambda)
        : m_Name(name), m_Lambda(lambda)
    {
        m_Start = std::chrono::high_resolution_clock::now();
    }

    Timer::~Timer()
    {
        if (!m_Stopped)
            Stop();
    }

    void Timer::Stop()
    {
        auto now = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_Start).time_since_epoch();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch();

        auto duration = end - start;

        m_Lambda(m_Name, duration.count());
        m_Stopped = true;
    }
}