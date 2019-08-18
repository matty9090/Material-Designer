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
    IWidget(IWidget* parent = nullptr) : Parent(parent) {}

    virtual void Draw(std::unique_ptr<DirectX::SpriteBatch>& Batch) = 0;
    virtual void Update(float dt) = 0;
    virtual void SetPosition(int x, int y) = 0;

    virtual void OnHover(int mx, int my) {}
    virtual void OnUnHover(int mx, int my) {}

    virtual void OnFocus(int mx, int my) {}
    virtual void OnUnFocus(int mx, int my) {}

    virtual bool OnDragBegin(int mx, int my) { return false; }
    virtual void OnDragUpdate(int mx, int my) {}
    virtual void OnDragEnd(int mx, int my) {}

    virtual DirectX::SimpleMath::Rectangle GetBounds() = 0;

protected:
    IWidget* Parent = nullptr;
};