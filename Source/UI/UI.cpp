#include "UI.hpp"
#include "WidgetFactory.hpp"

#include "Services/Log.hpp"
#include "Services/TextureManager.hpp"

#include <algorithm>
#include <d3d11.h>
#include <SimpleMath.h>

using DirectX::SimpleMath::Vector2;
using ButtonState = DirectX::Mouse::ButtonStateTracker::ButtonState;

UI::UI(ID3D11DeviceContext* context, HWND hwnd) : Context(context), WidgetFactory(context)
{
    Mouse = std::make_unique<DirectX::Mouse>();
    Mouse->SetWindow(hwnd);

    Batch = std::make_unique<DirectX::SpriteBatch>(context);
    Background = FTextureManager::Get().GetTexture("Background");

    Widgets.push_back(SWidget(std::move(WidgetFactory.CreateNodeWidget())));
}

void UI::Render()
{
    Batch->Begin();
    Batch->Draw(Background, Vector2(0.0f, 0.0f), DirectX::Colors::White);

    std::for_each(Widgets.begin(), Widgets.end(), [this](SWidget& widget) {
        widget.Widget->Draw(Batch);
    });

    Batch->End();
}

void UI::Update(float dt)
{
    auto mouse = Mouse->GetState();
    Tracker.Update(mouse);

    std::for_each(Widgets.begin(), Widgets.end(), [this, dt, mouse](SWidget& widget) {
        widget.Widget->Update(dt);

        auto &bounds = widget.Widget->GetBounds();
        bool isInBounds = bounds.Contains(mouse.x, mouse.y);

        if (!widget.IsHovered && isInBounds)
            widget.IsHovered = true, widget.Widget->OnHover();

        if (widget.IsHovered && !isInBounds)
            widget.IsHovered = false, widget.Widget->OnUnHover();

        if (Tracker.leftButton == ButtonState::PRESSED && isInBounds && !widget.IsFocused)
            widget.IsFocused = true, widget.Widget->OnFocus();

        if (Tracker.leftButton == ButtonState::RELEASED && !isInBounds && widget.IsFocused)
            widget.IsFocused = false, widget.Widget->OnUnFocus();

        if (Tracker.leftButton == ButtonState::HELD && widget.IsFocused && !widget.IsDragging)
            widget.IsDragging = true, widget.Widget->OnDragBegin(mouse.x, mouse.y);

        if (Tracker.leftButton == ButtonState::RELEASED && widget.IsDragging)
            widget.IsDragging = false,  widget.Widget->OnDragEnd();

        if (widget.IsDragging)
            widget.Widget->OnDragUpdate(mouse.x, mouse.y);
    });
}

void UI::Reset()
{
    Batch.reset();
}