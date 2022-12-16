#pragma once

namespace Engine
{
    class Timer
    {
    public:
        Timer(const std::string &name);
        ~Timer();

        inline const std::string &GetName() const { return m_Name; }

        double GetDuration() const;

    private:
        std::string m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    };
}