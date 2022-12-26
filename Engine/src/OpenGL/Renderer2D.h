#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Engine
{
    class Renderer2D
    {
    public:
        static void Initialize();
        static void Shutdown();

        static void BeginScene(std::shared_ptr<const OrthographicCamera> camera);
        static void EndScene();
        static void Flush();

        static void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color);
        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);
        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, std::shared_ptr<Texture2D> texture, const glm::vec4 &tintColor = glm::vec4(1.0f));

        static void DrawRotatedQuad(const glm::mat4 &transform, const glm::vec4 &color);
        static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotationRadians, const glm::vec4 &color);
        static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotationRadians, std::shared_ptr<Texture2D> texture, const glm::vec4 &tintColor = glm::vec4(1.0f));

        static void DrawLine(const glm::vec3 &positionA, const glm::vec3 &positionB, const glm::vec4 &color);
    };
}