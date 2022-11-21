#include "Application.h"
#include "Log.h"

#include <GLFW/glfw3.h>
#include "spdlog/spdlog.h"

#include <iostream>

namespace Engine
{

    Application::Application(){

    };

    Application::~Application(){

    };

    void Application::Run()
    {
        if (!glfwInit())
            return;

        GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        ENG_CORE_INFO("log from application.cpp");
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }
};