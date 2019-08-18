#pragma once

#include "Widget.hpp"

class FDraggableWidget : public FWidget
{
public:
    void Draw() override;
    void Update(float dt) override;

    void OnDragBegin() override;
    void OnDragEnd() override;
    
protected:
    
};