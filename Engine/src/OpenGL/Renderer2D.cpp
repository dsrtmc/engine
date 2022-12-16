#include "Renderer2D.h"

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    struct RenderData
    {
        std::shared_ptr<VertexArray> QuadVertexArray;
        std::shared_ptr<Shader> QuadShader;
        std::shared_ptr<Texture2D> QuadWhiteTexture;
    };

    static RenderData *s_Data;

    void Renderer2D::Initialize()
    {
        s_Data = new RenderData;

        s_Data->QuadShader = Shader::FromTextFiles(
            "../Sandbox/assets/shaders/quad.vert.glsl",
            "../Sandbox/assets/shaders/quad.frag.glsl"
        );

        // Create a 1x1 white fallback texture; will load unless we specify a texture in the draw call
        unsigned int white = 0xffffffff;
        s_Data->QuadWhiteTexture = std::make_shared<Texture2D>(1, 1);
        s_Data->QuadWhiteTexture->SetData(&white, sizeof(unsigned int));
        s_Data->QuadWhiteTexture->Bind(0);

        float vertices[4 * 5] = {
            // vertex position //  texture  //
            -0.5f, -0.5f, 0.0f, -1.0f, -1.0f, // bottom left
             0.5f, -0.5f, 0.0f,  1.0f, -1.0f, // bottom right
             0.5f,  0.5f, 0.0f,  1.0f,  1.0f, // top right
            -0.5f,  0.5f, 0.0f, -1.0f,  1.0f  // top left
        };

        GLuint indices[2 * 3] = {
            0, 1, 2,
            2, 3, 0
        };

        // Create a vertex array object
        std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>();

        // Specify a layout of our vertices
        // TODO: maybe change bufferlayout logic, looks ugly
        BufferLayout layout;
        layout.Push(3); // vertex positions
        layout.Push(2); // texture coordinates

        // Create a vertex buffer object and bind it to the specified layout
        std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        vbo->SetLayout(layout);

        // Create an index buffer object 
        std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));
        ibo->Bind();

        // Make the buffers the vertex array's private members, not used yet
        vao->SetVertexBuffer(vbo);
        vao->SetIndexBuffer(ibo);

        s_Data->QuadVertexArray = vao;
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(std::shared_ptr<const OrthographicCamera> camera)
    {
        s_Data->QuadVertexArray->Bind();
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetUniformMatrix4fv("u_VP", camera->GetProjectionMatrix() * camera->GetViewMatrix());
        s_Data->QuadShader->SetUniformMatrix4fv("u_Transform", glm::mat4(1.0f));
    }

    void Renderer2D::EndScene()
    {
    }

    /* For every quad, the default values are vec4(1.0, 1.0, 1.0, 1.0) for color
     * and a 1x1px white texture. One can choose whether they want to use a texture or
     * a solid color by specifying those parameters */
    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        GLsizei count = s_Data->QuadVertexArray->GetIndexBuffer()->GetCount();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        s_Data->QuadShader->SetUniform4fv("u_Color", color);
        s_Data->QuadShader->SetUniformMatrix4fv("u_Transform", transform);
        s_Data->QuadWhiteTexture->Bind(0);

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, std::shared_ptr<Texture2D> texture)
    {
        GLsizei count = s_Data->QuadVertexArray->GetIndexBuffer()->GetCount();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        s_Data->QuadShader->SetUniform4fv("u_Color", glm::vec4(1.0f));
        s_Data->QuadShader->SetUniformMatrix4fv("u_Transform", transform);
        texture->Bind(0);

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
    // TODO: Allow drawing textured quads with a tint color
}