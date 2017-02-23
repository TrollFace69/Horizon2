#ifndef __H_MENU_H
#define __H_MENU_H

#include "sdk.h"
#include "cCvar.h"

class cMenu
{
public:
	void Render(int x, int y, int w, int h);
	void RenderTab(int x, int y, int w, int h);
	bool MouseClick(int x, int y, int w, int h);
	bool MouseIn(int x, int y, int w, int h);
	void GetMouse();
	bool Mover(int &X, int &Y, int W, int H, int index);
	void DrawMenu();
	bool menuEvent();

	//=== Controls ===//
	void DrawButton(int x, int y, int w, int h, const char* tText, const char* action);
	void DrawCheckBox(int x, int y, const char* fmt, bool &option);
	void DrawListbox(int x, int y, int w, int h, int letters, DWORD dwColor, DWORD textColor, const char* fmt);
	void AddTab(int x, int y, int w, int h, DWORD dwColor, DWORD outColor, const char* tText);
	void CloseButton(int x, int y, int w, int h, DWORD dwColor);
	void TabOperator(int x, int y, int w, int h);
};

extern cMenu gMenu;

#endif