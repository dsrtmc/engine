#include "Shader.h"

namespace Engine
{
    Shader::~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    std::string Shader::ParseShader(const std::string &filepath)
    {
        // Could write in C in the future
        std::ifstream file(filepath);
        std::string line;
        std::stringstream ss;
        while (std::getline(file, line))
            ss << line << '\n';
        return ss.str();
    }

    std::unique_ptr<Shader> Shader::FromTextFiles(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
    {
        std::unique_ptr<Shader> shader = std::make_unique<Shader>(_tag());
        shader->LoadFromTextFiles(vertexShaderPath, fragmentShaderPath);
        return shader;
    }

    void Shader::LoadFromTextFiles(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
    {
        std::string vertexSource = ParseShader(vertexShaderPath);
        std::string fragmentSource = ParseShader(fragmentShaderPath);
        if (vertexSource.empty())
            ENG_WARN("Vertex shader not found");
        if (fragmentSource.empty())
            ENG_WARN("Fragment shader not found");

        GLuint vs = CreateShader(vertexSource, GL_VERTEX_SHADER);
        GLuint fs = CreateShader(fragmentSource, GL_FRAGMENT_SHADER);

        GLuint shaderProgram;
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vs);
        glAttachShader(shaderProgram, fs);
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);
        glDetachShader(shaderProgram, vs);
        glDetachShader(shaderProgram, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);
        m_RendererID = shaderProgram;
    }

    GLuint Shader::CreateShader(const std::string &source, GLenum type)
    {
        const char *src = source.c_str();
        GLuint shader;
        shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            // Get shader compilation error log
            int length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            char message[length];
            glGetShaderInfoLog(shader, length, &length, message);

            ENG_ERROR("(GLSL) Failed to compile {0} shader.", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
            ENG_ERROR("(GLSL) {0}", std::string(message));

            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    GLint Shader::GetUniformLocation(const std::string &name) const
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        if (location == -1)
            ENG_WARN("Uniform \"{0}\" not found or unused.", name);
        return location;
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::SetUniform1i(const std::string &name, bool value)
    {
        glUniform1i(GetUniformLocation(name), (GLint)value);
    }

    void Shader::SetUniform1i(const std::string &name, GLint value)
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetUniform1iv(const std::string &name, GLint *values, int count)
    {
        glUniform1iv(GetUniformLocation(name), count, values);
    }

    void Shader::SetUniform1f(const std::string &name, GLfloat value)
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetUniform2f(const std::string &name, GLfloat v0, GLfloat v1)
    {
        glUniform2f(GetUniformLocation(name), v0, v1);
    }
    
    void Shader::SetUniform2fv(const std::string &name, const glm::vec2 &vector)
    {
        glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(vector));
    }

    void Shader::SetUniform3f(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2)
    {
        glUniform3f(GetUniformLocation(name), v0, v1, v2);
    }

    void Shader::SetUniform3fv(const std::string &name, const glm::vec3 &vector)
    {
        glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vector));
    }

    void Shader::SetUniform4f(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
    {
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }
    
    void Shader::SetUniform4fv(const std::string &name, const glm::vec4 &vector)
    {
        glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(vector));
    }

    void Shader::SetUniformMatrix2fv(const std::string &name, const glm::mat4 &matrix)
    {
        glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::SetUniformMatrix3fv(const std::string &name, const glm::mat4 &matrix)
    {
        glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::SetUniformMatrix4fv(const std::string &name, const glm::mat4 &matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }
}