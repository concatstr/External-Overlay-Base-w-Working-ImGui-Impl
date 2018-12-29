#include <render.h>

char buffer[256];
bool bTest = false;

bool bFirstTime = true;

namespace Render {
	void DrawInfo(IDirect3DDevice9* pDevice) {
		sprintf(buffer, "FPS at %d", Globals::iFPS);
		DrawStringOutline("Direct3D Overlay by Dream666\nPress INS to show/hide menu", 15, 10, 255, 255, 255, 255, pFontUISmall);
		DrawStringOutline(buffer, 15, 35, 197, 66, 244, 255, pFontUISmall);
	}

	void DrawVisuals(IDirect3DDevice9* pDevice) {
		//ESP Loop.. etc
	}

	void DrawMenu(IDirect3DDevice9* pDevice) {
		//ImGui Custom Colors
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.62f, 0.93f, 0.06f, 1.00f);

		//ImGui Frame
		ImGui_ImplDX9_NewFrame();

		if (bFirstTime)
			ImGui::SetNextWindowSize(ImVec2(400, 300));

		ImGui::Begin("ImGui Window");
		
		ImGui::Checkbox("enabled", &bTest);

		ImGui::End();

		ImGui::Render();

		bFirstTime = false;
	}
}