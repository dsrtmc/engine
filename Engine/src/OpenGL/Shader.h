#pragma once

#include <glad/glad.h>

namespace Engine
{
    class Shader
    {
    public:
        Shader();
        ~Shader();
    private:
        GLuint m_RendererID;
    };
};