#pragma once

#include <d3d11.h>
#include <vector>
#include <imgui_node_editor.h>

#include "Node.hpp"

class UI
{
public:
    UI(ID3D11DeviceContext* context, HWND hwnd);
    ~UI();

    void Render();
    void Update(float dt);
    void Reset();

private:
    FNode TestNode;

    bool FirstFrame = true;
    ax::NodeEditor::EditorContext* NodeContext = nullptr;
};