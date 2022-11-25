#pragma once

#include <glad/glad.h>

namespace Engine
{
    class Renderer
    {
    public:
        static void Clear();
        static void Draw();

    private:
        Renderer();
        unsigned int m_RendererID;
    };
};
