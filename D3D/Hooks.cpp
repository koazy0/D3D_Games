//���Ƕ�Hook�ľ���ʵ��


#include "pch.h"
#include "Hooks.h"


namespace Hooks
{
	//WINAPI��__stdcall�ȼ�
	tD3D11Present oPresent ;
	tD3D11DrawIndexed oDrawIndexed ;
	bool bOnce = false;
	int testvalue = -1;

	enum eDepthState
	{
		ENABLED,
		DISABLED,
		READ_NO_WRITE,
		NO_READ_NO_WRITE,
		_DEPTH_COUNT,
	};

	ID3D11DepthStencilState * myDepthStencilState[static_cast<int>(eDepthState::_DEPTH_COUNT)];


	HRESULT GenerateShader(ID3D11Device *pD3DDevice, ID3D11PixelShader **pShader, float r, float g, float b) {
		return 0;
	}


	//��ͣ�Ļ��������
	HRESULT __stdcall hktD3D11Present(IDXGISwapChain *pSwapchain,UINT Sys, UINT flags) {
		

		if (!bOnce) {
			//��һ�λ����
			//�õ���Ϸ�Ĵ��壬���п�ͼ��Ⱦ��ʼ��
			//MessageBox(NULL, "Initial", "test", MB_OK);

			HWND h_Window = FindWindow(NULL, GAME);
			if (SUCCEEDED(pSwapchain->GetDevice(__uuidof(ID3D11Device), (void **)(&pDevice)))) {
				pSwapchain->GetDevice(__uuidof(ID3D11Device), (void **)(&pDevice));
				pDevice->GetImmediateContext(&pContext);
			}

		//������ȾĿ����ͼ
			ID3D11Texture2D *RenderTargetTexture = nullptr;
			
			//��ȡ�󻺳�����ַ
			if (SUCCEEDED(pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<PVOID *>(&RenderTargetTexture)))) {
				//����Ŀ����ͼ
				pDevice->CreateRenderTargetView(RenderTargetTexture, NULL, &pRenderTargetView);
				//�ͷź󻺳�
				RenderTargetTexture->Release();
			}
			
			D3D11_DEPTH_STENCIL_DESC StencilDesc;
			StencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
			StencilDesc.StencilEnable = true;
			StencilDesc.StencilReadMask = 0xff;
			StencilDesc.StencilWriteMask = 0xff;

			StencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			StencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			StencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			StencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			StencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			StencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			StencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			StencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;


			//Enabled ����״̬
			StencilDesc.DepthEnable = true;
			StencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			pDevice->CreateDepthStencilState(&StencilDesc, &myDepthStencilState[static_cast<int>(eDepthState::ENABLED)]);

			//Disabled ����״̬
			StencilDesc.DepthEnable = false;
			StencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			pDevice->CreateDepthStencilState(&StencilDesc, &myDepthStencilState[static_cast<int>(eDepthState::DISABLED)]);

			//NO_READ_NO_WRITE
			StencilDesc.DepthEnable = false;
			StencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
			StencilDesc.StencilEnable = false;
			StencilDesc.StencilReadMask = (UINT)0xff;
			StencilDesc.StencilWriteMask = 0x0;
			pDevice->CreateDepthStencilState(&StencilDesc, &myDepthStencilState[static_cast<int>(eDepthState::NO_READ_NO_WRITE)]);


			//READ_NO_WRITE
			StencilDesc.DepthEnable = true;
			StencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			StencilDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
			StencilDesc.StencilEnable = false;
			StencilDesc.StencilReadMask = (UINT)0xff;
			StencilDesc.StencilWriteMask = 0x0;

			StencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_ZERO;
			StencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_ZERO;
			StencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			StencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;

			StencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_ZERO;
			StencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_ZERO;
			StencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_ZERO;
			StencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;
			pDevice->CreateDepthStencilState(&StencilDesc, &myDepthStencilState[static_cast<int>(eDepthState::READ_NO_WRITE)]);


			//��ɫ��,����
			GenerateShader(pDevice, psRed, 1.0f, 0.0f, 0.0f);
			GenerateShader(pDevice, psGreen, 0.0f, 1.0f, 0.0f);


			//----------------------------------------------------------------------

			ImGui_ImplWin32_Init(h_Window);
			ImGui_ImplDX11_Init( pDevice, pContext);
			ImGui_ImplDX11_CreateDeviceObjects();
			ImGui::StyleColorsLight();
			bOnce = true;
			
		}
		
		//������Ⱦ����
		pContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);
		
		//printf("aaaaa\n");				//�����ã����hook�ɹ���һֱ����
		
		//��ͣ�Ļ��������
		ImGui_ImplWin32_NewFrame();
		ImGui_ImplDX11_NewFrame();
		
		ImGui::NewFrame();
		

		if (bOnce) {
			ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(200, 400));
			ImGui::Begin(u8"�������", &bOnce,0);
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		
		return oPresent(pSwapchain, Sys, flags);		//����ԭ����

	}

	void __stdcall hktD3D11DrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndex, INT BaseVertexLocation) {

		UINT Stride = 0;
		ID3D11Buffer *veBuffer;
		UINT VEBufferOffset = 0;
		pContext->IAGetVertexBuffers(0, 1, &veBuffer, &Stride, &VEBufferOffset);

		if (GetAsyncKeyState('n') & 1) {
			testvalue = 512222792;
		}

		if (GetAsyncKeyState('m') & 1) {
			testvalue = 0;
		}

		/*if (IndexCount >= testvalue && IndexCount <= testvalue + 100) {
			printf("IndexCount:%d\n", IndexCount);
			return oDrawIndexed(pContext, IndexCount, StartIndex, BaseVertexLocation);
		}*/


		if (IndexCount == testvalue) {
			printf("%d\n", testvalue);
			return oDrawIndexed(pContext, IndexCount, StartIndex, BaseVertexLocation);
		}
		
		/*printf("%d\n", Stride);
		if (Stride == 80) {
			return;
		}
		return oDrawIndexed(pContext, IndexCount, StartIndex, BaseVertexLocation);*/

	}

	
};
