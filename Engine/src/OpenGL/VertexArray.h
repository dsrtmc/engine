#pragma once

#include "Buffer.h"

namespace Engine
{
    // For now it supports one vertex buffer per vertex array, will probably change in the future
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void SetVertexBuffer(const VertexBuffer &vbo);
        void SetIndexBuffer(const IndexBuffer &ibo);

        void Bind() const;
        void Unbind() const;

    private:
        GLuint m_RendererID;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
    };
}