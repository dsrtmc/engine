#include "Texture.h"

#include "stb_image.h"

namespace Engine
{
    Texture::Texture(const std::string &filepath)
        : m_Data(nullptr), m_Width(0), m_Height(0),
        m_BPP(0), m_Filepath(filepath), m_RendererID(0)
    {
        stbi_set_flip_vertically_on_load(true);
        m_Data = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 0);

        if (!m_Data)
        {
            ENG_WARN("Failed to load texture: {0}", filepath);
        }

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        // Texture filtering for magnifying/minifying operations
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Texture wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        // Only .jpg for now
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_Data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(m_Data);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void Texture::Bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void Texture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}