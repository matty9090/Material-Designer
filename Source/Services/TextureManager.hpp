#pragma once

#include <map>
#include <string>

#include <d3d11.h>
#include <wrl/client.h>

struct FTexture
{
    unsigned int Width, Height;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Texture;
};

class FTextureManager
{
public:
    static FTextureManager& Get()
    {
        static FTextureManager instance;
        return instance;
    }

    FTextureManager(FTextureManager const&) = delete;
    void operator=(FTextureManager const&) = delete;

    void Initialize(ID3D11Device* device);
    bool LoadTexture(std::string key, std::wstring file);

    ID3D11ShaderResourceView* GetTexture(std::string key);
    ID3D11ShaderResourceView* GetTexture(std::string key, unsigned int& Width, unsigned int& Height);

private:
    FTextureManager() {}

    std::wstring Folder = L"Assets/";
    ID3D11Device* Device = nullptr;
    std::map<std::string, FTexture> Textures;
};