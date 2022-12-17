#pragma once

#include <functional>

namespace Engine
{
    class Timer
    {
    typedef std::function<void(const std::string &name, double duration)> UpdateFunction;
    public:
        Timer(const std::string &name, const UpdateFunction &lambda);
        ~Timer();

        // Stops the timer and updates the profiling results vector
        void Stop();

    private:
        std::string m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
        bool m_Stopped = false;
        UpdateFunction m_Lambda;
    };
}