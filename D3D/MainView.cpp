// MainView.cpp: 实现文件
// 主要绘制主页面

#include "pch.h"
#include "MFCDLL.h"
#include "MainView.h"
#include "afxdialogex.h"


// CMainView 对话框

IMPLEMENT_DYNAMIC(CMainView, CDialog)

CMainView::CMainView(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MainView, pParent)
{

}

CMainView::~CMainView()
{
}

void CMainView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MainTab, m_ctl_tab);
}


BEGIN_MESSAGE_MAP(CMainView, CDialog)
	//ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CMainView::OnTcnSelchangeTab2)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MainTab, &CMainView::OnTcnSelchangeMaintab)
END_MESSAGE_MAP()


// CMainView 消息处理程序
BOOL CMainView::OnInitDialog() {
	CDialog::OnInitDialog();

	// TODO: 在此添加额外的初始化
	m_ctl_tab.AddPage("1", &m_Page1, IDD_PAGE1);
	m_ctl_tab.AddPage("2", &m_Page2, IDD_PAGE2);
	/*m_ctl_tab.AddPage("3", &m_Page3, IDD_PAGE3);
	m_ctl_tab.AddPage("4", &m_Page4, IDD_PAGE4);
	m_ctl_tab.AddPage("5", &m_Page5, IDD_PAGE5);*/

	m_ctl_tab.Show();
	return TRUE;
}




void CMainView::OnTcnSelchangeMaintab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

