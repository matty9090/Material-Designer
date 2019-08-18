#pragma once

#include <map>
#include <string>

#include <d3d11.h>
#include <wrl/client.h>
#include <SpriteFont.h>

class FAssetManager
{
public:
    static FAssetManager& Get()
    {
        static FAssetManager instance;
        return instance;
    }

    FAssetManager(FAssetManager const&) = delete;
    void operator=(FAssetManager const&) = delete;

    void Initialize(ID3D11Device* device);

    bool LoadTexture(std::string key, std::wstring file);
    ID3D11ShaderResourceView* GetTexture(std::string key);
    ID3D11ShaderResourceView* GetTexture(std::string key, unsigned int& Width, unsigned int& Height);

    bool LoadFont(std::string key, std::wstring file);
    DirectX::SpriteFont* GetFont(std::string key);

private:
    FAssetManager() {}

    struct FTexture
    {
        unsigned int Width, Height;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Texture;
    };

    std::wstring Folder = L"Assets/";
    ID3D11Device* Device = nullptr;

    std::map<std::string, FTexture> Textures;
    std::map<std::string, std::unique_ptr<DirectX::SpriteFont>> Fonts;
};