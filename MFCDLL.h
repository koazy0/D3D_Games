// MFCDLL.h: MFCDLL DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号


// CMFCDLLApp
// 有关此类实现的信息，请参阅 MFCDLL.cpp
//

class CMFCDLLApp : public CWinApp
{
public:
	CMFCDLLApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
