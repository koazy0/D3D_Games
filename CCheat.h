#pragma once
#pragma comment(lib, "d3d11.lib")

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
