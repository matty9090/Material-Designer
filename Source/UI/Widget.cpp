#include "Widget.hpp"

void FWidget::Draw()
{
    Child->Draw();
}

void FWidget::Update(float dt)
{
    Child->Update(dt);
}