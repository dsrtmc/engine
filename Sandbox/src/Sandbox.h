#include "Engine.h"
#include "EntryPoint.h"

#include <memory>

class Sandbox : public Engine::Application
{
public:
    Sandbox();
    virtual ~Sandbox() override;

    inline Engine::Window *GetWindow() { return m_Window; };

    virtual void Run() override;

    virtual void OnEvent(Engine::Event &event) override;

private:
    void Initialize();

private:
    Engine::Window *m_Window;
};


Engine::Application *Engine::CreateApplication()
{
    return new Sandbox();
}