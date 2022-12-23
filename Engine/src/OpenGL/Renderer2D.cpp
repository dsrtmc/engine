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

    struct LineVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
    };

    struct RenderData
    {
        const unsigned int MaxQuads = 10000;
        const unsigned int MaxVertices = MaxQuads * 4;
        const unsigned int MaxIndices = MaxQuads * 6;

        /* Quad */
        std::shared_ptr<VertexArray> QuadVertexArray;
        std::shared_ptr<VertexBuffer> QuadVertexBuffer;
        std::shared_ptr<Shader> QuadShader;

        // We use a 4D vector so we can multiply it with a 4D matrix
        glm::vec4 QuadDefaultPositions[4];
        glm::vec2 QuadTextureCoordinates[4];

        unsigned int QuadIndexCount = 0;
        QuadVertex *QuadVertexBufferBatch = nullptr;
        QuadVertex *QuadVertexBufferCursor = nullptr;

        /* Line */
        std::shared_ptr<VertexArray> LineVertexArray;
        std::shared_ptr<VertexBuffer> LineVertexBuffer;
        std::shared_ptr<Shader> LineShader;

        unsigned int LineVertexCount = 0;
        LineVertex *LineVertexBufferBatch = nullptr;
        LineVertex *LineVertexBufferCursor = nullptr;

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

        /* Quad */
        s_Data->QuadDefaultPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        s_Data->QuadDefaultPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
        s_Data->QuadDefaultPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
        s_Data->QuadDefaultPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
        s_Data->QuadTextureCoordinates[0] = { 0.0f, 0.0f };
        s_Data->QuadTextureCoordinates[1] = { 1.0f, 0.0f };
        s_Data->QuadTextureCoordinates[2] = { 1.0f, 1.0f };
        s_Data->QuadTextureCoordinates[3] = { 0.0f, 1.0f };

        s_Data->QuadVertexBufferBatch = new QuadVertex[s_Data->MaxVertices];
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
        s_Data->QuadVertexBuffer = std::make_shared<VertexBuffer>(s_Data->MaxVertices * sizeof(QuadVertex));

        BufferLayout quadLayout;
        quadLayout.Push(3);
        quadLayout.Push(4);
        quadLayout.Push(2);

        s_Data->QuadVertexBuffer->SetLayout(quadLayout);
        s_Data->QuadVertexArray->SetIndexBuffer(std::make_shared<IndexBuffer>(quadIndices, s_Data->MaxIndices));
        delete[] quadIndices;

        /* Line */
        s_Data->LineVertexArray = std::make_shared<VertexArray>();
        s_Data->LineVertexBuffer = std::make_shared<VertexBuffer>(s_Data->MaxVertices * sizeof(LineVertex));
        // TODO: Maybe make unique pointers? too much issues with memory leak if delete is not a recursive(?) operator
        s_Data->LineVertexBufferBatch = new LineVertex[s_Data->MaxVertices];
        s_Data->LineVertexBufferCursor = s_Data->LineVertexBufferBatch;
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(std::shared_ptr<const OrthographicCamera> camera)
    {
        ENG_WARN("BEGIN SCENE");
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetUniformMatrix4fv("u_VP", camera->GetProjectionMatrix() * camera->GetViewMatrix());
        s_Data->QuadShader->SetUniformMatrix4fv("u_Transform", glm::mat4(1.0f));
        s_Data->QuadIndexCount = 0;
        s_Data->QuadVertexBufferCursor = s_Data->QuadVertexBufferBatch;

        s_Data->LineShader->Bind();
        s_Data->LineShader->SetUniformMatrix4fv("u_VP", camera->GetProjectionMatrix() * camera->GetViewMatrix());
        s_Data->LineShader->SetUniformMatrix4fv("u_Transform", glm::mat4(1.0f));
        s_Data->LineVertexCount = 0;
        s_Data->LineVertexBufferCursor = s_Data->LineVertexBufferBatch;
    }

    // TODO: fix bug that happens when you create one scene after another
    void Renderer2D::EndScene()
    {
        ENG_WARN("END SCENE");
        ENG_INFO("Line vertexcount RIGHT BEFORE FLUSH: {0}", s_Data->LineVertexCount);
        ENG_INFO("Line count: {0}", s_Data->LineVertexCount);
        Flush();
    }

    void Renderer2D::Flush()
    {
        {
            uint32_t dataSize = (uint8_t *)s_Data->QuadVertexBufferCursor - (uint8_t *)s_Data->QuadVertexBufferBatch;
            s_Data->QuadVertexArray->Bind();
            s_Data->QuadVertexBuffer->SetData(s_Data->QuadVertexBufferBatch, dataSize);
            s_Data->QuadVertexArray->SetVertexBuffer(s_Data->QuadVertexBuffer);
            s_Data->QuadShader->Bind();
            glDrawElements(GL_TRIANGLES, s_Data->QuadIndexCount, GL_UNSIGNED_INT, nullptr);
        }

        {
            uint32_t dataSize = (uint8_t *)s_Data->LineVertexBufferCursor - (uint8_t *)s_Data->LineVertexBufferBatch;
            s_Data->LineVertexArray->Bind();
            s_Data->LineVertexBuffer->SetData(s_Data->LineVertexBufferBatch, dataSize);
            s_Data->LineVertexArray->SetVertexBuffer(s_Data->LineVertexBuffer);
            s_Data->LineShader->Bind();
            // 私がっかりしてます ^_^
            // literally cancer fucking impossible to fix idk why it doesn't work
            glDrawArrays(GL_LINES, 0, s_Data->LineVertexCount);
        }
    }

    /* Should probably only be called directly, rather than by other functions, since recalculating the
    transform matrix every call is really expensive */
    void Renderer2D::DrawQuad(const glm::mat4 &transform, const glm::vec4 &color)
    {
        for (int i = 0; i < 4; i++)
        {
            s_Data->QuadVertexBufferCursor->Position = transform * s_Data->QuadDefaultPositions[i];
            s_Data->QuadVertexBufferCursor->Color = color;
            s_Data->QuadVertexBufferCursor->TextureCoordinates = s_Data->QuadTextureCoordinates[i];
            s_Data->QuadVertexBufferCursor++;
        }
        s_Data->QuadIndexCount += 6;
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        /* TextureCoordinates help us determine which corner we are in:
         * (0, 0) is bottom-left, (1, 0) is bottom-right etc., thus we can use current vertex's
         * texture coordinate to know whether we should modify the position by the given size */
        for (int i = 0; i < 4; i++)
        {
            s_Data->QuadVertexBufferCursor->Position = {
                position.x - (size.x / 2) + s_Data->QuadTextureCoordinates[i].x * size.x,
                position.y - (size.y / 2) + s_Data->QuadTextureCoordinates[i].y * size.y,
                position.z
            };
            s_Data->QuadVertexBufferCursor->Color = color;
            s_Data->QuadVertexBufferCursor->TextureCoordinates = s_Data->QuadTextureCoordinates[i];
            s_Data->QuadVertexBufferCursor++;
        }
        s_Data->QuadIndexCount += 6;
    }

#if OLD_API
    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, std::shared_ptr<Texture2D> texture, const glm::vec4 &tintColor)
    {
        GLsizei count = s_Data->QuadVertexArray->GetIndexBuffer()->GetCount();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        s_Data->QuadShader->SetUniform4fv("u_Color", tintColor);
        s_Data->QuadShader->SetUniformMatrix4fv("u_Transform", transform);
        texture->Bind(0);

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
#endif

    /* The main draw function, which can be called by other overloaded DrawRotatedQuad() functions */
    void Renderer2D::DrawRotatedQuad(const glm::mat4 &transform, const glm::vec4 &color)
    {
        for (int i = 0; i < 4; i++)
        {
            s_Data->QuadVertexBufferCursor->Position = transform * s_Data->QuadDefaultPositions[i];
            s_Data->QuadVertexBufferCursor->Color = color;
            s_Data->QuadVertexBufferCursor->TextureCoordinates = s_Data->QuadTextureCoordinates[i];
            s_Data->QuadVertexBufferCursor++;
        }
        s_Data->QuadIndexCount += 6;
    }

    /* Bad performance if called a lot of times, avoid big batches of rotated quads unless we somehow improve the transform */
    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) *
                              glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
        DrawRotatedQuad(transform, color);
    }

#if OLD_API
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
#endif

    void Renderer2D::DrawLine(const glm::vec3 &positionA, const glm::vec3 &positionB, const glm::vec4 &color)
    {
        s_Data->LineVertexBufferCursor->Position = positionA;
        s_Data->LineVertexBufferCursor->Color = color;
        s_Data->LineVertexBufferCursor++;

        s_Data->LineVertexBufferCursor->Position = positionB;
        s_Data->LineVertexBufferCursor->Color = color;
        s_Data->LineVertexBufferCursor++;

        s_Data->LineVertexCount += 2;
    }
}