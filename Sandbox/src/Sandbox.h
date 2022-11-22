#include "Engine.h"

class Sandbox : public Engine::Application
{
public:
    Sandbox();
    ~Sandbox() override;

    void Run() override;

private:
    Engine::Window *m_Window;
    bool m_Running = true;
};


Engine::Application *Engine::CreateApplication()
{
    return new Sandbox();
}