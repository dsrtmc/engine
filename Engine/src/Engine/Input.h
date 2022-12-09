#pragma once

#include "Application.h"

namespace Engine
{
    class Input
    {
    public:
        Input(const Input &) = delete;

        // definitely needs to be fixed but my Application is not a singleton yet
        inline static bool IsKeyPressed(Application &app, int keycode) { return s_Instance->IsKeyPressedInternal(app, keycode); }
        inline static bool IsMouseButtonPressed(Application &app, int button) { return s_Instance->IsMouseButtonPressedInternal(app, button); }

    private:
        Input();
        bool IsKeyPressedInternal(Application &app, int keycode);
        bool IsMouseButtonPressedInternal(Application &app, int button);

    private:
        static Input *s_Instance;
    };
}