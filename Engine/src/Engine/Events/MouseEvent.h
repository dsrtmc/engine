#pragma once

#include "Event.h"

namespace Engine
{
    class MouseButtonEvent : public Event
    {
    public:
        explicit MouseButtonEvent(int button)
            : m_Button(button) {}

    private:
        int m_Button;
    };

    class MouseButtonPressed : public MouseButtonEvent
    {
    public:
        explicit MouseButtonPressed(int button)
            : MouseButtonEvent(button) {}
        
        EVENT_GET_TYPE_NAME(MouseButtonPressed);
    };

    class MouseButtonReleased : public MouseButtonEvent
    {
    public:
        explicit MouseButtonReleased(int button)
            : MouseButtonEvent(button) {}
        
        EVENT_GET_TYPE_NAME(MouseButtonReleased);
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(double xoffset, double yoffset)
            : m_OffsetX(xoffset), m_OffsetY(yoffset) {}
        
        [[nodiscard]] double GetXOffset() const { return m_OffsetX; }
        [[nodiscard]] double GetYOffset() const { return m_OffsetY; }

        EVENT_GET_TYPE_NAME(MouseScrolled);

    private:
        double m_OffsetX;
        double m_OffsetY;
    };
}