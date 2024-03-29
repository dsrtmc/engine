#include "Engine.h"
#include "EntryPoint.h"

#include <memory>

class Sandbox : public Engine::Application
{
public:
    Sandbox();
    ~Sandbox() override;

    inline Engine::Window *GetWindow() override { return m_Window; };

    void Run() override;

    void OnEvent(Engine::Event &e) override;

private:
    void Initialize();

private:
    Engine::Window *m_Window;
    float m_LastFrameTime = 0.0f;
};


Engine::Application *Engine::CreateApplication()
{
    return new Sandbox();
}