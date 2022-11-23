#include "Shader.h"

#include "Log.h"

namespace Engine
{
    Shader::Shader()
    {
        ENG_INFO("created a shader");
    }

    Shader::~Shader()
    {
        ENG_INFO("destroyed a shader");
    }
}