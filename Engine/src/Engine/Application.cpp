#include "Application.h"

/*
Application is sort of an interface, but also a singleton
This .cpp file's purpose is only to initialize its static s_Instance variable,
so that there are no "multiple definition" errors
*/
namespace Engine
{
    Application *Application::s_Instance;
};