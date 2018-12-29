#pragma once

#include <main.h>

//Resources
extern ID3DXLine* pLine;

extern ID3DXFont* pFontVisualsLarge;
extern ID3DXFont* pFontVisualsSmall;

extern ID3DXFont* pFontUILarge;
extern ID3DXFont* pFontUISmall;

//DX Stuff
void D3DRender();
BOOL D3DInitialize(HWND hWnd);

//Drawing Functions
void DrawStringOutline(char* string, float x, float y, int r, int g, int b, int a, ID3DXFont* pFont);

//Math
void iGetFPS(int * fps);

