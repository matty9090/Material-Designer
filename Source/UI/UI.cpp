#include "UI.hpp"
#include "WidgetFactory.hpp"

#include "Services/Log.hpp"
#include "Services/AssetManager.hpp"

#include <algorithm>
#include <d3d11.h>
#include <SimpleMath.h>

using DirectX::SimpleMath::Vector2;
using ButtonState = DirectX::Mouse::ButtonStateTracker::ButtonState;

UI::UI(ID3D11DeviceContext* context, HWND hwnd) : Context(context), WidgetFactory(context)
{
    FAssetManager::Get().LoadFont("NodeTitle", L"Fonts/arial14.font");
    Font = FAssetManager::Get().GetFont("NodeTitle");

    Mouse = std::make_unique<DirectX::Mouse>();
    Mouse->SetWindow(hwnd);

    Batch = std::make_unique<DirectX::SpriteBatch>(context);
    Background = FAssetManager::Get().GetTexture("Background");

    Widgets.push_back(SWidget(std::move(WidgetFactory.CreateNodeWidget())));

    ID3D11Device* device = nullptr;
    context->GetDevice(&device);

    States = std::make_unique<DirectX::CommonStates>(device);
}

void UI::Render()
{
    Batch->Begin(DirectX::SpriteSortMode_Deferred, States->NonPremultiplied());
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
            widget.IsHovered = true, widget.Widget->OnHover(mouse.x, mouse.y);

        if (widget.IsHovered && !isInBounds)
            widget.IsHovered = false, widget.Widget->OnUnHover(mouse.x, mouse.y);

        if (Tracker.leftButton == ButtonState::PRESSED && isInBounds)
            widget.IsFocused = true, widget.Widget->OnFocus(mouse.x, mouse.y);

        if (Tracker.leftButton == ButtonState::RELEASED && !isInBounds && widget.IsFocused)
            widget.IsFocused = false, widget.Widget->OnUnFocus(mouse.x, mouse.y);

        if (Tracker.leftButton == ButtonState::HELD && isInBounds && !widget.IsDragging)
            widget.IsDragging = widget.Widget->OnDragBegin(mouse.x, mouse.y);

        if (Tracker.leftButton == ButtonState::RELEASED && widget.IsDragging)
            widget.IsDragging = false,  widget.Widget->OnDragEnd(mouse.x, mouse.y);

        if (widget.IsDragging)
            widget.Widget->OnDragUpdate(mouse.x, mouse.y);
    });
}

void UI::Reset()
{
    Batch.reset();
}