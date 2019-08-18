#include "UI.hpp"
#include "WidgetFactory.hpp"
#include "Services/TextureManager.hpp"

#include <algorithm>
#include <SimpleMath.h>

using DirectX::SimpleMath::Vector2;

UI::UI(ID3D11DeviceContext* context, HWND hwnd) : Context(context)
{
    Mouse = std::make_unique<DirectX::Mouse>();
    Mouse->SetWindow(hwnd);

    Batch = std::make_unique<DirectX::SpriteBatch>(context);
    Background = FTextureManager::Get().GetTexture("Background");
}

void UI::Render()
{
    Batch->Begin();
    Batch->Draw(Background, Vector2(0.0f, 0.0f), DirectX::Colors::White);

    std::for_each(Widgets.begin(), Widgets.end(), [](std::unique_ptr<FWidget>& widget) {
        widget->Draw();
    });

    Batch->End();
}

void UI::Update(float dt)
{
    std::for_each(Widgets.begin(), Widgets.end(), [dt](std::unique_ptr<FWidget>& widget) {
        widget->Update(dt);
    });
}

void UI::Reset()
{
    Batch.reset();
}