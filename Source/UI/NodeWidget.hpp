#pragma once

#include "DraggableWidget.hpp"

class FNodeWidget : public FDraggableWidget
{
public:
	FNodeWidget();

	void Draw() override;
	void Update(float dt) override;

protected:

};