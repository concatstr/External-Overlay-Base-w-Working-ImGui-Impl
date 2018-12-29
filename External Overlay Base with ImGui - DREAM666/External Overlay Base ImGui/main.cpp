#include <main.h>

char WINNAME[19] = " ";
char TARGETNAME[64] = "Roblox";

DWORD procID;
MARGINS MARGIN = { 0, 0, Globals::rWidth, Globals::rHeight };

BOOL UNLOADING = FALSE;
BOOL NOTFOUND = FALSE;
BOOL INITIALIZED = FALSE;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//Thread Creation
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Cheat::Update, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Cheat::LateUpdate, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UpdateWinPosition, 0, 0, 0);

	//Find Target Window
	while (Globals::rWidth < 640 && Globals::rHeight < 480) {
		Globals::tWnd = FindWindow(NULL, TARGETNAME);

		RECT wSize;
		GetWindowRect(Globals::tWnd, &wSize);
		Globals::rWidth = wSize.right - wSize.left;
		Globals::rHeight = wSize.bottom - wSize.top;
	}
	
	//Get All Access Handle
	GetWindowThreadProcessId(Globals::tWnd, &procID);
	Globals::hGame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

	//Initialize Overlay Window
	Globals::hWnd = InitializeWin((HINSTANCE)hInst);
	MSG uMessage;

	if (Globals::hWnd == NULL) { exit(1); }

	ShowWindow(Globals::hWnd, SW_SHOW);

	INITIALIZED = TRUE;

	while (!UNLOADING) {
		if (PeekMessage(&uMessage, Globals::hWnd, 0, 0, PM_REMOVE)) {
			DispatchMessage(&uMessage);
			TranslateMessage(&uMessage);
		}

		//Timed MessageBox
		if (UNLOADING) {
			HWND hMsg = FindWindow(NULL, "Info");

			if (hMsg) {
				std::this_thread::sleep_for(std::chrono::seconds(3));
				SendMessageA(hMsg, WM_CLOSE, 0, 0);
			}
		}
	}
	
	//Cleanup and unload our module 
	//NOTE: Leftover code from internal overlay!
	DestroyWindow(Globals::hWnd);
	UnregisterClass(WINNAME, (HINSTANCE)hInst);
	FreeLibraryAndExitThread((HMODULE)hInst, 0);
	return 0;
}

HWND WINAPI InitializeWin(HINSTANCE hInst) {
	WNDCLASSEX wndClass;

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = NULL;
	wndClass.cbWndExtra = NULL;
	wndClass.hCursor = LoadCursor(0, IDC_ARROW);
	wndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wndClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wndClass.hInstance = hInst; 
	wndClass.lpfnWndProc = WindowProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = WINNAME;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wndClass)) {
		exit(1);
	}

	Globals::hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, WINNAME, WINNAME, WS_POPUP, 1, 1, Globals::rWidth, Globals::rHeight, 0, 0, 0, 0);
	SetLayeredWindowAttributes(Globals::hWnd, 0, 255, LWA_ALPHA);
	SetLayeredWindowAttributes(Globals::hWnd, RGB(0, 0, 0), 0, ULW_COLORKEY);

	D3DInitialize(Globals::hWnd);

	return Globals::hWnd;
}

void UpdateWinPosition() {
	while (!UNLOADING) {
		UpdateSurface(Globals::hWnd);

		std::this_thread::sleep_for(std::chrono::seconds(2));
	}

	return;
}

void WINAPI UpdateSurface(HWND hWnd) {
		RECT wSize;
		HWND tWnd;

		tWnd = FindWindow(NULL, TARGETNAME);

		if (!tWnd && hWnd && !UNLOADING && !NOTFOUND) { ShowWindow(hWnd, SW_HIDE); MessageBox(NULL, "Game closed! Shutting down cheat client...", "Info", MB_OK | MB_ICONINFORMATION); UNLOADING = TRUE; }

		if (tWnd) {
			GetWindowRect(tWnd, &wSize);
			Globals::rWidth = wSize.right - wSize.left;
			Globals::rHeight = wSize.bottom - wSize.top;

			DWORD dwStyle = GetWindowLong(tWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				wSize.top += 23; Globals::rHeight -= 23;
				//wSize.left += 10; rWidth -= 10;
			}

			if (hWnd) {
				MoveWindow(hWnd, wSize.left, wSize.top, Globals::rWidth, Globals::rHeight, true);
			}
		}

	return;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
	switch (uMessage) {
		case WM_CREATE:
			DwmExtendFrameIntoClientArea(hWnd, &MARGIN);
			break;

		case WM_PAINT:
			D3DRender();
			break;

		case WM_DESTROY:
			PostQuitMessage(1);
			break;

		default:
			ImGui_ImplWin32_WndProcHandler(hWnd, uMessage, wParam, lParam);
			return DefWindowProc(hWnd, uMessage, wParam, lParam);
			break;
	}

	return 0;
}