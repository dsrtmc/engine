#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Engine
{
    static bool s_GLFWInitialized = false;

    typedef void (*EventCallbackFn)();

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
        Window(EventCallbackFn eventCallback, const WindowProps &props);
        ~Window();

        unsigned int GetWidth()  const;
        unsigned int GetHeight() const;
        GLFWwindow *GetWindow()  const;

        void SetEventCallback(EventCallbackFn eventCallback);
        EventCallbackFn GetEventCallback() const;

        void Init(EventCallbackFn eventCallback, const WindowProps &props);
        void Shutdown();
        void OnUpdate();

        static Window *Create(
            EventCallbackFn eventCallback = nullptr, const WindowProps &props = WindowProps()
        );

    private:
        GLFWwindow *m_Window;
        WindowProps m_Data;
        EventCallbackFn m_EventCallback;
    };
};