#include "WidgetFactory.hpp"

#include "NodeWidget.hpp"
#include "TextWidget.hpp"

std::unique_ptr<IWidget> FWidgetFactory::CreateNodeWidget()
{
    return std::make_unique<FNodeWidget>(Context);
}

std::unique_ptr<IWidget> FWidgetFactory::CreateTextWidget(IWidget* parent, std::string txt)
{
    return std::make_unique<FTextWidget>(parent, txt);
}
