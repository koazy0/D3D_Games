#pragma once
#pragma comment(lib, "d3d11.lib")

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <iostream>



class CCheat
{
public:
	CCheat();
	~CCheat();

	void Initialize();
	void Release();
	
	
};

void ErrorPut();
