// MFCDLL.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "MFCDLL.h"
#include "MainView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CMFCDLLApp

BEGIN_MESSAGE_MAP(CMFCDLLApp, CWinApp)
END_MESSAGE_MAP()


// CMFCDLLApp 构造

CMFCDLLApp::CMFCDLLApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFCDLLApp 对象

CMFCDLLApp theApp;
HANDLE g_Mainthread;
HANDLE h_FreeHandle;


void UIThread(void *param) {
	
	//进行资源切换
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HINSTANCE hResOld = AfxGetResourceHandle();
	AfxSetResourceHandle(theApp.m_hInstance);

	//创建窗体
	CMainView *Mainview=new CMainView();
	Mainview->DoModal();						//模态窗口，如同帮助-关于窗口，关闭之前无法操作主窗口
	
	//关闭窗口后
	delete Mainview;
	Mainview = NULL;	//养成好习惯
	

	//开辟一个线程，卸载掉注入的theApp模块
	h_FreeHandle =::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, theApp.m_hInstance, NULL, NULL);
	
	//释放资源，防止内存泄漏
	CloseHandle(g_Mainthread);//释放界面线程的句柄
	CloseHandle(h_FreeHandle);//释放释放线程的句柄

	//将资源切换回去
	AfxSetResourceHandle(hResOld);
}

// CMFCDLLApp 初始化

BOOL CMFCDLLApp::InitInstance()		//入口函数，首先执行到这里
{
	CWinApp::InitInstance();
	
	//开辟一个线程
	g_Mainthread=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)UIThread, NULL, 0,0);

	return TRUE;
}
