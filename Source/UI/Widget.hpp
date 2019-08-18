#pragma once

#include <memory>

class FWidget
{
public:
    virtual void Draw();
    virtual void Update(float dt);

    virtual void OnHover() {}
    virtual void OnUnHover() {}

    virtual void OnFocus() {}
    virtual void OnUnFocus() {}

    virtual void OnDragBegin() {}
    virtual void OnDragEnd() {}
    
protected:
    std::unique_ptr<FWidget> Child;
};