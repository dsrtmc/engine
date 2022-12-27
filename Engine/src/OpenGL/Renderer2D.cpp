#include "Renderer2D.h"

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
        float TextureIndex;
    };

    struct LineVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
    };

    struct RenderData
    {
        static constexpr unsigned int MaxQuads = 10000;
        static constexpr unsigned int MaxVertices = MaxQuads * 4;
        static constexpr unsigned int MaxIndices = MaxQuads * 6;
        static constexpr unsigned int MaxTextureSlots = 16; // TODO: check what the target machine has available

        /* Quad */

        // We use a 4D vector, so we can multiply it with a 4D matrix
        glm::vec4 QuadDefaultPositions[4];
        glm::vec2 QuadTextureCoordinates[4];

        std::shared_ptr<VertexArray> QuadVertexArray;
        std::shared_ptr<VertexBuffer> QuadVertexBuffer;
        std::shared_ptr<Shader> QuadShader;

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

        /* General */
        std::shared_ptr<Texture2D> WhiteTexture;
        std::array<std::shared_ptr<Texture2D>, MaxTextureSlots> TextureSlots;
        unsigned int CurrentTextureIndex = 1; // 0 - white texture
    };

    static RenderData *s_Data;

    void Renderer2D::Initialize()
    {
        s_Data = new RenderData;

        s_Data->QuadShader = Shader::FromTextFiles("../../Sandbox/assets/shaders/quad.vert.glsl", "../../Sandbox/assets/shaders/quad.frag.glsl");
        s_Data->LineShader = Shader::FromTextFiles("../../Sandbox/assets/shaders/line.vert.glsl", "../../Sandbox/assets/shaders/line.frag.glsl");

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

        s_Data->QuadVertexBufferBatch = new QuadVertex[RenderData::MaxVertices];
        s_Data->QuadVertexBufferCursor = s_Data->QuadVertexBufferBatch;

        s_Data->QuadVertexArray = std::make_shared<VertexArray>();
        s_Data->QuadVertexBuffer = std::make_shared<VertexBuffer>(RenderData::MaxVertices * sizeof(QuadVertex));

        s_Data->QuadVertexBuffer->SetLayout(BufferLayout({
            {3, "a_Position"},
            {4, "a_Color"},
            {2, "a_TextureCoordinates"},
            {1, "a_TextureIndex"}
        }));

        auto *quadIndices = new unsigned int[RenderData::MaxIndices];
        int offset = 0;
        for (int i = 0; i < RenderData::MaxIndices; i += 6)
        {
            quadIndices[i + 0] = 0 + offset;
            quadIndices[i + 1] = 1 + offset;
            quadIndices[i + 2] = 2 + offset;

            quadIndices[i + 3] = 2 + offset;
            quadIndices[i + 4] = 3 + offset;
            quadIndices[i + 5] = 0 + offset;

            offset += 4;
        }
        s_Data->QuadVertexArray->SetIndexBuffer(std::make_shared<IndexBuffer>(quadIndices, RenderData::MaxIndices));
        delete[] quadIndices;

        s_Data->TextureSlots[0] = s_Data->WhiteTexture;

        int samplers[RenderData::MaxTextureSlots];
        for (int i = 0; i < RenderData::MaxTextureSlots; i++)
            samplers[i] = i;
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetUniform1iv("u_Textures", samplers, RenderData::MaxTextureSlots);

        /* Line */
        s_Data->LineVertexBufferBatch = new LineVertex[RenderData::MaxVertices];
        s_Data->LineVertexBufferCursor = s_Data->LineVertexBufferBatch;

        s_Data->LineVertexArray = std::make_shared<VertexArray>();
        s_Data->LineVertexBuffer = std::make_shared<VertexBuffer>(RenderData::MaxVertices * sizeof(LineVertex));

        s_Data->LineVertexBuffer->SetLayout(BufferLayout({
            {3, "a_Position"},
            {4, "a_Color"}
        }));
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data->QuadVertexBufferBatch;
        delete s_Data->LineVertexBufferBatch;
        delete s_Data;
    }

    void Renderer2D::StartBatch()
    {
        s_Data->QuadIndexCount = 0;
        s_Data->QuadVertexBufferCursor = s_Data->QuadVertexBufferBatch;

        s_Data->LineVertexCount = 0;
        s_Data->LineVertexBufferCursor = s_Data->LineVertexBufferBatch;
    }

    void Renderer2D::NextBatch()
    {
        Flush();
        StartBatch();
    }

    void Renderer2D::BeginScene(std::shared_ptr<const OrthographicCamera> camera)
    {
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetUniformMatrix4fv("u_VP", camera->GetProjectionMatrix() * camera->GetViewMatrix());
        s_Data->QuadShader->SetUniformMatrix4fv("u_Transform", glm::mat4(1.0f));

        s_Data->LineShader->Bind();
        s_Data->LineShader->SetUniformMatrix4fv("u_VP", camera->GetProjectionMatrix() * camera->GetViewMatrix());
        s_Data->LineShader->SetUniformMatrix4fv("u_Transform", glm::mat4(1.0f));
        StartBatch();
    }

    void Renderer2D::EndScene()
    {
        Flush();
    }

    void Renderer2D::Flush()
    {
        if (s_Data->QuadIndexCount)
        {
            for (int i = 0; i < s_Data->CurrentTextureIndex; i++)
                s_Data->TextureSlots[i]->Bind(i);

            uint32_t dataSize = (uint8_t *)s_Data->QuadVertexBufferCursor - (uint8_t *)s_Data->QuadVertexBufferBatch;
            s_Data->QuadVertexArray->Bind();
            s_Data->QuadVertexBuffer->SetData(s_Data->QuadVertexBufferBatch, dataSize);
            s_Data->QuadVertexArray->SetVertexBuffer(s_Data->QuadVertexBuffer);
            s_Data->QuadShader->Bind();
            glDrawElements(GL_TRIANGLES, s_Data->QuadIndexCount, GL_UNSIGNED_INT, nullptr);
        }

        if (s_Data->LineVertexCount)
        {
            uint32_t dataSize = (uint8_t *)s_Data->LineVertexBufferCursor - (uint8_t *)s_Data->LineVertexBufferBatch;
            s_Data->LineVertexArray->Bind();
            s_Data->LineVertexBuffer->SetData(s_Data->LineVertexBufferBatch, dataSize);
            s_Data->LineVertexArray->SetVertexBuffer(s_Data->LineVertexBuffer);
            s_Data->LineShader->Bind();
            glDrawArrays(GL_LINES, 0, s_Data->LineVertexCount);
        }
    }

    void Renderer2D::DrawQuad(const glm::mat4 &transform, const glm::vec4 &color)
    {
        // TODO: try to find a way to avoid having to write those 2 lines on every draw function
        if (s_Data->QuadIndexCount >= RenderData::MaxIndices)
            NextBatch();

        for (int i = 0; i < 4; i++)
        {
            s_Data->QuadVertexBufferCursor->Position = transform * s_Data->QuadDefaultPositions[i];
            s_Data->QuadVertexBufferCursor->Color = color;
            s_Data->QuadVertexBufferCursor->TextureCoordinates = s_Data->QuadTextureCoordinates[i];
            s_Data->QuadVertexBufferCursor->TextureIndex = 0.0f;
            s_Data->QuadVertexBufferCursor++;
        }
        s_Data->QuadIndexCount += 6;
    }

    void Renderer2D::DrawQuad(const glm::mat4 &transform, std::shared_ptr<Texture2D> texture, const glm::vec4 &tintColor)
    {
        if (s_Data->QuadIndexCount >= RenderData::MaxIndices)
            NextBatch();

        float textureIndex = 0.0f;
        for (int i = 1; i < s_Data->CurrentTextureIndex; i++)
        {
            if (s_Data->TextureSlots[i]->GetRendererID() == texture->GetRendererID())
            {
                textureIndex = (float)i;
                break;
            }
        }
        if (textureIndex == 0.0f)
        {
            s_Data->TextureSlots[s_Data->CurrentTextureIndex] = texture;
            s_Data->CurrentTextureIndex++;
        }
        for (int i = 0; i < 4; i++)
        {
            s_Data->QuadVertexBufferCursor->Position = transform * s_Data->QuadDefaultPositions[i];
            s_Data->QuadVertexBufferCursor->Color = tintColor;
            s_Data->QuadVertexBufferCursor->TextureCoordinates = s_Data->QuadTextureCoordinates[i];
            s_Data->QuadVertexBufferCursor->TextureIndex = textureIndex;
            s_Data->QuadVertexBufferCursor++;
        }
        s_Data->QuadIndexCount += 6;
    }

    /* Should be used the most for regular quads since that's the most performant function */
    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        if (s_Data->QuadIndexCount >= RenderData::MaxIndices)
            NextBatch();
        /* TextureCoordinates help us determine which corner we are in:
         * (0, 0) is bottom-left, (1, 0) is bottom-right etc., thus we can use current vertex's
         * texture coordinate to know whether we should modify the position by the given size */
        for (auto &QuadTextureCoordinate : s_Data->QuadTextureCoordinates)
        {
            s_Data->QuadVertexBufferCursor->Position = {
                position.x - (size.x / 2) + QuadTextureCoordinate.x * size.x,
                position.y - (size.y / 2) + QuadTextureCoordinate.y * size.y,
                position.z
            };
            s_Data->QuadVertexBufferCursor->Color = color;
            s_Data->QuadVertexBufferCursor->TextureCoordinates = QuadTextureCoordinate;
            s_Data->QuadVertexBufferCursor->TextureIndex = 0.0f;
            s_Data->QuadVertexBufferCursor++;
        }
        s_Data->QuadIndexCount += 6;
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, std::shared_ptr<Texture2D> texture, const glm::vec4 &tintColor)
    {
        if (s_Data->QuadIndexCount >= RenderData::MaxIndices)
            NextBatch();

        float textureIndex = 0.0f;
        for (int i = 1; i < s_Data->CurrentTextureIndex; i++)
        {
            if (s_Data->TextureSlots[i]->GetRendererID() == texture->GetRendererID())
            {
                textureIndex = (float)i;
                break;
            }
        }
        if (textureIndex == 0.0f)
        {
            s_Data->TextureSlots[s_Data->CurrentTextureIndex] = texture;
            s_Data->CurrentTextureIndex++;
        }
        for (auto &QuadTextureCoordinate : s_Data->QuadTextureCoordinates)
        {
            s_Data->QuadVertexBufferCursor->Position = {
                    position.x - (size.x / 2) + QuadTextureCoordinate.x * size.x,
                    position.y - (size.y / 2) + QuadTextureCoordinate.y * size.y,
                    position.z
            };
            s_Data->QuadVertexBufferCursor->Color = tintColor;
            s_Data->QuadVertexBufferCursor->TextureCoordinates = QuadTextureCoordinate;
            s_Data->QuadVertexBufferCursor->TextureIndex = textureIndex;
            s_Data->QuadVertexBufferCursor++;
        }
        s_Data->QuadIndexCount += 6;
    }

    /* Bad performance if called a lot of times, avoid big batches of rotated quads unless we somehow improve the transform */
    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotationRadians, const glm::vec4 &color)
    {
        if (s_Data->QuadIndexCount >= RenderData::MaxIndices)
            NextBatch();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), rotationRadians, glm::vec3(0.0f, 0.0f, 1.0f)) *
                              glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
        DrawQuad(transform, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotationRadians, std::shared_ptr<Texture2D> texture, const glm::vec4 &tintColor)
    {
        if (s_Data->QuadIndexCount >= RenderData::MaxIndices)
            NextBatch();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), rotationRadians, glm::vec3(0.0f, 0.0f, 1.0f)) *
                              glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
        DrawQuad(transform, texture, tintColor);
    }

    void Renderer2D::DrawLine(const glm::vec3 &positionA, const glm::vec3 &positionB, const glm::vec4 &color)
    {
        if (s_Data->LineVertexCount >= RenderData::MaxVertices)
            NextBatch();

        s_Data->LineVertexBufferCursor->Position = positionA;
        s_Data->LineVertexBufferCursor->Color = color;
        s_Data->LineVertexBufferCursor++;

        s_Data->LineVertexBufferCursor->Position = positionB;
        s_Data->LineVertexBufferCursor->Color = color;
        s_Data->LineVertexBufferCursor++;

        s_Data->LineVertexCount += 2;
    }
}