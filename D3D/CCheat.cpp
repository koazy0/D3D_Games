// Hook����Ҫ�߼�
// ��������жԽ�������hook

#include "pch.h"
#include "CCheat.h"
#include "Helpers.h"
#include "Hooks.h"
#include "Render.h"







ID3D11Device *pDevice;
ID3D11DeviceContext *pContext;
IDXGISwapChain *pSwapchain;
ID3D11RenderTargetView *pRenderTargetView;

CCheat::CCheat() {

}

CCheat::~CCheat() {

}

void CCheat::Initialize() {
	AllocConsole();
	freopen("CON", "w", stdout);	//���������򵽿���̨
	SetConsoleTitle("CheatDll");

	HWND h_Window = FindWindow(NULL, GAME);
	if (!h_Window) {
		ErrorPut();
	}

	printf("h_Window:%x\n", h_Window);

	//����D3D�Ľ�����
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));

	//�Խ��������г�ʼ��
	sd.BufferCount = 1;
	/*sd.BufferDesc.Width = 1920;
	sd.BufferDesc.Height = 1080;*/
	sd.BufferDesc.Width = 1024;
	sd.BufferDesc.Height = 768;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		//8λRGBA��4��8λ����ɣ�ÿ����ԱΪ[0,1.f]֮�䣻

	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;	//���ű�
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	//ɨ����

	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		//��ȾĿ�����
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		//����ģʽ�л�

	sd.OutputWindow = h_Window;		//����Ϸ�ڲ����л���
	sd.SampleDesc.Count = 1;		//����1�ز���
	sd.SampleDesc.Quality = 0;

	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = TRUE;				//ture����ȫ����ʵ����Ӧ�ø�����Ϸ�Ƿ�ȫ�������û����Ƿ���Ҫȫ��
	//sd.Windowed = ((GetWindowLong(h_Window, GWL_STYLE)&WS_POPUP) != 0) ? false : true;	//�ж��Ƿ�ȫ��
	sd.BufferDesc.RefreshRate.Numerator = 144;	//ˢ����
	sd.BufferDesc.RefreshRate.Denominator = 1;	//ˢ��������ķ�ĸ  

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
		&pSwapchain,	//����Ҫ�Ķ���
		&pDevice,
		NULL,
		&pContext
	);

//hook�麯��
	//��ȡ��IDXGISwapChain::Prensent()�ĵ�ַ
	DWORD_PTR * pSwapchainVT = reinterpret_cast<DWORD_PTR * > (pSwapchain);
	pSwapchainVT = reinterpret_cast<DWORD_PTR *>(pSwapchainVT[0]);
	Hooks::oPresent = reinterpret_cast<tD3D11Present>(pSwapchainVT[8]);

	//��ȡ��ID3D11DeviceContext::DrawIndexed()�ĵ�ַ
	DWORD_PTR * pContextVT = reinterpret_cast<DWORD_PTR *> (pContext);
	pSwapchainVT = reinterpret_cast<DWORD_PTR *>(pContextVT[0]);
	Hooks::oDrawIndexed = reinterpret_cast<tD3D11DrawIndexed>(pContextVT[12]);
	//��֤���ַ���Ƿ��ӡ��ȷ
	/*for (int i = 0; i < 9; i++) {
		printf("pSwapchainVT[%d]:%X\n",i, pSwapchainVT[i]);
	}*/
	
	//�ڴ�λ�ý��л���ĳ�ʼ��
	//��ʼ������ʼ�Թؼ���������hook
	//����C++����ģʽ---->����ģʽ(�ڹ����ʱ����ʵ��)
	printf("pSwapChain:%X\n", pSwapchain);
	printf("pDevice:%X\n", pDevice);
	printf("pContext:%X\n", pContext);

	Render::GetInstance()->Initialize();

	Helpers::HookFunction(reinterpret_cast<PVOID *>(&(Hooks::oPresent)), Hooks::hktD3D11Present);
	Helpers::HookFunction(reinterpret_cast<PVOID *>(&Hooks::oDrawIndexed), Hooks::hktD3D11DrawIndexed);
	
	printf("\n\n\n");
	printf("Initialize Finished \n");

}

void CCheat::Release() {
	Helpers::UnhookFunction(reinterpret_cast<PVOID *>(&(Hooks::oPresent)), Hooks::hktD3D11Present);
	Helpers::UnhookFunction(reinterpret_cast<PVOID *>(&(Hooks::oDrawIndexed)), Hooks::hktD3D11DrawIndexed);
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	FreeConsole();
}

void ErrorPut() {
	std::cout << GetLastError() << std::endl;
}