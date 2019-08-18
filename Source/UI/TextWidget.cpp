#include "TextWidget.hpp"
#include "Services/AssetManager.hpp"

using DirectX::SimpleMath::Vector2;

FTextWidget::FTextWidget(IWidget* parent, std::string txt) : IWidget(parent), Text(txt)
{
    Font = FAssetManager::Get().GetFont("NodeTitle");
    
    Vector2 txtSize = Font->MeasureString(txt.c_str());

    Bounds.width = txtSize.x;
    Bounds.height = txtSize.y;
}

void FTextWidget::Draw(std::unique_ptr<DirectX::SpriteBatch>& Batch)
{
    auto parentBounds = Parent->GetBounds();
    Bounds.x = parentBounds.x + static_cast<long>(LocalPosition.x);
    Bounds.y = parentBounds.y + static_cast<long>(LocalPosition.y);

    auto pos = Vector2(static_cast<float>(Bounds.x), static_cast<float>(Bounds.y));
    Font->DrawString(Batch.get(), Text.c_str(), pos, DirectX::Colors::White, 0.0f, Vector2::Zero);
}

void FTextWidget::Update(float dt)
{
    
}

void FTextWidget::SetPosition(int x, int y)
{
    LocalPosition = Vector2(static_cast<float>(x), static_cast<float>(y));
}

DirectX::SimpleMath::Rectangle FTextWidget::GetBounds()
{
    return Bounds;
}
