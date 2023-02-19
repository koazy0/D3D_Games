#pragma once
#pragma comment(lib, "d3d11.lib")

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <iostream>



class CCheat
{
public:
	CCheat();
	~CCheat();

	void Initialize();
	void Release();
	
	ID3D11Device *pDevice;
	ID3D11DeviceContext *pContext;
	IDXGISwapChain *pSwapchain;
};

void ErrorPut();
