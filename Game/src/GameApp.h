#include "Engine.h"
#include "EntryPoint.h"

#include <memory>

class GameApp : public Engine::Application
{
public:
    GameApp();
    ~GameApp() override;

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
    return new GameApp();
}