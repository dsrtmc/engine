#pragma once

#include "Window.h"

namespace Engine
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();

    private:
        Window *m_Window;
        bool m_Running = true;
    };

    Application *CreateApplication();
};