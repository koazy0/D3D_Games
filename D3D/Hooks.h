//���Ƕ�ҪHook���ܵļ���
//��������Hook������ԭ��


#pragma once
#pragma comment(lib, "d3d11.lib")
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <iostream>

//����Present������ԭ��
typedef HRESULT(__stdcall *tD3D11Present) (IDXGISwapChain *pSwapchain, UINT Sys, UINT flags);

namespace Hooks
{
	extern tD3D11Present oPresent;
	//WINAPI��__stdcall�ȼ�
	HRESULT __stdcall hktD3D11Present (IDXGISwapChain *pSwapchain, UINT Sys, UINT flags);

};



