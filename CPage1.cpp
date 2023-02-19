// CPage1.cpp: 实现文件
//

#include "pch.h"
#include "MFCDLL.h"
#include "CPage1.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// CPage1 消息处理程序


void CPage1::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
