#pragma once

#include "TabSheet.h"
#include "CPage1.h"
#include "CPage2.h"


// CMainView 对话框

class CMainView : public CDialog
{
	DECLARE_DYNAMIC(CMainView)

public:
	CMainView(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMainView();
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MainView };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CPage1 m_Page1;
	CPage2 m_Page2;
	/*CPage3 m_Page3;
	CPage4 m_Page4;
	CPage5 m_Page5;*/
	

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeMaintab(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CTabSheet m_ctl_tab;
};

