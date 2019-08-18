#include "AssetManager.hpp"
#include "Core/Except.hpp"
#include "Log.hpp"

#include <WICTextureLoader.h>

using Microsoft::WRL::ComPtr;

void FAssetManager::Initialize(ID3D11Device* device)
{
    Device = device;
}

bool FAssetManager::LoadTexture(std::string key, std::wstring file)
{
    if (Textures.find(key) != Textures.end())
        return false;

    // Load texture
    ComPtr<ID3D11Resource> resource = nullptr;
    ComPtr<ID3D11ShaderResourceView> texture = nullptr;

    DX::ThrowIfFailed(DirectX::CreateWICTextureFromFile(Device, (Folder + file).c_str(), resource.ReleaseAndGetAddressOf(), texture.ReleaseAndGetAddressOf()));

    // Get width and height
    ComPtr<ID3D11Texture2D> texture2d;
    DX::ThrowIfFailed(resource.As(&texture2d));

    CD3D11_TEXTURE2D_DESC texDesc;
    texture2d->GetDesc(&texDesc);

    // Store in cache
    Textures[key] = { texDesc.Width, texDesc.Height, texture };

    FLog::Get().Log("Loaded texture '" + key + "'", FLog::Info);

    return true;
}

ID3D11ShaderResourceView* FAssetManager::GetTexture(std::string key)
{
    if (Textures.find(key) != Textures.end())
        return Textures[key].Texture.Get();
    
    FLog::Get().Log("Could not find texture '" + key + "'!", FLog::Error);
    throw file_not_found(key);

    return nullptr;
}

ID3D11ShaderResourceView* FAssetManager::GetTexture(std::string key, unsigned int& Width, unsigned int& Height)
{
    if (Textures.find(key) != Textures.end())
    {
        auto &tex = Textures[key];
        Width = tex.Width;
        Height = tex.Height;

        return tex.Texture.Get();
    }

    FLog::Get().Log("Could not find texture '" + key + "'!", FLog::Error);
    throw file_not_found(key);

    return nullptr;
}

bool FAssetManager::LoadFont(std::string key, std::wstring file)
{
    if (Fonts.find(key) != Fonts.end())
        return false;

    std::unique_ptr<DirectX::SpriteFont> font = std::make_unique<DirectX::SpriteFont>(Device, (Folder + file).c_str());

    if (font == nullptr)
        throw file_not_found(key);

    FLog::Get().Log("Loaded font '" + key + "'");
    Fonts[key] = std::move(font);

    return true;
}

DirectX::SpriteFont* FAssetManager::GetFont(std::string key)
{
    if (Fonts.find(key) != Fonts.end())
        return Fonts[key].get();

    FLog::Get().Log("Could not find font '" + key + "'!", FLog::Error);
    throw file_not_found(key);

    return nullptr;
}
