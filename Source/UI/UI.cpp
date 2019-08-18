#include "UI.hpp"
#include "WidgetFactory.hpp"
#include "Services/TextureManager.hpp"

#include "SimpleMath.h"

using DirectX::SimpleMath::Vector2;

UI::UI(ID3D11DeviceContext* context) : Context(context)
{
	Batch = std::make_unique<DirectX::SpriteBatch>(context);
	Background = FTextureManager::Get().GetTexture("Background");
}

void UI::Render()
{
	Batch->Begin();
	Batch->Draw(Background, Vector2(0.0f, 0.0f), DirectX::Colors::White);
	Batch->End();
}

void UI::Update(float dt)
{

}

void UI::Reset()
{
	Batch.reset();
}