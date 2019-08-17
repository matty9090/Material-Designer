#pragma once

#include <map>
#include <string>

#include <d3d11.h>

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

private:
	FTextureManager() {}

	ID3D11Device* Device = nullptr;
	std::map<std::string, ID3D11ShaderResourceView*> Textures;
};