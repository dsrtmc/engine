#pragma once

#include "Event.h"

namespace Engine
{
    class KeyEvent : public Event
    {
    public:
        // should probably be int since we're using GLFW unknown key that's -1
        KeyEvent(unsigned int Keycode)
            : m_Keycode(Keycode) {}

    private:
        unsigned int m_Keycode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, bool repeated = false)
            : KeyEvent(keycode), m_IsRepeat(repeated) {}

        EVENT_GET_TYPE_NAME(KeyPressed);

        bool IsRepeat() const { return m_IsRepeat; }

    private:
        bool m_IsRepeat;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {}

        EVENT_GET_TYPE_NAME(KeyReleased);
    };
}