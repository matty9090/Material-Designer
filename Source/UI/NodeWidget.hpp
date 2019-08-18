#pragma once

#include "Widget.hpp"

#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>

class FNodeWidget : public IWidget
{
public:
    FNodeWidget(ID3D11DeviceContext* context);

    void Draw(std::unique_ptr<DirectX::SpriteBatch>& Batch) final;
    void Update(float dt) final;
    void SetPosition(int x, int y) final;

    void OnHover() final;
    void OnUnHover() final;

    void OnFocus() final;
    void OnUnFocus() final;

    void OnDragBegin(int mx, int my) final;
    void OnDragUpdate(int mx, int my) final;
    void OnDragEnd() final;

    DirectX::SimpleMath::Rectangle GetBounds() final;

private:
    ID3D11DeviceContext* Context;
    ID3D11ShaderResourceView *Texture;

    DirectX::SimpleMath::Rectangle Bounds;
    DirectX::SimpleMath::Vector2 DragOffset;
};