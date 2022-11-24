#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Engine
{
    static bool s_GLFWInitialized = false;

    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string &title = "Engine",
                    unsigned int width = 1280, unsigned int height = 720)
            : Title(title), Width(width), Height(height){};
    };

    class Window
    {
    public:
        Window(const WindowProps &props);
        ~Window();

        unsigned int GetWidth()  const;
        unsigned int GetHeight() const;
        GLFWwindow *GetWindow()  const;

        void Init(const WindowProps &props);
        void Shutdown();
        void OnUpdate();

        static Window *Create(const WindowProps &props = WindowProps());

    private:
        GLFWwindow *m_Window;
        WindowProps m_Data;
        EventCallbackFn m_EventCallback;
    };
};