#pragma once

#include "Widget.hpp"

#include <string>
#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>

namespace DirectX
{
    class SpriteFont;
}

class FTextWidget : public IWidget
{
public:
    FTextWidget(IWidget* parent, std::string txt = "");

    void Draw(std::unique_ptr<DirectX::SpriteBatch>& Batch) override;
    void Update(float dt) override;
    void SetPosition(int x, int y) override;

    bool OnDragBegin(int mx, int my) { return false; }

    DirectX::SimpleMath::Rectangle GetBounds() override;

private:
    DirectX::SimpleMath::Vector2 LocalPosition;
    DirectX::SimpleMath::Rectangle Bounds;

    std::string Text;
    DirectX::SpriteFont* Font;
};