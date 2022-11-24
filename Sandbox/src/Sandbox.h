#include "Engine.h"

#include <memory>

class Sandbox : public Engine::Application
{
public:
    Sandbox();
    ~Sandbox() override;

    void Run() override;

private:
    void EventCallback() override;
    void Initialize();

private:
    bool m_Running = true;
    Engine::Window *m_Window;
    std::unique_ptr<Engine::Shader> m_Shader;
};


Engine::Application *Engine::CreateApplication()
{
    return new Sandbox();
}