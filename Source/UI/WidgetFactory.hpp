#pragma once

#include "Widget.hpp"

#include <d3d11.h>
#include <string>

class FWidgetFactory
{
public:
    FWidgetFactory(ID3D11DeviceContext* context) : Context(context) {}

    std::unique_ptr<IWidget> CreateNodeWidget();
    std::unique_ptr<IWidget> CreateTextWidget(IWidget* parent, std::string txt = "");
    std::unique_ptr<IWidget> CreateNodeConnectionWidget(IWidget* parent, std::string txt = "");

private:
    ID3D11DeviceContext* Context;
};