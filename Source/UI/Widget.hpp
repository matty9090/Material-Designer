#pragma once

#include <memory>

namespace DirectX
{
    class SpriteBatch;

    namespace SimpleMath
    {
        struct Rectangle;
    }
}

class IWidget
{
public:
    virtual void Draw(std::unique_ptr<DirectX::SpriteBatch>& Batch) = 0;
    virtual void Update(float dt) = 0;
    virtual void SetPosition(int x, int y) = 0;

    virtual void OnHover() {}
    virtual void OnUnHover() {}

    virtual void OnFocus() {}
    virtual void OnUnFocus() {}

    virtual void OnDragBegin(int mx, int my) {}
    virtual void OnDragUpdate(int mx, int my) {}
    virtual void OnDragEnd() {}

    virtual DirectX::SimpleMath::Rectangle GetBounds() = 0;
};