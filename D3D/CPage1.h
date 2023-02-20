#pragma once
#pragma comment(lib, "detours.lib")

// CPage1 对话框

class CPage1 : public CDialog
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPage1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
};

int  WINAPI My_Messagebox(
	HWND hWnd,
	LPCSTR lpText,
	LPCSTR lpCaption,
	UINT uType);