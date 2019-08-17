#pragma once

#include <d3d11.h>
#include <SpriteBatch.h>

class UI
{
public:
	UI(ID3D11DeviceContext* context);

	void Render();
	void Reset();

private:
	ID3D11DeviceContext* Context;
	ID3D11ShaderResourceView* Background;

	std::unique_ptr<DirectX::SpriteBatch> Batch;
};