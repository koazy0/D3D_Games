#pragma once
#include "CCheat.h"

// CPage2 对话框

class CPage2 : public CDialog
{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPage2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
