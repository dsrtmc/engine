#pragma once

#include <glad/glad.h>

namespace Engine
{
    /* Buffer Layout */
    struct BufferElement
    {
        GLsizei count;
        GLenum type;
        GLboolean normalized;

        static unsigned int GetSizeOfType(GLenum type)
        {
            switch (type)
            {
                case GL_FLOAT:
                    return sizeof(GLfloat);
                case GL_UNSIGNED_INT:
                    return sizeof(GLuint);
                case GL_UNSIGNED_BYTE:
                    return sizeof(GLubyte);
                default:
                    return 0;
            }
        };
    };

    class BufferLayout
    {
    public:
        explicit BufferLayout(const std::vector<std::pair<GLsizei, std::string>> &elements)
            : m_Stride(0)
        {
            for (auto &element : elements)
            {
                m_Elements.push_back((BufferElement) { element.first, GL_FLOAT, GL_FALSE });
                m_Stride += element.first * sizeof(GLfloat);
            }
        }

        [[nodiscard]] std::vector<BufferElement> GetElements() const { return m_Elements; };
        [[nodiscard]] GLsizei GetStride() const { return m_Stride; };

    private:
        std::vector<BufferElement> m_Elements;
        GLsizei m_Stride;
    };

    /* Vertex Buffer */
    class VertexBuffer
    {
    public:
        explicit VertexBuffer(unsigned int size);
        VertexBuffer(const void *data, unsigned int size);
        ~VertexBuffer();

        void SetData(const void *data, unsigned int size) const;
        void SetLayout(const BufferLayout &layout);
        
        [[nodiscard]] BufferLayout GetLayout() const;

        void Bind() const;
        void Unbind() const;

    private:
        GLuint m_RendererID;
        BufferLayout m_Layout;
    };

    /* Index Buffer */
    class IndexBuffer
    {
    public:
        /* Not sure why, but having size as a parameter behaves weird,
         * sizeof(indices) (GLuint[6]) returns 8 here, but 24 in the app itself */
        IndexBuffer(const void *indices, GLsizei count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;
        [[nodiscard]] inline GLsizei GetCount() const { return m_Count; };

    private:
        GLuint m_RendererID;
        GLsizei m_Count;
    };
}