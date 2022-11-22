#pragma once
#include <iostream>

extern Engine::Application *Engine::CreateApplication();

int main(void)
{
    Engine::Log::Init();
    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
    return 0;
}