#pragma once

#include "Application.h"

namespace Engine
{
    class Input
    {
    public:
        Input(const Input &) = delete;

        // definitely needs to be fixed but my Application is not a singleton yet
        inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedInternal(keycode); }
        inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedInternal(button); }

    private:
        Input();
        bool IsKeyPressedInternal(int keycode);
        bool IsMouseButtonPressedInternal(int button);

    private:
        static Input *s_Instance;
    };
}