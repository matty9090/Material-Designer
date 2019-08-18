#include "NodeWidget.hpp"
#include "Services/Log.hpp"
#include "Services/TextureManager.hpp"

using DirectX::SimpleMath::Vector2;

FNodeWidget::FNodeWidget(ID3D11DeviceContext* context) : Context(context)
{
    unsigned int width, height;

    FTextureManager::Get().LoadTexture("Node", L"node.png");
    Texture = FTextureManager::Get().GetTexture("Node", width, height);

    Bounds.width = static_cast<long>(width);
    Bounds.height = static_cast<long>(height);
}

void FNodeWidget::Draw(std::unique_ptr<DirectX::SpriteBatch>& Batch)
{
    auto pos = Vector2(static_cast<float>(Bounds.x), static_cast<float>(Bounds.y));
    Batch->Draw(Texture, pos, DirectX::Colors::White);
}

void FNodeWidget::Update(float dt)
{
    
}

void FNodeWidget::SetPosition(int x, int y)
{
    Bounds.x = x;
    Bounds.y = y;
}

void FNodeWidget::OnHover()
{
    FLog::Get().Log("Hovered", FLog::Verbose);
}

void FNodeWidget::OnUnHover()
{
    FLog::Get().Log("Unhovered", FLog::Verbose);
}

void FNodeWidget::OnFocus()
{
    FLog::Get().Log("Focused", FLog::Verbose);
}

void FNodeWidget::OnUnFocus()
{
    FLog::Get().Log("Unfocused", FLog::Verbose);
}

void FNodeWidget::OnDragBegin(int mx, int my)
{
    DragOffset = DirectX::SimpleMath::Vector2(static_cast<float>(Bounds.x - mx), static_cast<float>(Bounds.y - my));
    FLog::Get().Log("Drag started", FLog::Verbose);
}

void FNodeWidget::OnDragUpdate(int mx, int my)
{
    SetPosition(mx + static_cast<int>(DragOffset.x), my + static_cast<int>(DragOffset.y));
}

void FNodeWidget::OnDragEnd()
{
    FLog::Get().Log("Drag ended", FLog::Verbose);
}

DirectX::SimpleMath::Rectangle FNodeWidget::GetBounds()
{
    return Bounds;
}
