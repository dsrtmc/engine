#pragma once

namespace Engine
{
    struct FramebufferProperties
    {
        unsigned int width, height;
    };

    class Framebuffer {
    public:
        explicit Framebuffer(FramebufferProperties properties);
        ~Framebuffer();

        unsigned int GetColorAttachmentID() { return m_ColorAttachmentID; }

        void Bind();
        void Unbind();

    private:
        FramebufferProperties m_Properties;
        unsigned int m_RendererID;
        unsigned int m_ColorAttachmentID;
        unsigned int m_DepthStencilAttachmentID;
    };
}