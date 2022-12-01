#include "Engine.h"

#include <memory>

class Sandbox : public Engine::Application
{
public:
    Sandbox();
    ~Sandbox() override;

    void Run() override;

private:
    void PollEvents() override;
    void Initialize();

private:
    std::unique_ptr<Engine::Shader> m_Shader;
};


Engine::Application *Engine::CreateApplication()
{
    return new Sandbox();
}