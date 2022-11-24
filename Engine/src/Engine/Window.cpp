#include "Window.h"

namespace Engine
{
    Window *Window::Create(EventCallbackFn eventCallback, const WindowProps &props)
    {
        return new Window(eventCallback, props);
    }

    Window::Window(EventCallbackFn eventCallback, const WindowProps &props)
    {
        Init(eventCallback, props);
    }

    Window::~Window()
    {
        Shutdown();
    }

    void Window::Init(EventCallbackFn eventCallback, const WindowProps &props)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        SetEventCallback(eventCallback);

        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        if (!s_GLFWInitialized)
        {
            glfwInit();
            // ASSERT(glfwInit(), "errro messge");
            s_GLFWInitialized = true;
        }
        m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
    }

    void Window::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void Window::OnUpdate()
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    unsigned int Window::GetWidth() const
    {
        return m_Data.Width;
    }

    unsigned int Window::GetHeight() const
    {
        return m_Data.Height;
    }

    GLFWwindow *Window::GetWindow() const
    {
        return m_Window;
    }

    void Window::SetEventCallback(EventCallbackFn eventCallback)
    {
        m_EventCallback = eventCallback;
    }

    EventCallbackFn Window::GetEventCallback() const
    {
        return m_EventCallback;
    }
};