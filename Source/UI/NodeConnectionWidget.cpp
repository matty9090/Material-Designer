#include "NodeConnectionWidget.hpp"
#include "Services/AssetManager.hpp"

#include <algorithm>

using DirectX::SimpleMath::Vector2;

FNodeConnectionWidget::FNodeConnectionWidget(IWidget* parent, std::string lbl)
    : IWidget(parent),
      Label(lbl),
      Padding(2)
{
    Font = FAssetManager::Get().GetFont("NodeTitle");

    unsigned int height;

    FAssetManager::Get().LoadTexture("NodeConnection", L"Img/node_connection.png");
    FAssetManager::Get().LoadTexture("NodeConnectionHover", L"Img/node_connection_hover.png");

    Textures[Idle]    = FAssetManager::Get().GetTexture("NodeConnection", ConWidth, height);
    Textures[Hovered] = FAssetManager::Get().GetTexture("NodeConnectionHover");
    
    Vector2 txtSize = Font->MeasureString(lbl.c_str());

    Bounds.width  = static_cast<long>(ConWidth) + static_cast<long>(Padding) + static_cast<long>(txtSize.x);
    Bounds.height = static_cast<long>((std::max)(static_cast<unsigned int>(txtSize.y), height));
}

void FNodeConnectionWidget::Draw(std::unique_ptr<DirectX::SpriteBatch>& Batch)
{
    auto parentBounds = Parent->GetBounds();
    Bounds.x = parentBounds.x + static_cast<long>(LocalPosition.x);
    Bounds.y = parentBounds.y + static_cast<long>(LocalPosition.y);

    auto pos = Vector2(static_cast<float>(Bounds.x), static_cast<float>(Bounds.y));
    Batch->Draw(Textures[State], pos, DirectX::Colors::White);

    pos.x += ConWidth + Padding;
    pos.y -= 2.0f;
    Font->DrawString(Batch.get(), Label.c_str(), pos, DirectX::Colors::White, 0.0f, Vector2::Zero);
}

void FNodeConnectionWidget::Update(float dt)
{
    
}

void FNodeConnectionWidget::SetPosition(int x, int y)
{
    LocalPosition = Vector2(static_cast<float>(x), static_cast<float>(y));
}

DirectX::SimpleMath::Rectangle FNodeConnectionWidget::GetBounds()
{
    return Bounds;
}
