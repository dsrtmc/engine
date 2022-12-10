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

        // Filepath relative from /build/
        io.Fonts->AddFontFromFileTTF("../Sandbox/assets/fonts/opensans/OpenSans-Regular.ttf", 16.5);

        ImGui_ImplGlfw_InitForOpenGL(Application::Get()->GetWindow()->GetNativeWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    UILayer::~UILayer()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        ENG_TRACE("Destroyed UI layer");
    }

    void UILayer::OnImGuiUpdate()
    {
        ImGui::Begin("main UI window");
        ImGui::Text("that is text from the main ui");
        ImGui::End();
    }

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