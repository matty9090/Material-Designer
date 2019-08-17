#include "TextureManager.hpp"
#include "Core/Except.hpp"
#include "Log.hpp"

#include "WICTextureLoader.h"

void FTextureManager::Initialize(ID3D11Device* device)
{
	Device = device;
}

bool FTextureManager::LoadTexture(std::string key, std::wstring file)
{
	if (Textures.find(key) != Textures.end())
	{
		FLog::Get().Log("Texture entry already exists! Keeping old texture.", FLog::Warning);
		return false;
	}

	ID3D11Resource* resource = nullptr;
	ID3D11ShaderResourceView *srv = nullptr;

	DX::ThrowIfFailed(DirectX::CreateWICTextureFromFile(Device, file.c_str(), &resource, &srv));

	Textures[key] = srv;

	FLog::Get().Log("Loaded texture '" + key + "'", FLog::Info);

	return true;
}

ID3D11ShaderResourceView* FTextureManager::GetTexture(std::string key)
{
	if (Textures.find(key) != Textures.end())
		return Textures[key];
	
	FLog::Get().Log("Could not find texture '" + key + "'!", FLog::Error);
	throw file_not_found(key);

	return nullptr;
}