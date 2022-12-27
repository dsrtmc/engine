#include "VertexArray.h"

namespace Engine
{
    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::SetVertexBuffer(std::shared_ptr<VertexBuffer> vbo)
    {
        this->Bind();
        vbo->Bind();

        BufferLayout layout = vbo->GetLayout();

        const auto &elements = layout.GetElements();
        GLsizei stride = layout.GetStride();

        unsigned int offset = 0;
        for (int i = 0; i < elements.size(); i++)
        {
            const auto &element = elements[i];
            glEnableVertexAttribArray(i);
            // Do a double cast to ignore the compiler warning: -W-int-to-void-pointer-cast
            glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                                        stride, (const void *)(uintptr_t)offset);
            offset += element.count * BufferElement::GetSizeOfType(element.type);
        }
        m_VertexBuffer = vbo;
    }

    void VertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> ibo)
    {
        this->Bind();
        ibo->Bind();
        m_IndexBuffer = ibo;
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