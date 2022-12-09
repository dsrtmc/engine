#include "Input.h"

#include "Application.h"

#include <GLFW/glfw3.h>

namespace Engine
{
    // Instantiate the singleton
    Input *Input::s_Instance;

    bool Input::IsKeyPressedInternal(int keycode)
    {
        auto window = Application::Get()->GetWindow()->GetNativeWindow();
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressedInternal(int button)
    {
        auto window = Application::Get()->GetWindow()->GetNativeWindow();
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }
}