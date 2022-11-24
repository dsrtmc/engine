#pragma once

#include "Window.h"

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

    private:
        Window *m_Window;
        bool m_Running = true;
    };

    Application *CreateApplication();
};