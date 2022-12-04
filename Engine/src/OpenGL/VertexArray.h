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

        // void SetVertexBuffer(const VertexBuffer &vbo);
        void SetVertexBuffer(const std::shared_ptr<VertexBuffer> &vbo);
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &ibo);

        std::shared_ptr<VertexBuffer> GetVertexBuffer() const { return m_VertexBuffer; }
        std::shared_ptr<IndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; }

        void Bind() const;
        void Unbind() const;

    private:
        GLuint m_RendererID;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}