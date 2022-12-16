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

        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);
        // static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, const glm::mat4 &transform);
        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, std::shared_ptr<Texture2D> texture);
        // static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, std::shared_ptr<Texture2D> texture, const glm::mat4 &transform);
    };
}