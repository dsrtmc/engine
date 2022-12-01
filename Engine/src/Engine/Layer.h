#pragma once

namespace Engine
{
    class Layer
    {
    public:
        Layer(const std::string &name = "Layer");
        virtual ~Layer();

        virtual void OnUpdate() {}
        inline std::string GetName() { return m_Name; };

    private:
        std::string m_Name;
    };
}