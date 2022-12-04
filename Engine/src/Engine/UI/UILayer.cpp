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
        // TODO: move to OnAttach() if added
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags)
        {
            style.WindowRounding = 10.0f;
        }
        // Filepath relative from /build/
        io.Fonts->AddFontFromFileTTF("../Sandbox/assets/fonts/SFProDisplay/SFPRODISPLAYMEDIUM.OTF", 15);

        ImGui_ImplOpenGL3_Init("#version 330");
    }

    UILayer::~UILayer()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        ENG_TRACE("Destroyed UI layer");
    }

    // // Renders ImGui data
    // void UILayer::OnUpdate()
    // {
    //     ImGui::Render();
    //     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // }

    void UILayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void UILayer::End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}