//��ͷ�ļ������������ľ���ʵ��

#include "pch.h"
#include "Hooks.h"



namespace Hooks
{
	//WINAPI��__stdcall�ȼ�
	tD3D11Present oPresent = NULL;
	bool bOnce = true;

	//��ͣ�Ļ��������
	HRESULT __stdcall hktD3D11Present(IDXGISwapChain *pSwapchain, UINT Sys, UINT flags) {
		

		if (!bOnce) {
			//��һ�λ����
			//�õ���Ϸ�Ĵ��壬���п�ͼ��Ⱦ��ʼ��
			MessageBox(NULL, "Initial", "test", MB_OK);

		}
		//��ͣ�Ļ���
		printf("aaaaa\n");				//�����ã����hook�ɹ���һֱ����
		return oPresent(pSwapchain,  Sys,  flags);		//����ԭ����

	}

};