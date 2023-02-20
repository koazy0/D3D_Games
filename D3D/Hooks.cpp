//对头文件中声明函数的具体实现

#include "pch.h"
#include "Hooks.h"



namespace Hooks
{
	//WINAPI和__stdcall等价
	tD3D11Present oPresent = NULL;
	bool bOnce = true;

	//不停的画插件界面
	HRESULT __stdcall hktD3D11Present(IDXGISwapChain *pSwapchain, UINT Sys, UINT flags) {
		

		if (!bOnce) {
			//第一次会进来
			//得到游戏的窗体，进行框图渲染初始化
			MessageBox(NULL, "Initial", "test", MB_OK);

		}
		//不停的画框
		printf("aaaaa\n");				//测试用，如果hook成功能一直画框
		return oPresent(pSwapchain,  Sys,  flags);		//返回原函数

	}

};