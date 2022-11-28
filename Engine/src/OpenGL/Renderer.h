#pragma once

#include <glad/glad.h>

#include "Buffer.h"

namespace Engine
{
    class Renderer
    {
    public:
        static void Clear();
        static void Draw(unsigned int count);

    private:
        Renderer();
        unsigned int m_RendererID;
    };
};
