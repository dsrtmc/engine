#pragma once

extern Engine::Application *Engine::CreateApplication();

int main(int argc, char **argv)
{
    // Engine::Log::Init();
    // ENG_CORE_INFO("Initialized Log!");
    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
    return 0;
}