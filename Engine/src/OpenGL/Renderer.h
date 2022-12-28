#pragma once

#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"

#include <glad/glad.h>

namespace Engine
{
    class Renderer
    {
    typedef std::shared_ptr<VertexArray> RefVAO;
    typedef std::shared_ptr<Shader> RefShader;
    public:
        Renderer(const Renderer &) = delete;

        static void Clear();
        static void Submit(const RefVAO &vao, const RefShader &shader);

    private:
        static void Draw(GLsizei count);

    private:
        Renderer() = default;
        unsigned int m_RendererID;
    };
};
