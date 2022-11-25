#pragma once

#include <glad/glad.h>

namespace Engine
{
    class Shader
    {
    /*
        Can't have a private constructor with make_unique(), so we make it public and require
        a non-public tag type as a parameter.
    */ 
    struct _tag {};
    public:
        Shader(_tag) {}
        ~Shader();

        static std::unique_ptr<Shader> FromTextFiles(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

        void Bind() const;
        void Unbind() const;

    private:
        void LoadFromTextFiles(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

        static std::string ParseShader(const std::string &filepath);
        static GLuint CreateShader(const std::string &source, GLenum type);

    private:
        GLuint m_RendererID;
    };
};