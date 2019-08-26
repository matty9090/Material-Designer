#pragma once

#include <d3d11.h>

class UI
{
public:
    UI(ID3D11DeviceContext* context, HWND hwnd);
    ~UI();

    void Render();
    void Update(float dt);
    void Reset();

private:
    ID3D11DeviceContext* Context;
};