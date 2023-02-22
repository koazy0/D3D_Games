// CPage1.cpp: 实现文件
//

#include "pch.h"
#include "MFCDLL.h"
#include "CPage1.h"
#include "afxdialogex.h"

#include <detours.h>

// CPage1 对话框

IMPLEMENT_DYNAMIC(CPage1, CDialog)

CPage1::CPage1(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PAGE1, pParent)
{

}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage1, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CPage1::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CPage1 消息处理程序


void CPage1::OnBnClickedButton1()
{
	//花指令，方便调试的时候定位
	
	MessageBox("Unhook", NULL, MB_OK);
	// TODO: 在此添加控件通知处理程序代码
}


static int (WINAPI * Real_Messagebox)( 
	HWND hWnd,
	LPCSTR lpText,
	LPCSTR lpCaption,
	UINT uType) = MessageBox;

int WINAPI My_Messagebox(
	 HWND hWnd,
	 LPCSTR lpText,
	 LPCSTR lpCaption,
	 UINT uType) {

	lpText = "Hooked!";
	return Real_Messagebox(hWnd, lpText, lpCaption, uType);
}

void CPage1::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	

	if (((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck()) {
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)Real_Messagebox, My_Messagebox);
		DetourTransactionCommit();
	}
	else {
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)Real_Messagebox, My_Messagebox);
		DetourTransactionCommit();
	}
}
