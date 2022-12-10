#pragma once

namespace Engine
{

    #define EVENT_GET_TYPE_NAME(type) virtual EventType GetType() const override { return EventType::type; }\
                                   virtual std::string GetName() const override { return #type; }


    enum class EventType
    {
        None = 0,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseScrolled,
        WindowResized, WindowClosed
    };

    class Event
    {
    public:
        virtual EventType GetType() const = 0;
        virtual std::string GetName() const = 0;

    private:
        bool m_Handled = false;
    };
}