#include "VertexArray.h"

namespace Engine
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::SetVertexBuffer(const VertexBuffer &vbo)
    {
        this->Bind();
        vbo.Bind();

        BufferLayout layout = vbo.GetLayout();

        const auto &elements = layout.GetElements();
        GLsizei stride = layout.GetStride();

        unsigned int offset = 0;
        for (int i = 0; i < elements.size(); i++)
        {
            const auto &element = elements[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                                        stride, (const void *)offset);
            offset += element.count * element.GetSizeOfType(element.type);
        }
        m_VertexBuffer = std::make_unique<VertexBuffer>(vbo);
    }

    void VertexArray::SetIndexBuffer(const IndexBuffer &ibo)
    {
        this->Bind();
        ibo.Bind();
        m_IndexBuffer = std::make_unique<IndexBuffer>(ibo);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
}