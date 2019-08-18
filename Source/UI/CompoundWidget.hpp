#pragma once

#include "Widget.hpp"

#include <vector>
#include <memory>

#include <d3d11.h>
#include <Mouse.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>

class FCompoundWidget : public IWidget
{
public:
    FCompoundWidget();

    void Draw(std::unique_ptr<DirectX::SpriteBatch>& Batch) override;
    void Update(float dt) override;

    void AddChildWidget(std::unique_ptr<IWidget> widget);

protected:
    bool OnChildHover(int mx, int my);
    bool OnChildUnHover(int mx, int my);

    bool OnChildFocus(int mx, int my);
    bool OnChildUnFocus(int mx, int my);

    bool OnChildDragBegin(int mx, int my);
    bool OnChildDragUpdate(int mx, int my);
    bool OnChildDragEnd(int mx, int my);

private:
    struct SChildWidget
    {
        bool IsHovered = false;
        bool IsFocused = false;
        bool IsDragging = false;

        std::unique_ptr<IWidget> Widget;

        SChildWidget(std::unique_ptr<IWidget> widget) : Widget(std::move(widget)) {}
    };

    std::vector<SChildWidget> Children;

    bool IntersectsChild(int mx, int my, IWidget** child);
};