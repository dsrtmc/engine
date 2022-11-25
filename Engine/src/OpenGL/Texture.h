#pragma once

#include <glad/glad.h>

namespace Engine
{
    class Texture
    {
    public:
        Texture(const std::string &filepath);
        ~Texture();

        void Bind(unsigned int slot) const;
        void Unbind() const;

    private:
        unsigned char *m_Data;
        int m_Width;
        int m_Height;
        int m_BPP;
        std::string m_Filepath;
        GLuint m_RendererID;
    };
}