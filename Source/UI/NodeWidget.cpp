#include "NodeWidget.hpp"
#include "WidgetFactory.hpp"

#include "Services/Log.hpp"
#include "Services/AssetManager.hpp"

using DirectX::SimpleMath::Vector2;

FNodeWidget::FNodeWidget(ID3D11DeviceContext* context) : Context(context)
{
    unsigned int width, bottomHeight;

    FAssetManager::Get().LoadTexture("NodeTop"     , L"Img/node_top.png");
    FAssetManager::Get().LoadTexture("NodeTopHover", L"Img/node_top_hover.png");
    FAssetManager::Get().LoadTexture("NodeTopFocus", L"Img/node_top_focus.png");
    FAssetManager::Get().LoadTexture("NodeBtm"     , L"Img/node_bottom.png");
    FAssetManager::Get().LoadTexture("NodeBtmHover", L"Img/node_bottom_hover.png");
    FAssetManager::Get().LoadTexture("NodeBtmFocus", L"Img/node_bottom_focus.png");

    TextureMatrix[Idle] = {
        FAssetManager::Get().GetTexture("NodeTop", width, TopHeight),
        FAssetManager::Get().GetTexture("NodeBtm", width, bottomHeight)
    };

    TextureMatrix[Hovered] = {
        FAssetManager::Get().GetTexture("NodeTopHover"),
        FAssetManager::Get().GetTexture("NodeBtmHover")
    };

    TextureMatrix[Focused] = {
        FAssetManager::Get().GetTexture("NodeTopFocus"),
        FAssetManager::Get().GetTexture("NodeBtmFocus")
    };

    Bounds.width  = static_cast<long>(width);
    Bounds.height = static_cast<long>(TopHeight + bottomHeight);

    FWidgetFactory factory(context);
    
    auto txtWidget = factory.CreateTextWidget(this, "Node");
    txtWidget->SetPosition(10, 8);

    AddChildWidget(std::move(txtWidget));
}

void FNodeWidget::Draw(std::unique_ptr<DirectX::SpriteBatch>& Batch)
{
    auto pos = Vector2(static_cast<float>(Bounds.x), static_cast<float>(Bounds.y));
    Batch->Draw(TextureMatrix[State].first, pos, DirectX::Colors::White);

    pos.y += TopHeight;
    Batch->Draw(TextureMatrix[State].second, pos, DirectX::Colors::White);

    FCompoundWidget::Draw(Batch);
}

void FNodeWidget::Update(float dt)
{
    FCompoundWidget::Update(dt);
}

void FNodeWidget::SetPosition(int x, int y)
{
    Bounds.x = x;
    Bounds.y = y;
}

void FNodeWidget::OnHover(int mx, int my)
{
    State = (State != Focused) ? Hovered : Focused;
    FCompoundWidget::OnChildHover(Bounds.x - mx, Bounds.y - my);
    FLog::Get().Log("Hovered", FLog::Verbose);
}

void FNodeWidget::OnUnHover(int mx, int my)
{
    State = (State != Focused) ? Idle : Focused;
    FLog::Get().Log("Unhovered", FLog::Verbose);
}

void FNodeWidget::OnFocus(int mx, int my)
{
    State = Focused;
    FCompoundWidget::OnChildFocus(Bounds.x - mx, Bounds.y - my);
    FLog::Get().Log("Focused", FLog::Verbose);
}

void FNodeWidget::OnUnFocus(int mx, int my)
{
    State = Idle;
    FLog::Get().Log("Unfocused", FLog::Verbose);
}

bool FNodeWidget::OnDragBegin(int mx, int my)
{
    if (!FCompoundWidget::OnChildDragBegin(mx, my))
    {
        FLog::Get().Log("Drag started", FLog::Verbose);
        DragOffset = DirectX::SimpleMath::Vector2(static_cast<float>(Bounds.x - mx), static_cast<float>(Bounds.y - my));

        return true;
    }

    return false;
}

void FNodeWidget::OnDragUpdate(int mx, int my)
{
    if (!FCompoundWidget::OnChildDragUpdate(static_cast<int>(DragOffset.x), static_cast<int>(DragOffset.y)))
    {
        SetPosition(mx + static_cast<int>(DragOffset.x), my + static_cast<int>(DragOffset.y));
    }
}

void FNodeWidget::OnDragEnd(int mx, int my)
{
    FLog::Get().Log("Drag ended", FLog::Verbose);
}

DirectX::SimpleMath::Rectangle FNodeWidget::GetBounds()
{
    return Bounds;
}
