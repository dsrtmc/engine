#include "Event.h"

namespace Engine
{
    class MouseButtonEvent : public Event
    {
    public:
        MouseButtonEvent(int button)
            : m_Button(button) {}

    private:
        int m_Button;
    };

    class MouseButtonPressed : public MouseButtonEvent
    {
    public:
        MouseButtonPressed(int button)
            : MouseButtonEvent(button) {}
        
        EVENT_GET_TYPE_NAME(MouseButtonPressed);
    };

    class MouseButtonReleased : public MouseButtonEvent
    {
    public:
        MouseButtonReleased(int button)
            : MouseButtonEvent(button) {}
        
        EVENT_GET_TYPE_NAME(MouseButtonReleased);
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(double xoffset, double yoffset)
            : m_OffsetX(xoffset), m_OffsetY(yoffset) {}
        
        float GetXOffset() { return m_OffsetX; }
        float GetYOffset() { return m_OffsetY; }

        EVENT_GET_TYPE_NAME(MouseScrolled);

    private:
        double m_OffsetX;
        double m_OffsetY;
    };
}