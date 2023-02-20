// Hook的主要逻辑
// 在这里进行对交换链的hook

#include "pch.h"
#include "CCheat.h"
#include "Helpers.h"
#include "Hooks.h"

CCheat::CCheat() {

}

CCheat::~CCheat() {

}


void CCheat::Initialize() {
	AllocConsole();
	freopen("CON", "w", stdout);	//输入流定向到控制台
	SetConsoleTitle("CheatDll");

	HWND h_Window = FindWindow(NULL, "Counter-Strike");
	//HWND h_Window = FindWindow(NULL, "AssaultCube");
	if (!h_Window) {
		ErrorPut();
	}

	printf("h_Window:%x\n", h_Window);

	//建立D3D的交换链
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));

	//对交换链进行初始化
	sd.BufferCount = 1;
	/*sd.BufferDesc.Width = 1920;
	sd.BufferDesc.Height = 1080;*/

	sd.BufferDesc.Width = 1024;
	sd.BufferDesc.Height = 768;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		//8位RGBA，4个8位数组成，每个成员为[0,1.f]之间；

	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;	//缩放比
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	//扫描线

	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		//渲染目标输出
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		//允许模式切换

	sd.OutputWindow = h_Window;		//在游戏内部进行画框
	sd.SampleDesc.Count = 1;		//设置1重采样
	sd.SampleDesc.Quality = 0;

	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = TRUE;				//ture代表全屏；实际上应该根据游戏是否全屏来设置画框是否需要全屏
	//sd.Windowed = ((GetWindowLong(h_Window, GWL_STYLE)&WS_POPUP) != 0) ? false : true;	//判断是否全屏
	sd.BufferDesc.RefreshRate.Numerator = 144;	//刷新率
	sd.BufferDesc.RefreshRate.Denominator = 1;	//刷新率相除的分母  

	D3D_FEATURE_LEVEL featurelevel = D3D_FEATURE_LEVEL_11_0;

	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		&featurelevel,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapchain,	//最重要的东西
		&pDevice,
		NULL,
		&pContext
	);

	DWORD_PTR * pSwapchainVT = reinterpret_cast<DWORD_PTR * > (pSwapchain);
	
	pSwapchainVT = reinterpret_cast<DWORD_PTR *>(pSwapchainVT[0]);

	for (int i = 0; i < 9; i++) {
		printf("pSwapchainVT[%d]:%X\n",i, pSwapchainVT[i]);
	}
	
	Hooks::oPresent = reinterpret_cast<tD3D11Present>(pSwapchainVT[8]);
	
	Helpers::HookFunction(reinterpret_cast<PVOID *>(&Hooks::oPresent), Hooks::hktD3D11Present);

	printf("pSwapChain:%X\n",pSwapchain);
	printf("pDevice:%X\n", pDevice);
	printf("pContext:%X\n", pContext);
	printf("Initialize Finished \n");

}

void CCheat::Release() {
	Helpers::UnhookFunction(reinterpret_cast<PVOID *>(&Hooks::oPresent), Hooks::hktD3D11Present);
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	FreeConsole();
}

void ErrorPut() {
	std::cout << GetLastError() << std::endl;
}