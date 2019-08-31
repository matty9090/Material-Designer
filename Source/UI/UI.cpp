#include "UI.hpp"

#include "Services/Log.hpp"
#include "Services/AssetManager.hpp"

#include "ImGuiDx11.h"
#include "ImGuiWin32.h"

namespace Node = ax::NodeEditor;

UI::UI(ID3D11DeviceContext* context, HWND hwnd)
{    
    ID3D11Device* device = nullptr;
    context->GetDevice(&device);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(device, context);

    NodeContext = Node::CreateEditor();
}

UI::~UI()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    Node::DestroyEditor(NodeContext);
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

    Node::SetCurrentEditor(NodeContext);
    Node::Begin("My Editor", ImVec2(0.0, 0.0f));
    int uniqueId = 1;
    // Start drawing nodes.
    Node::BeginNode(uniqueId++);
    ImGui::Text("Node A");
    Node::BeginPin(uniqueId++, Node::PinKind::Input);
    ImGui::Text("-> In");
    Node::EndPin();
    ImGui::SameLine();
    Node::BeginPin(uniqueId++, Node::PinKind::Output);
    ImGui::Text("Out ->");
    Node::EndPin();
    Node::EndNode();
    Node::End();
    Node::SetCurrentEditor(nullptr);

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UI::Update(float dt)
{

}

void UI::Reset()
{

}