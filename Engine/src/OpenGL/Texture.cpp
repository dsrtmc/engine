#include "Texture.h"

#include "stb_image.h"

namespace Engine
{
    Texture::Texture(const std::string &filepath)
        : m_Data(nullptr), m_Width(0), m_Height(0),
        m_Channels(0), m_Filepath(filepath), m_RendererID(0)
    {
        stbi_set_flip_vertically_on_load(true);
        // TODO: think if we actually need to store height, width etc in the class itself
        m_Data = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_Channels, 0);

        if (!m_Data)
            ENG_WARN("Failed to load texture: {0}", filepath);

        GLenum dataFormat = 0;
        if (m_Channels == 3)
            dataFormat = GL_RGB;
        else if (m_Channels == 4)
            dataFormat = GL_RGBA;
        
        // TODO: assert(dataFormat != 0, "wrong format");
        if (!dataFormat)
            ENG_WARN("Texture format not supported: {0}", filepath);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        // Texture filtering for magnifying/minifying operations
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Texture wrapping
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        // Only .jpg || .png for now
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, m_Data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(m_Data);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void Texture::Bind(unsigned int slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }

    void Texture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}