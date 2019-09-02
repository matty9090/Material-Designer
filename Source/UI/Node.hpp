#pragma once

#include <imgui_node_editor.h>
#include <string>

#include "Core/Pins.hpp"

class FNode
{
public:
    FNode(std::string name, PinList inputs, PinList outputs);
    ~FNode();

    void Draw();

private:
    static int Unique;

    int Id, PinId = 0;
    int Padding = 4;

    std::string Name;

    PinList Inputs;
    PinList Outputs;

    void DrawPin(ImVec2 s, ImVec2 e, int pad);
    void DrawHeader(ImVec2 s, ImVec2 e);
};