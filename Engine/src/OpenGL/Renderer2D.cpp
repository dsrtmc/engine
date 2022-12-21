#include "Renderer2D.h"

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TextureCoordinates;
    };

    struct RenderData
    {
        const unsigned int MaxQuads = 5000;
        const unsigned int MaxVertices = MaxQuads * 4;
        const unsigned int MaxIndices = MaxQuads * 6;

        /* Whenever we call BeginScene(camera), we want to:
         * Initialize/clear the VertexBuffer to be empty (probably via something like BeginBatch()),
         * Do the same with the IndexBuffer */

        /* Whenever we call DrawQuad(props), we want to:
         * Add the quad to the current QuadVertexBuffer, thus also adjust the buffer's pointer,
         * Adjust the index buffer using a loop */

        /* Calling EndScene() will: 
         * Execute the draw call on the currently bound VertexBuffer and IndexBuffer */

        // Quad
        std::shared_ptr<VertexArray> QuadVertexArray;
        std::shared_ptr<VertexBuffer> QuadVertexBuffer;
        std::shared_ptr<Shader> QuadShader;

        unsigned int QuadIndexCount = 0;
        QuadVertex *QuadVertexBufferBatch = nullptr;
        QuadVertex *QuadVertexBufferCursor = nullptr;

        // Line
        std::shared_ptr<VertexArray> LineVertexArray;
        std::shared_ptr<VertexBuffer> LineVertexBuffer;
        std::shared_ptr<Shader> LineShader;

        // General
        std::shared_ptr<Texture2D> WhiteTexture;
    };

    static RenderData *s_Data;

    void Renderer2D::Initialize()
    {
        // TODO: clean up code
        s_Data = new RenderData;

        s_Data->QuadShader = Shader::FromTextFiles("../Sandbox/assets/shaders/quad.vert.glsl", "../Sandbox/assets/shaders/quad.frag.glsl");
        s_Data->LineShader = Shader::FromTextFiles("../Sandbox/assets/shaders/line.vert.glsl", "../Sandbox/assets/shaders/line.frag.glsl");

        // Create a 1x1 white fallback texture; will load unless we specify a texture in the draw call
        unsigned int white = 0xffffffff;
        s_Data->WhiteTexture = std::make_shared<Texture2D>(1, 1);
        s_Data->WhiteTexture->SetData(&white, sizeof(unsigned int));
        s_Data->WhiteTexture->Bind(0);

        s_Data->QuadVertexBufferBatch = new QuadVertex[s_Data->MaxQuads];
        s_Data->QuadVertexBufferCursor = s_Data->QuadVertexBufferBatch;

        unsigned int *quadIndices = new unsigned int[s_Data->MaxIndices];
        int offset = 0;
        for (int i = 0; i < s_Data->MaxIndices; i += 6)
        {
            quadIndices[i + 0] = 0 + offset;
            quadIndices[i + 1] = 1 + offset;
            quadIndices[i + 2] = 2 + offset;

            quadIndices[i + 3] = 2 + offset;
            quadIndices[i + 4] = 3 + offset;
            quadIndices[i + 5] = 0 + offset;

            offset += 4;
        }
        s_Data->QuadVertexArray = std::make_shared<VertexArray>();
        s_Data->QuadVertexBuffer = std::make_shared<VertexBuffer>(s_Data->MaxVertices);

        BufferLayout quadLayout;
        quadLayout.Push(3);
        quadLayout.Push(4);
        quadLayout.Push(2);

        s_Data->QuadVertexBuffer->SetLayout(quadLayout);
        s_Data->QuadVertexArray->SetIndexBuffer(std::make_shared<IndexBuffer>(quadIndices, s_Data->MaxIndices));
        delete[] quadIndices;
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(std::shared_ptr<const OrthographicCamera> camera)
    {
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetUniformMatrix4fv("u_VP", camera->GetProjectionMatrix() * camera->GetViewMatrix());
        s_Data->QuadShader->SetUniformMatrix4fv("u_Transform", glm::mat4(1.0f));
        s_Data->QuadIndexCount = 0;
        s_Data->QuadVertexBufferCursor = s_Data->QuadVertexBufferBatch;
    }

    // TODO: fix bug that happens when you create one scene after another
    void Renderer2D::EndScene()
    {
        Flush();
    }

    void Renderer2D::Flush()
    {
        // Draw stuff here
        uint32_t dataSize = (uint32_t)((uint8_t *)s_Data->QuadVertexBufferCursor - (uint8_t *)s_Data->QuadVertexBufferBatch);
        s_Data->QuadVertexArray->Bind();
        s_Data->QuadVertexBuffer->SetData(s_Data->QuadVertexBufferBatch, dataSize);
        s_Data->QuadVertexArray->SetVertexBuffer(s_Data->QuadVertexBuffer);
        s_Data->QuadShader->Bind();
        glDrawElements(GL_TRIANGLES, s_Data->QuadIndexCount, GL_UNSIGNED_INT, nullptr);
    }

    /* For every quad, the default values are vec4(1.0, 1.0, 1.0, 1.0) for color
     * and a 1x1px white texture. One can choose whether they want to use a texture or
     * a solid color by specifying those parameters */
    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        s_Data->QuadVertexBufferCursor->Position = { -0.5f + position.x, -0.5f + position.y, position.z };
        s_Data->QuadVertexBufferCursor->Color = color;
        s_Data->QuadVertexBufferCursor->TextureCoordinates = { 0.0f, 0.0f };
        s_Data->QuadVertexBufferCursor++;

        s_Data->QuadVertexBufferCursor->Position = { 0.5f + position.x, -0.5f + position.y, position.z };
        s_Data->QuadVertexBufferCursor->Color = color;
        s_Data->QuadVertexBufferCursor->TextureCoordinates = { 1.0f, 0.0f };
        s_Data->QuadVertexBufferCursor++;

        s_Data->QuadVertexBufferCursor->Position = { 0.5f + position.x, 0.5f + position.y, position.z };
        s_Data->QuadVertexBufferCursor->Color = color;
        s_Data->QuadVertexBufferCursor->TextureCoordinates = { 1.0f, 1.0f };
        s_Data->QuadVertexBufferCursor++;

        s_Data->QuadVertexBufferCursor->Position = { -0.5f + position.x, 0.5f + position.y, position.z };
        s_Data->QuadVertexBufferCursor->Color = color;
        s_Data->QuadVertexBufferCursor->TextureCoordinates = { 0.0f, 1.0f };
        s_Data->QuadVertexBufferCursor++;

        s_Data->QuadIndexCount += 6;
        // GLsizei count = s_Data->QuadVertexArray->GetIndexBuffer()->GetCount();

        // glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        // s_Data->QuadShader->SetUniform4fv("u_Color", color);
        // s_Data->QuadShader->SetUniformMatrix4fv("u_Transform", transform);
        // s_Data->WhiteTexture->Bind(0);

        // glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, std::shared_ptr<Texture2D> texture, const glm::vec4 &tintColor)
    {
        GLsizei count = s_Data->QuadVertexArray->GetIndexBuffer()->GetCount();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        s_Data->QuadShader->SetUniform4fv("u_Color", tintColor);
        s_Data->QuadShader->SetUniformMatrix4fv("u_Transform", transform);
        texture->Bind(0);

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {
        GLsizei count = s_Data->QuadVertexArray->GetIndexBuffer()->GetCount();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) * 
                              glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        s_Data->QuadShader->SetUniform4fv("u_Color", color);
        s_Data->QuadShader->SetUniformMatrix4fv("u_Transform", transform);
        s_Data->WhiteTexture->Bind(0);

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, std::shared_ptr<Texture2D> texture, const glm::vec4 &tintColor)
    {
        GLsizei count = s_Data->QuadVertexArray->GetIndexBuffer()->GetCount();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) * 
                              glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        s_Data->QuadShader->SetUniform4fv("u_Color", tintColor);
        s_Data->QuadShader->SetUniformMatrix4fv("u_Transform", transform);
        texture->Bind(0);

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    /* Meant for debug, bad performance if used for many draw calls, since
     * we're binding the shader for every drawn line */
    void Renderer2D::DrawLine(const glm::vec3 &positionA, const glm::vec3 &positionB, const glm::vec4 &color)
    {
        // float vertices[] = {
        //     positionA.x, positionA.y, positionA.z,
        //     positionB.x, positionB.y, positionB.z 
        // };

        // s_Data->LineVertexArray->Bind();
        // s_Data->LineVertexArray->SetVertexBuffer(s_Data->LineVertexBuffer);
        // s_Data->LineVertexBuffer->SetData(vertices, sizeof(vertices));

        // s_Data->LineShader->Bind();
        // s_Data->LineShader->SetUniform4fv("u_Color", color);
        // s_Data->LineShader->SetUniformMatrix4fv("u_Transform", glm::mat4(1.0f));
        
        // glDrawArrays(GL_LINES, 0, 2);
        ENG_INFO("We tried to draw a line but the code is disabled");
    }
}