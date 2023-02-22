//包含了所Hook函数的原型

#pragma once
#pragma comment(lib, "d3d11.lib")
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <iostream>
#include "imgui/imgui.h"
#include "Imgui/imgui_impl_dx11.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_win32.h"

#define CS 
//#define TF


#ifdef CS
#define GAME "Counter-Strike"
#else TF
#define GAME "TheForest"

#endif // CS

extern ID3D11Device *pDevice;
extern ID3D11DeviceContext *pContext;
extern IDXGISwapChain *pSwapchain;
extern ID3D11RenderTargetView *pRenderTargetView;


//IDXGISwapChain::Present()
/*

virtual HRESULT STDMETHODCALLTYPE Present(
				UINT SyncInterval,
				UINT Flags) = 0;
*/

typedef HRESULT(STDMETHODCALLTYPE *tD3D11Present) (IDXGISwapChain *pSwapchain, UINT Sys, UINT flags);

//ID3D11DeviceContext::DrawIndexed method (d3d11.h)
/*
virtual void STDMETHODCALLTYPE DrawIndexed(
			_In_  UINT IndexCount,
			_In_  UINT StartIndexLocation,
			_In_  INT BaseVertexLocation) = 0;
*/
typedef void (STDMETHODCALLTYPE *tD3D11DrawIndexed)(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndex, INT BaseVertexLocation);
//typedef void (STDMETHODCALLTYPE *tD3D11DrawIndexed)(UINT IndexCount, UINT StartIndex, INT BaseVertexLocation);


namespace Hooks
{
	extern tD3D11Present oPresent;
	extern tD3D11DrawIndexed oDrawIndexed;
	//WINAPI和__stdcall等价
	HRESULT STDMETHODCALLTYPE hktD3D11Present(IDXGISwapChain *pSwapchain,UINT Sys, UINT flags);
	void STDMETHODCALLTYPE hktD3D11DrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndex, INT BaseVertexLocation);
	//void STDMETHODCALLTYPE hktD3D11DrawIndexed( UINT IndexCount, UINT StartIndex, INT BaseVertexLocation);

};

