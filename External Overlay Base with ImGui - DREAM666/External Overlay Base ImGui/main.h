#pragma once

#include <Windows.h>
#include <Process.h>

#include <iostream>
#include <sstream>

#include <thread>
#include <chrono>

#include <dwmapi.h>

#pragma comment(lib, "dwmapi.lib")

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//ImGui
#include <imgui.h>
#include <imgui_impl_dx9.h>

#include <globals.h>
#include <direct3d.h>
#include <cheat.h>
#include <render.h>


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
void WINAPI UpdateSurface(HWND hWnd);
HWND WINAPI InitializeWin(HINSTANCE hInst);
void UpdateWinPosition();
