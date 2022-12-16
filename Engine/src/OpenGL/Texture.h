#pragma once

#include <glad/glad.h>

namespace Engine
{
    class Texture2D
    {
    public:
        Texture2D(GLsizei width, GLsizei height);
        Texture2D(const std::string &filepath);
        ~Texture2D();

        void SetData(const void *data, unsigned int size);

        void Bind(unsigned int slot) const;
        void Unbind() const;

    private:
        unsigned char *m_Data;
        int m_Width;
        int m_Height;
        int m_Channels;
        GLenum m_DataFormat;
        GLenum m_InternalFormat;
        std::string m_Filepath;
        GLuint m_RendererID;
    };
}