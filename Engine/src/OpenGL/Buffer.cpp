#include "Buffer.h"

namespace Engine
{
    /* ------------ Vertex Buffer ------------ */
    VertexBuffer::VertexBuffer(unsigned int size)
        : m_Layout({})
    {
        glCreateBuffers(1, &m_RendererID);

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::VertexBuffer(const void *data, unsigned int size)
        : m_Layout({})
    {
        glCreateBuffers(1, &m_RendererID);

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void VertexBuffer::SetData(const void *data, unsigned int size) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    void VertexBuffer::SetLayout(const BufferLayout &layout)
    {
        m_Layout = layout;
    }

    BufferLayout VertexBuffer::GetLayout() const
    {
        return m_Layout;
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /* ------------ Index Buffer ------------ */
    IndexBuffer::IndexBuffer(const void *indices, GLsizei count)
        : m_Count(count)
    {
        glCreateBuffers(1, &m_RendererID);

        // Binding to GL_ARRAY_BUFFER apparently prevents an error in case of an unbound VAO
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLsizei), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}