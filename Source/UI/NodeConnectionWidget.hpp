#pragma once

#include "Widget.hpp"

#include <map>
#include <string>
#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>

namespace DirectX
{
    class SpriteFont;
}

class FNodeConnectionWidget : public IWidget
{
public:
    FNodeConnectionWidget(IWidget* parent, std::string lbl = "");

    void Draw(std::unique_ptr<DirectX::SpriteBatch>& Batch) override;
    void Update(float dt) override;
    void SetPosition(int x, int y) override;

    bool OnDragBegin(int mx, int my) { return false; }

    DirectX::SimpleMath::Rectangle GetBounds() override;

private:
    DirectX::SimpleMath::Vector2 LocalPosition;
    DirectX::SimpleMath::Rectangle Bounds;

    int Padding;
    unsigned int ConWidth;

    std::string Label;
    DirectX::SpriteFont* Font;

    enum EState
    {
        Idle,
        Hovered
    };

    EState State = Idle;
    std::map<EState, ID3D11ShaderResourceView*> Textures;
};