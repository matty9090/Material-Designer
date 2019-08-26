#include "UI.hpp"

#include "Services/Log.hpp"
#include "Services/AssetManager.hpp"

#include <imgui.h>

#include "ImGuiDx11.h"
#include "ImGuiWin32.h"

UI::UI(ID3D11DeviceContext* context, HWND hwnd) : Context(context)
{    
    ID3D11Device* device = nullptr;
    context->GetDevice(&device);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(device, context);
}

UI::~UI()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void UI::Render()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    bool open = true;
    ImGui::Begin("Test", &open, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Hello, world %d", 123);
    if (ImGui::Button("Save"))
    {
        // do stuff
    }
    char buf[200] = "Testing...";
    float f = 0.0f;

    ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UI::Update(float dt)
{

}

void UI::Reset()
{

}