#include "Engine.h"
#include "EntryPoint.h"

#include <memory>

class Sandbox : public Engine::Application
{
public:
    Sandbox();
    ~Sandbox() override;

    inline Engine::Window *GetWindow() { return m_Window; };

    void Run() override;

    void OnEvent(Engine::Event &e);

private:
    void Initialize();

private:
    Engine::Window *m_Window;
};


Engine::Application *Engine::CreateApplication()
{
    return new Sandbox();
}