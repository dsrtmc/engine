#include <glad/glad.h>

namespace Engine
{
    class VertexBuffer
    {
    public:
        VertexBuffer(const void *data, unsigned int size);
        ~VertexBuffer();

        // use glBufferSubData
        void SetData(const void *data, unsigned int size);

        void Bind() const;
        void Unbind() const;
    private:
        GLuint m_RendererID;
    };

    class IndexBuffer
    {
    public:
        /*
            Not sure why, but having size as a parameter behaves weird,
            sizeof(indices) (GLuint[6]) returns 8 here, but 24 in the app itself
        */
        IndexBuffer(const void *indices, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

    private:
        GLuint m_RendererID;
    };
}