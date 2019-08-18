#include "WidgetFactory.hpp"
#include "NodeWidget.hpp"

std::unique_ptr<IWidget> FWidgetFactory::CreateNodeWidget()
{
    return std::make_unique<FNodeWidget>(Context);
}