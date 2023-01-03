#include "Framebuffer.h"

#include <glad/glad.h>

namespace Engine
{
    Framebuffer::Framebuffer(FramebufferProperties properties)
        : m_Properties(properties)
    {
        glCreateFramebuffers(1, &m_RendererID);

        // Create the color attachment - texture
        glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachmentID);
        glTextureStorage2D(m_ColorAttachmentID, 1, GL_RGB8, m_Properties.width, m_Properties.height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        glNamedFramebufferTexture(m_RendererID, GL_COLOR_ATTACHMENT0, m_ColorAttachmentID, 0);

        // Create the depth-stencil attachment - renderbuffer
        glCreateRenderbuffers(1, &m_DepthStencilAttachmentID);
        glNamedRenderbufferStorage(m_DepthStencilAttachmentID, GL_DEPTH_STENCIL, m_Properties.width, m_Properties.height);
        glNamedFramebufferRenderbuffer(m_RendererID, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthStencilAttachmentID);

        if (glCheckNamedFramebufferStatus(m_RendererID, GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            ENG_ERROR("Framebuffer is not complete");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &m_RendererID);
    }

    void Framebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    }

    void Framebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}