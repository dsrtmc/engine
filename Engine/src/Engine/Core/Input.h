#pragma once

#include "Application.h"

namespace Engine
{
    class Input
    {
    public:
        Input(const Input &) = delete;

        inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedInternal(keycode); }
        inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedInternal(button); }

    private:
        Input() = default;
        bool IsKeyPressedInternal(int keycode);
        bool IsMouseButtonPressedInternal(int button);

    private:
        static Input *s_Instance;
    };
}