#pragma once

#include <glad/glad.h>

namespace Engine
{
    class Texture2D
    {
    public:
        static GLuint currentSlot;
    public:
        Texture2D(GLsizei width, GLsizei height);
        explicit Texture2D(const std::string &filepath);
        ~Texture2D();

        void SetData(const void *data, unsigned int size);

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }
        inline GLuint GetRendererID() const { return m_RendererID; }

        void Bind(unsigned int slot) const;

    private:
        unsigned char *m_Data;
        int m_Width;
        int m_Height;
        int m_Channels;
        GLenum m_DataFormat;
        GLenum m_InternalFormat;
        GLuint m_RendererID;
    };
}