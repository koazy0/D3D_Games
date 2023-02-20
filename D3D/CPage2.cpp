// CPage2.cpp: 实现文件
//

#include "pch.h"
#include "MFCDLL.h"
#include "CPage2.h"
#include "afxdialogex.h"


// CPage2 对话框

IMPLEMENT_DYNAMIC(CPage2, CDialog)

CPage2::CPage2(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PAGE2, pParent)
{

}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage2, CDialog)
	ON_BN_CLICKED(IDOK, &CPage2::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage2::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPage2::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPage2 消息处理程序


void CPage2::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}

CCheat c;

void CPage2::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	c.Initialize();
}


void CPage2::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	c.Release();
}
