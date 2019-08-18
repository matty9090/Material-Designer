#include "WidgetFactory.hpp"

#include "NodeWidget.hpp"
#include "TextWidget.hpp"
#include "NodeConnectionWidget.hpp"

std::unique_ptr<IWidget> FWidgetFactory::CreateNodeWidget()
{
    return std::make_unique<FNodeWidget>(Context);
}

std::unique_ptr<IWidget> FWidgetFactory::CreateTextWidget(IWidget* parent, std::string txt)
{
    return std::make_unique<FTextWidget>(parent, txt);
}

std::unique_ptr<IWidget> FWidgetFactory::CreateNodeConnectionWidget(IWidget* parent, std::string txt)
{
    return std::make_unique<FNodeConnectionWidget>(parent, txt);
}