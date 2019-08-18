#pragma once

#include <d3d11.h>
#include <SpriteBatch.h>
#include <vector>
#include <Mouse.h>
#include <Mouse.h>

#include "Widget.hpp"
#include "WidgetFactory.hpp"

namespace DirectX
{
    class SpriteFont;
}

class UI
{
public:
    UI(ID3D11DeviceContext* context, HWND hwnd);

    void Render();
    void Update(float dt);
    void Reset();

private:
    ID3D11DeviceContext* Context;
    ID3D11ShaderResourceView* Background;

    struct SWidget
    {
        bool IsHovered = false;
        bool IsFocused = false;
        bool IsDragging = false;

        std::unique_ptr<IWidget> Widget;

        SWidget(std::unique_ptr<IWidget> widget) : Widget(std::move(widget)) {}
    };

    FWidgetFactory WidgetFactory;
    
    DirectX::SpriteFont* Font;
    DirectX::Mouse::ButtonStateTracker Tracker;

    std::unique_ptr<DirectX::Mouse> Mouse;
    std::unique_ptr<DirectX::SpriteBatch> Batch;
    
    std::vector<SWidget> Widgets;
};