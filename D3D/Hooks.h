//这是对要Hook功能的集合
//包含了所Hook函数的原型


#pragma once
#pragma comment(lib, "d3d11.lib")
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <iostream>

//这是Present函数的原型
typedef HRESULT(__stdcall *tD3D11Present) (IDXGISwapChain *pSwapchain, UINT Sys, UINT flags);

namespace Hooks
{
	extern tD3D11Present oPresent;
	//WINAPI和__stdcall等价
	HRESULT __stdcall hktD3D11Present (IDXGISwapChain *pSwapchain, UINT Sys, UINT flags);

};



