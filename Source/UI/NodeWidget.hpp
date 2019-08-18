#pragma once

#include "CompoundWidget.hpp"

#include <map>
#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>

class FNodeWidget : public FCompoundWidget
{
public:
    FNodeWidget(ID3D11DeviceContext* context);

    void Draw(std::unique_ptr<DirectX::SpriteBatch>& Batch) final;
    void Update(float dt) final;
    void SetPosition(int x, int y) final;

    void OnHover(int mx, int my) final;
    void OnUnHover(int mx, int my) final;

    void OnFocus(int mx, int my) final;
    void OnUnFocus(int mx, int my) final;

    bool OnDragBegin(int mx, int my) final;
    void OnDragUpdate(int mx, int my) final;
    void OnDragEnd(int mx, int my) final;

    DirectX::SimpleMath::Rectangle GetBounds() final;

private:
    enum EState
    {
        Idle,
        Focused,
        Hovered
    };

    EState State = Idle;

    ID3D11DeviceContext* Context;
    std::map<EState, std::pair<ID3D11ShaderResourceView*, ID3D11ShaderResourceView*>> TextureMatrix;

    unsigned int TopHeight;
    DirectX::SimpleMath::Rectangle Bounds;
    DirectX::SimpleMath::Vector2 DragOffset;
};