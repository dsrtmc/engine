#pragma once

#include <glad/glad.h>

#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"

namespace Engine
{
    class Renderer
    {
    typedef std::shared_ptr<Engine::VertexArray> RefVAO;
    typedef std::shared_ptr<Engine::Shader> RefShader;
    public:
        Renderer(const Renderer &) = delete;

        static void Clear();
        static void Submit(const RefVAO &vao, const RefShader &shader);

    private:
        static void Draw(unsigned int count);

    private:
        Renderer();
        unsigned int m_RendererID;
    };
};
