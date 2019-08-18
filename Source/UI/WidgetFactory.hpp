#pragma once

#include "Widget.hpp"
#include <d3d11.h>

class FWidgetFactory
{
public:
    FWidgetFactory(ID3D11DeviceContext* context) : Context(context) {}

    std::unique_ptr<IWidget> CreateNodeWidget();

private:
    ID3D11DeviceContext* Context;
};