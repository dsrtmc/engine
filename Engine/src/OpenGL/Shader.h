#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.inl>

namespace Engine
{
    class Shader
    {
    /* Can't have a private constructor with make_unique(), so we make it public and require
     * a non-public tag type as a parameter. */ 
    struct _tag {};
    public:
        Shader(_tag) {}
        ~Shader();

        static std::unique_ptr<Shader> FromTextFiles(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

        GLint GetUniformLocation(const std::string &name);

        void SetUniform1i(const std::string &name, bool value);
        void SetUniform1i(const std::string &name, GLint value);
        void SetUniform1f(const std::string &name, GLfloat value);
        void SetUniform2f(const std::string &name, GLfloat v0, GLfloat v1);
        void SetUniform2fv(const std::string &name, const glm::vec2 &vector);
        void SetUniform3f(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2);
        void SetUniform3fv(const std::string &name, const glm::vec3 &vector);
        void SetUniform4f(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
        void SetUniform4fv(const std::string &name, const glm::vec4 &vector);
        void SetUniformMatrix2fv(const std::string &name, const glm::mat4 &matrix);
        void SetUniformMatrix3fv(const std::string &name, const glm::mat4 &matrix);
        void SetUniformMatrix4fv(const std::string &name, const glm::mat4 &matrix);

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