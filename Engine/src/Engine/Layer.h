#pragma once

#include "Event.h"

namespace Engine
{
    class Layer
    {
    public:
        Layer(const std::string &name = "Layer") { m_Name = name; }
        virtual ~Layer() {}

        virtual void OnImGuiUpdate() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event &event) {}
        inline std::string GetName() { return m_Name; };

    private:
        std::string m_Name;
    };
}