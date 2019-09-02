#include "UI.hpp"

#include "Services/Log.hpp"
#include "Services/AssetManager.hpp"

#include "ImGuiDx11.h"
#include "ImGuiWin32.h"

namespace Ed = ax::NodeEditor;

UI::UI(ID3D11DeviceContext* context, HWND hwnd)
    : TestNode("Test", {{ EPin::Float, "Magnitude" }, { EPin::Float, "Op" }}, {{ EPin::Float, "Scaled" }})
{    
    ID3D11Device* device = nullptr;
    context->GetDevice(&device);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(device, context);

    Ed::Config config;
    config.SettingsFile = "Settings.json";
    NodeContext = Ed::CreateEditor(&config);
}

UI::~UI()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    Ed::DestroyEditor(NodeContext);
}

void UI::Render()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);

    ImGui::Begin("Content", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save")) { /* Do stuff */ }
            if (ImGui::MenuItem("Close")) { PostQuitMessage(0); }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    Ed::SetCurrentEditor(NodeContext);
    Ed::Begin("Material Editor", ImVec2(0.0f, 0.0f));
    
    TestNode.Draw();

    Ed::End();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    if (FirstFrame)
        Ed::NavigateToContent(0.0f);

    Ed::SetCurrentEditor(nullptr);
    FirstFrame = false;
}

void UI::Update(float dt)
{

}

void UI::Reset()
{

}