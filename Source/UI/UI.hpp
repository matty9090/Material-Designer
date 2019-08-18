#pragma once

#include <d3d11.h>
#include <SpriteBatch.h>
#include <vector>
#include <Mouse.h>

#include "Widget.hpp"

class UI
{
public:
    UI(ID3D11DeviceContext* context, HWND hwnd);

    void Render();
    void Update(float dt);
    void Reset();

private:
    ID3D11DeviceContext* Context;
    ID3D11ShaderResourceView* Background;

    std::unique_ptr<DirectX::Mouse> Mouse;
    std::unique_ptr<DirectX::SpriteBatch> Batch;
    std::vector<std::unique_ptr<FWidget>> Widgets;
};