#pragma once

#include <d3d11.h>
#include <imgui_node_editor.h>

class UI
{
public:
    UI(ID3D11DeviceContext* context, HWND hwnd);
    ~UI();

    void Render();
    void Update(float dt);
    void Reset();

private:
    ax::NodeEditor::EditorContext* NodeContext = nullptr;
};