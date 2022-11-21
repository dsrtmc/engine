#include <GLFW/glfw3.h>

#include <iostream>

#include "Engine.h"

class Sandbox : public Engine::Application
{
public:
    Sandbox()
    {
    }
    ~Sandbox()
    {
    }
};

void ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

int main(void)
{
    // Sandbox *sandbox = new Sandbox();
    // sandbox->Run();
    // delete sandbox;
    // return 0;
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // breaks logging after that point lol
    // std::cout << glGetString(GL_VERSION) << std::endl;

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 0.05f, 0.2f, 1.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}