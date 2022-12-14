#pragma once

#include <glad/glad.h>

namespace Engine
{
    struct BufferElement
    {
        GLint count;
        GLenum type;
        GLboolean normalized;

        unsigned int GetSizeOfType(GLenum type) const
        {
            switch (type)
            {
                case GL_FLOAT:
                    return sizeof(GLfloat);
                case GL_UNSIGNED_INT:
                    return sizeof(GLuint);
                case GL_UNSIGNED_BYTE:
                    return sizeof(GLubyte);
            }
            return 0;
        };
    };

    class BufferLayout
    {
    public:
        BufferLayout() : m_Stride(0) {}

        std::vector<BufferElement> GetElements() const { return m_Elements; };
        GLsizei GetStride() const { return m_Stride; };

        // Add an attribute to the layout with *count* coordinates
        void Push(GLint count)
        {
            m_Elements.push_back((BufferElement){ count, GL_FLOAT, GL_FALSE });
            m_Stride += count * sizeof(GLfloat);
        }

    private:
        std::vector<BufferElement> m_Elements;
        GLsizei m_Stride;
    };

    class VertexBuffer
    {
    public:
        VertexBuffer(const void *data, unsigned int size);
        ~VertexBuffer();

        void SetData(const void *data, unsigned int size);
        void SetLayout(const BufferLayout &layout);
        
        BufferLayout GetLayout() const;

        void Bind() const;
        void Unbind() const;

    private:
        GLuint m_RendererID;
        BufferLayout m_Layout;
    };

    class IndexBuffer
    {
    public:
        /* Not sure why, but having size as a parameter behaves weird,
         * sizeof(indices) (GLuint[6]) returns 8 here, but 24 in the app itself */
        IndexBuffer(const void *indices, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;
        inline unsigned int GetCount() { return m_Count; };

    private:
        GLuint m_RendererID;
        unsigned int m_Count;
    };
}