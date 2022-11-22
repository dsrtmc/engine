#include "Window.h"

namespace Engine
{
    Window *Window::Create(const WindowProps &props)
    {
        return new Window(props);
    }

    Window::Window(const WindowProps &props)
    {
        Init(props);
    }

    Window::~Window()
    {
        Shutdown();
    }

    void Window::Init(const WindowProps &props)
    {
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
};