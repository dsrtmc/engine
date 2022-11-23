#include "Shader.h"
#include "Log.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
        {
            ss << line << '\n';
        }
        std::cout << "answer: " << ss.str() << std::endl;
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

            ENG_ERROR("Failed to compile {0} shader.", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
            ENG_ERROR("{0}", std::string(message));

            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }
}