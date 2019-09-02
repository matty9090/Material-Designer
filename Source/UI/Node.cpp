#include "Node.hpp"

#include <imgui.h>
#include <utility>

namespace Ed = ax::NodeEditor;

int FNode::Unique = 1;

FNode::FNode(std::string name, PinList inputs, PinList outputs)
    : Name(name),
      Inputs(inputs),
      Outputs(outputs)
{
    Id = Unique;
    Unique += Inputs.size() + Outputs.size();
}

FNode::~FNode()
{

}

void FNode::DrawPin(ImVec2 s, ImVec2 e, int pad)
{
    auto dl = Ed::GetNodeBackgroundDrawList(Id);

    auto centre = s;
    centre.x += pad;
    centre.y = (s.y + e.y) / 2;

    dl->AddCircleFilled(centre, 6.0f, IM_COL32(0, 0, 0, 255));
    dl->AddCircle(centre, 6.0f, IM_COL32(60, 60, 60, 255), 12, 2.0f);
}

void FNode::DrawHeader(ImVec2 s, ImVec2 e)
{
    auto dl = Ed::GetNodeBackgroundDrawList(Id);

    dl->AddRectFilledMultiColor(s, e, IM_COL32(0, 255, 40, 255), IM_COL32(0, 255, 40, 100),
                                      IM_COL32(0, 255, 40, 100), IM_COL32(0, 255, 40, 100));
}

void FNode::Draw()
{
    PinId = Id;

    ImVec2 headerStart, headerEnd;

    std::vector<std::pair<ImVec2, ImVec2>> inputRects;
    std::vector<std::pair<ImVec2, ImVec2>> outputRects;

    Ed::BeginNode(Id);
        ImGui::BeginVertical("Node");
            ImGui::BeginHorizontal("Header");
                ImGui::Text(Name.c_str());
            ImGui::EndHorizontal();

            headerStart = ImGui::GetItemRectMin();
            headerEnd = ImGui::GetItemRectMax();
            
            ImGui::BeginHorizontal("Content");
                ImGui::BeginVertical("Inputs");

                    for (const auto& input : Inputs)
                    {
                        Ed::BeginPin(++PinId, Ed::PinKind::Input);

                        ImGui::BeginHorizontal(PinId);
                            ImGui::Spring(0.0f, 15.0f);
                            ImGui::Text(input.Name.c_str());
                        ImGui::EndHorizontal();

                        inputRects.push_back(std::make_pair(
                            ImGui::GetItemRectMin(),
                            ImGui::GetItemRectMax())
                        );

                        Ed::EndPin();
                    }

                ImGui::EndVertical();
                ImGui::BeginVertical("Outputs");

                    for (const auto& output : Outputs)
                    {
                        Ed::BeginPin(++PinId, Ed::PinKind::Output);
                
                        ImGui::BeginHorizontal(PinId);
                            ImGui::Text(output.Name.c_str());
                            ImGui::Spring(0.0f, 15.0f);
                        ImGui::EndHorizontal();

                        outputRects.push_back(std::make_pair(
                            ImGui::GetItemRectMin(),
                            ImGui::GetItemRectMax())
                        );

                        Ed::EndPin();
                    }

                 ImGui::EndVertical();
            ImGui::EndHorizontal();
        ImGui::EndVertical();
    Ed::EndNode();

    //DrawHeader(headerStart, headerEnd);

    for(const auto inputRect : inputRects)
        DrawPin(inputRect.first, inputRect.second, Padding);

    for (const auto outputRect : outputRects)
        DrawPin(outputRect.second, outputRect.first, -Padding);
}