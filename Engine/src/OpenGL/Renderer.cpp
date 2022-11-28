#include "Renderer.h"

namespace Engine
{
    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::Draw(unsigned int count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
}