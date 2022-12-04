#include "UILayer.h"

#include "Application.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Engine
{
    UILayer::UILayer()
        : Layer("UI Layer")
    {
        ENG_TRACE("Created UI layer");
    }

    UILayer::~UILayer()
    {
        ENG_TRACE("Destroyed UI layer");
    }

    // Renders ImGui data
    void UILayer::OnUpdate()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}