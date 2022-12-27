#pragma once

#include "Event.h"

namespace Engine
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {}

        [[nodiscard]] unsigned int GetWidth() const { return m_Width; }
        [[nodiscard]] unsigned int GetHeight() const { return m_Height; }

        EVENT_GET_TYPE_NAME(WindowResized);

    private:
        unsigned int m_Width;
        unsigned int m_Height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_GET_TYPE_NAME(WindowClosed);

    private:
        unsigned int m_Width;
        unsigned int m_Height;
    };
}