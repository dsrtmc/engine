#include "Input.h"

#include <GLFW/glfw3.h>

namespace Engine
{
    // Instantiate the singleton
    Input *Input::s_Instance;

    bool Input::IsKeyPressedInternal(Application &app, int keycode)
    {
        auto window = app.GetWindow()->GetNativeWindow();
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressedInternal(Application &app, int button)
    {
        auto window = app.GetWindow()->GetNativeWindow();
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }
}