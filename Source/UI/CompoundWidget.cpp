#include "NodeWidget.hpp"
#include "Services/Log.hpp"
#include "Services/AssetManager.hpp"

#include <algorithm>

using DirectX::SimpleMath::Vector2;

FCompoundWidget::FCompoundWidget()
{
    
}

void FCompoundWidget::Draw(std::unique_ptr<DirectX::SpriteBatch>& Batch)
{
    std::for_each(Children.begin(), Children.end(), [&Batch](SChildWidget& child) {
        child.Widget->Draw(Batch);
    });
}

void FCompoundWidget::Update(float dt)
{
    std::for_each(Children.begin(), Children.end(), [dt](SChildWidget& child) {
        child.Widget->Update(dt);

        // TODO: implement only for mouse released events
        // auto &bounds = child.Widget->GetBounds();
        // bool isInBounds = bounds.Contains();
    });
}

bool FCompoundWidget::OnChildHover(int mx, int my)
{
    IWidget* child = nullptr;

    if (IntersectsChild(mx, my, &child))
    {
        FLog::Get().Log("Child hovered", FLog::Verbose);
        child->OnHover(mx, my);
    }

    return false;
}

bool FCompoundWidget::OnChildUnHover(int mx, int my)
{
    //FLog::Get().Log("Child unhovered", FLog::Verbose);
    return false;
}

bool FCompoundWidget::OnChildFocus(int mx, int my)
{
    IWidget* child = nullptr;

    if (IntersectsChild(mx, my, &child))
    {
        FLog::Get().Log("Child focused", FLog::Verbose);
        child->OnFocus(mx, my);
    }

    return false;
}

bool FCompoundWidget::OnChildUnFocus(int mx, int my)
{
    //FLog::Get().Log("Child unfocused", FLog::Verbose);
    return false;
}

bool FCompoundWidget::OnChildDragBegin(int mx, int my)
{
    IWidget* child = nullptr;

    if (IntersectsChild(mx, my, &child))
    {
        FLog::Get().Log("Child drag started", FLog::Verbose);
        return child->OnDragBegin(mx, my);
    }

    return false;
}

bool FCompoundWidget::OnChildDragUpdate(int mx, int my)
{
    IWidget* child = nullptr;

    if (IntersectsChild(mx, my, &child))
        child->OnDragUpdate(mx, my);

    return false;
}

bool FCompoundWidget::OnChildDragEnd(int mx, int my)
{
    IWidget* child = nullptr;

    if (IntersectsChild(mx, my, &child))
    {
        FLog::Get().Log("Child drag ended", FLog::Verbose);
        child->OnDragEnd(mx, my);
    }

    return false;
}

bool FCompoundWidget::IntersectsChild(int mx, int my, IWidget** child)
{
    return std::any_of(Children.begin(), Children.end(), [mx, my, &child](SChildWidget& widget) {
        if (widget.Widget->GetBounds().Contains(mx, my))
        {
            *child = widget.Widget.get();
            return true;
        }

        return false;
    });
}

void FCompoundWidget::AddChildWidget(std::unique_ptr<IWidget> widget)
{
    Children.push_back(std::move(widget));
}
