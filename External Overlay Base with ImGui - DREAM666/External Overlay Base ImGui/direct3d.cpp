#include <direct3d.h>

//Direct3D Resources
IDirect3DDevice9Ex* pDevice;
IDirect3D9Ex* pInstance;
D3DPRESENT_PARAMETERS pParams;

ID3DXFont* pFontVisualsLarge;
ID3DXFont* pFontVisualsSmall;

ID3DXFont* pFontUILarge;
ID3DXFont* pFontUISmall;

ID3DXLine* pLine;

char buf[128];

//Overlay FPS
float flCurTick, flOldTick;
int iTempFPS, iRenderFPS;

BOOL D3DInitialize(HWND hWnd) {

	//Direct3D
	Direct3DCreate9Ex(D3D_SDK_VERSION, &pInstance);

	pParams.Windowed = TRUE;
	pParams.BackBufferFormat = D3DFMT_A8R8G8B8;
	pParams.BackBufferHeight = Globals::rHeight;
	pParams.BackBufferWidth = Globals::rWidth;
	pParams.MultiSampleQuality = DEFAULT_QUALITY;
	pParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pParams.EnableAutoDepthStencil = TRUE;
	pParams.AutoDepthStencilFormat = D3DFMT_D16;
	pParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	pInstance->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pParams, 0, &pDevice);

	if (pDevice == NULL) { return FALSE; }

	D3DXCreateFont(pDevice, 14, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma", &pFontVisualsLarge);
	D3DXCreateFont(pDevice, 12, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma", &pFontVisualsSmall);

	D3DXCreateFont(pDevice, 14, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma", &pFontUILarge);
	D3DXCreateFont(pDevice, 12, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma", &pFontUISmall);

	D3DXCreateLine(pDevice, &pLine);

	//ImGui
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig fontCfg = ImFontConfig();
	io.DeltaTime = 1.0f / 60.0f;

	fontCfg.RasterizerFlags = 0x01;
	fontCfg.OversampleH = fontCfg.OversampleV = 1;
	fontCfg.PixelSnapH = true;

	ImGui_ImplDX9_Init(hWnd, pDevice);

	return TRUE;
}

void D3DRender() {
	pParams.BackBufferHeight = Globals::rHeight;
	pParams.BackBufferWidth = Globals::rWidth;
	pDevice->Reset(&pParams);

	pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

	pDevice->BeginScene();

	if (Globals::tWnd == GetForegroundWindow() || GetActiveWindow() == GetForegroundWindow()) {
		//Get FPS
		iGetFPS(&Globals::iFPS);

		//Render
		Render::DrawVisuals(pDevice);
		Render::DrawInfo(pDevice);

		if (Globals::bShowMenu)
			Render::DrawMenu(pDevice);
	}


	pDevice->EndScene();
	pDevice->PresentEx(0, 0, 0, 0, 0);
}

void DrawStringOutline(char* string, float x, float y, int r, int g, int b, int a, ID3DXFont* pFont) {
	RECT rPosition;

	rPosition.left = x + 1.0f;
	rPosition.top = y;

	pFont->DrawTextA(0, string, strlen(string), &rPosition, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));

	rPosition.left = x - 1.0f;
	rPosition.top = y;

	pFont->DrawTextA(0, string, strlen(string), &rPosition, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));

	rPosition.left = x;
	rPosition.top = y + 1.0f;

	pFont->DrawTextA(0, string, strlen(string), &rPosition, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));

	rPosition.left = x;
	rPosition.top = y - 1.0f;

	pFont->DrawTextA(0, string, strlen(string), &rPosition, DT_NOCLIP, D3DCOLOR_RGBA(1, 1, 1, a));

	rPosition.left = x;
	rPosition.top = y;

	pFont->DrawTextA(0, string, strlen(string), &rPosition, DT_NOCLIP, D3DCOLOR_RGBA(r, g, b, a));
}

void iGetFPS(int * fps) {

	flCurTick = clock() * 0.001f;
	iTempFPS++;
	if ((flCurTick - flOldTick) > 1.0f) {
		iRenderFPS = iTempFPS;

		iTempFPS = 0;
		flOldTick = flCurTick;
	}

	*(int *)fps = iRenderFPS;
}