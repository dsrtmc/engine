#pragma once

#include "Window.h"
#include "Layer.h"
#include "UILayer.h"

namespace Engine
{
    class Application
    {
    public:
        Application() {}
        virtual ~Application() {}

        virtual void Run() = 0;

    private:
        virtual void PollEvents() = 0; 

    protected:
        bool m_Running = true;
        std::unique_ptr<UILayer> m_UILayer;
        std::vector<Layer *> m_Layers;
    };

    Application *CreateApplication();
};