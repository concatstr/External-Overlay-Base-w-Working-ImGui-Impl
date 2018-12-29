#include <entry.h>

//Used for Internal/External Cheats
//NOTE: Leftover code from internal overlay!

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, hInst, 0, 0);
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UpdateWinPosition, 0, 0, 0);
		break;
	default:
		break;
	}
	return TRUE;
}