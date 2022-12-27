#pragma once

#include "Event.h"

namespace Engine
{
    class Layer
    {
    public:
        explicit Layer(const std::string &name = "Layer") { m_Name = name; }
        virtual ~Layer() = default;

        virtual void OnImGuiUpdate() {}
        virtual void OnUpdate(float timestep) {}
        virtual void OnEvent(Event &event) {}
        inline std::string GetName() { return m_Name; };

    private:
        std::string m_Name;
    };
}