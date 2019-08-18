#include "NodeWidget.hpp"

FNodeWidget::FNodeWidget() : FDraggableWidget()
{

}

void FNodeWidget::Draw()
{
    FDraggableWidget::Draw();
}

void FNodeWidget::Update(float dt)
{
    FDraggableWidget::Update(dt);
}
