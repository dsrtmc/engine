#pragma once

#include "Window.h"
#include "Layer.h"
#include "UILayer.h"

namespace Engine
{
    // TODO: make it a singleton or whatever, this class is ridiculously bad
    class Application
    {
    public:
        Application(const Application &) = delete;
        Application() {}
        virtual ~Application() {}

        virtual Window *GetWindow() = 0;

        virtual void Run() = 0;
        virtual void OnEvent(Event &event) = 0;

        static Application *Get() { return s_Instance; }

    protected:
        bool m_Running = true;
        std::unique_ptr<UILayer> m_UILayer;
        std::vector<Layer *> m_Layers;

        static Application *s_Instance;
    };

    Application *CreateApplication();
};