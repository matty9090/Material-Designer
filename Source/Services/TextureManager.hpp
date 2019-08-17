#pragma once

#include <d3d11.h>

class FTextureManager
{
public:
	static FTextureManager& Get()
	{
		static FLog instance;
		return instance;
	}

	FTextureManager(FLog const&) = delete;
	void operator=(FLog const&) = delete;

private:
	FTextureManager() {}
};