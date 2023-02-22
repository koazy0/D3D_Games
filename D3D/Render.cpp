//�Բ˵������Ⱦ
#include "pch.h"
#include "Imgui/imgui.h"
#include <Windows.h>
#include <iostream>
#include "Render.h"


Render* Render::m_Instance;

void Render::Initialize() {
	std::cout << "׼����ʼ��ImGui..." << std::endl;
	ImGui::CreateContext();
	ImGuiIO &Io = ImGui::GetIO();
	ImGuiStyle &Style = ImGui::GetStyle();

	Io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttc", 18.0f, NULL, Io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
	//Io.Fonts->GetTexDataAsAlpha8();
}

Render* Render::GetInstance() {
	if (m_Instance == NULL) {
		m_Instance = new Render;
	}
	return m_Instance;
}