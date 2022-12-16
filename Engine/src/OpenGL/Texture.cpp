#include "Texture.h"

#include "stb_image.h"

namespace Engine
{
    Texture2D::Texture2D(GLsizei width, GLsizei height)
        : m_Data(nullptr), m_Width(width), m_Height(height),
        m_Channels(0), m_RendererID(0), m_DataFormat(0), m_InternalFormat(0)
    {
        m_DataFormat = GL_RGB;
        m_InternalFormat = GL_RGB8;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        // Texture filtering for magnifying/minifying operations
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Texture wrapping
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    }

    Texture2D::Texture2D(const std::string &filepath)
        : m_Data(nullptr), m_Width(0), m_Height(0),
        m_Channels(0), m_Filepath(filepath), m_RendererID(0),
        m_DataFormat(0), m_InternalFormat(0)
    {
        stbi_set_flip_vertically_on_load(true);
        // TODO: think if we actually need to store height, width etc in the class itself
        m_Data = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_Channels, 0);

        if (!m_Data)
            ENG_WARN("Failed to load texture: {0}", filepath);

        if (m_Channels == 3)
        {
            m_DataFormat = GL_RGB;
            m_InternalFormat = GL_RGB8;
        }
        else if (m_Channels == 4)
        {
            m_DataFormat = GL_RGBA;
            m_InternalFormat = GL_RGBA8;
        }
        
        // TODO: assert(dataFormat != 0, "wrong format");
        if (!m_DataFormat || !m_InternalFormat)
            ENG_WARN("Texture format not supported: {0}", filepath);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        // Texture filtering for magnifying/minifying operations
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Texture wrapping
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        // Only .jpg || .png for now
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, m_Data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(m_Data);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void Texture2D::SetData(const void *data, unsigned int size)
    {
        unsigned int bpp = m_DataFormat == GL_RGB ? 3 : 4;
        if (bpp * m_Width * m_Height != size)
            ENG_WARN("Invalid texture (size != w * h * bpp)");
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void Texture2D::Bind(unsigned int slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }

    void Texture2D::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}