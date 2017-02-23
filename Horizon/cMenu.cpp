#include "cMenu.h"
#include "xorstr.h"
#include "cDrawing.h"

cMenu gMenu;

#define MENU_GOLD COLORCODE(218, 165, 32, 255)

void cMenu::Render(int x, int y, int w, int h)
{
	gDrawing.FillRGBA(x, y, w, h, COLORCODE(0, 0, 0, 120));				// Main BG
	gDrawing.FillRGBA(x, y, w, 20, COLORCODE(0, 0, 0, 255));			// Top Bar
	gDrawing.Border(x, y, w, h, CHEAT_BLACK);							// Border
	gDrawing.DrawString_w(x + 2, y + 3, CHEAT_WHITE, "HorizonHack");
	gDrawing.DrawLine(x + 350, y, x + w - 100, y + h, CHEAT_BLACK);		// Tab Border

	gMenu.TabOperator(x, y, w, h);
	gMenu.RenderTab(x, y, w, h);
	gMenu.GetMouse();
	gMenu.Mover(gCvar.MenuX, gCvar.MenuY, w, 20, 0);
}


//=============== Controls =============== //
void cMenu::AddTab(int x, int y, int w, int h, DWORD dwColor, DWORD oColor, const char* tText)
{
	gDrawing.FillRGBA(x, y, w, h, dwColor);
	gDrawing.Border(x, y, w, h, CHEAT_BLACK);
	gDrawing.DrawString_w(x + 30, y - 1, oColor, tText);
}

void cMenu::RenderTab(int x, int y, int w, int h)
{
	gMenu.AddTab(x + 351, y + 30, 99, 15, COLORCODE(0, 0, 0, 100), CHEAT_WHITE, "Aimbot");
	gMenu.AddTab(x + 351, y + 60, 99, 15, COLORCODE(0, 0, 0, 100), CHEAT_WHITE, "Visuals");
	gMenu.AddTab(x + 351, y + 90, 99, 15, COLORCODE(0, 0, 0, 100), CHEAT_WHITE, "Misc");
	gMenu.AddTab(x + 351, y + 120, 99, 15, COLORCODE(0, 0, 0, 100), CHEAT_WHITE, "Config");
}

void cMenu::DrawListbox(int x, int y, int w, int h, int letters, DWORD dwColor, DWORD textColor, const char* fmt)
{
	gDrawing.FillRGBA(x, y, w, h, COLORCODE(0, 0, 0, 100));
	gDrawing.Border(x, y, w, h, CHEAT_BLACK);
	gDrawing.DrawString(x, y - 15, textColor, fmt);
}

void cMenu::DrawCheckBox(int x, int y, const char* fmt, bool &option)
{
	POINT Pos;
	RECT mRect;
	HWND hWnd = ::GetActiveWindow();

	GetWindowRect(hWnd, (LPRECT)&mRect);
	GetCursorPos(&Pos);

	int cursorx = Pos.x - 05 - mRect.left;
	int cursory = Pos.y - 30 - mRect.top;

	gDrawing.Border(x, y, 12, 12, CHEAT_BLACK);
	gDrawing.DrawString(x + 18, y - 2, CHEAT_WHITE, fmt);


	if (cursorx > x && cursorx < x + 13 && cursory > y && cursory < y + 13)
	{
		if (GetAsyncKeyState(0x01) & 1)
		{
			option = !option;
		}
	}
	if (option)
	{
		gDrawing.DrawString(x + 2.7, y - 1.4, COLORCODE(204, 0, 0, 255), "X");
		//gDrawing.FillRGBA(x + 1, y + 1, 13, 12, MENU_GOLD);
	}
}

void cMenu::DrawButton(int x, int y, int w, int h, const char* tText, const char* action)
{
	POINT Pos;
	RECT mRect;
	HWND hWnd = ::GetActiveWindow();

	GetWindowRect(hWnd, (LPRECT)&mRect);
	GetCursorPos(&Pos);

	int cursorx = Pos.x - 05 - mRect.left;
	int cursory = Pos.y - 30 - mRect.top;

	gDrawing.FillRGBA(x, y, w, h, COLORCODE(0, 0, 0, 100));
	gDrawing.Border(x, y, w, h, CHEAT_BLACK);
	gDrawing.DrawString(x + w / 2 - 25, y + 5, CHEAT_WHITE, tText);
	if (cursorx > x && cursory > y  && cursorx < x + w && cursory < y + h)
	{
		gDrawing.Border(x, y, w, h, CHEAT_WHITE);
		if (GetAsyncKeyState(0x01) & 1)
		{
			if (action == "LoadRage")
			{
				gCvar.esp_active = true;
				gCvar.esp_name = false;
				gCvar.esp_health = true;
				gCvar.esp_steamid = false;
				gCvar.esp_distance = true;
				gCvar.esp_enemyonly = false;
				gCvar.esp_visibilty = false;
				gCvar.esp_2dbox = true;
				gCvar.esp_3dbox = false;
				gCvar.esp_playerlight = false;

				gCvar.esp_crosshair = true;
				gCvar.esp_plus = true;
				gCvar.esp_square = true;
			}

			if (action == "LoadHVH")
			{
				gCvar.esp_active = true;
				gCvar.esp_name = false;
				gCvar.esp_health = true;
				gCvar.esp_steamid = false;
				gCvar.esp_distance = false;
				gCvar.esp_enemyonly = false;
				gCvar.esp_visibilty = false;
				gCvar.esp_2dbox = true;
				gCvar.esp_3dbox = false;
				gCvar.esp_playerlight = false;

				gCvar.esp_crosshair = true;
				gCvar.esp_plus = false;
				gCvar.esp_square = true;
			}

			if (action == "BEEP")
			{
				Beep(500, 750);
			}
		}
	}
}

void cMenu::CloseButton(int x, int y, int w, int h, DWORD dwColor)
{
	gDrawing.FillRGBA(x, y, w, h, dwColor);
	gDrawing.DrawString(x + 12, y + 1, CHEAT_WHITE, "X");


	if (MouseClick(x, y, w, h))
	{
		gCvar.IsActive = !gCvar.IsActive;
	}
}

//=============== Menu ====================//
void cMenu::TabOperator(int x, int y, int w, int h)
{
	gMenu.CloseButton(x + w - 28, y - 1, 30, 21, CHEAT_RED);

	if (gMenu.MouseClick(x + 351, y + 30, 99, 15))
	{
		gCvar.tabAim = !gCvar.tabAim;
		gCvar.tabESP = false;
		gCvar.tabMis = false;
		gCvar.tabCre = false;
	}

	if (gMenu.MouseClick(x + 351, y + 60, 99, 15))
	{
		gCvar.tabAim = false;
		gCvar.tabESP = !gCvar.tabESP;
		gCvar.tabMis = false;
		gCvar.tabCre = false;
	}
	if (gMenu.MouseClick(x + 351, y + 90, 99, 15))
	{
		gCvar.tabAim = false;
		gCvar.tabESP = false;
		gCvar.tabCre = false;
		gCvar.tabMis = !gCvar.tabMis;
	}
	if (gMenu.MouseClick(x + 351, y + 120, 99, 15))
	{
		gCvar.tabAim = false;
		gCvar.tabESP = false;
		gCvar.tabMis = false;
		gCvar.tabCre = !gCvar.tabCre;
	}


	if (gCvar.tabAim)
	{
		gCvar.tabMis = false;
		gCvar.tabESP = false;
		gCvar.tabCre = false;

		gMenu.DrawCheckBox(x + 10, y + 40, "Aim Enabled", gCvar.aim_enable);
	}

	if (gCvar.tabESP)
	{
		gCvar.tabAim = false;
		gCvar.tabMis = false;
		gCvar.tabCre = false;

		int yPos = y;

		gMenu.DrawCheckBox(x + 10, yPos + 40, "ESP Enabled", gCvar.esp_active);
		yPos = yPos + 14;
		if (gCvar.esp_active)
		{
			gMenu.DrawCheckBox(x + 20, yPos + 45, "Name", gCvar.esp_name);
			yPos = yPos + 14;
			gMenu.DrawCheckBox(x + 20, yPos + 45, "Distance", gCvar.esp_distance);
			yPos = yPos + 14;
			gMenu.DrawCheckBox(x + 20, yPos + 45, "SteamID", gCvar.esp_steamid);
			yPos = yPos + 14;
			gMenu.DrawCheckBox(x + 20, yPos + 45, "Healthbar", gCvar.esp_health);
			yPos = yPos + 14;
			gMenu.DrawCheckBox(x + 20, yPos + 45, "2D Box", gCvar.esp_2dbox);
			yPos = yPos + 14;
			gMenu.DrawCheckBox(x + 20, yPos + 45, "3D Box", gCvar.esp_3dbox);
			yPos = yPos + 14;
			gMenu.DrawCheckBox(x + 20, yPos + 45, "Long ESP", gCvar.esp_long);
			yPos = yPos + 14;
		}

		gMenu.DrawCheckBox(x + 10, yPos + 50, "Crosshair Enabled", gCvar.esp_crosshair);
		yPos = yPos + 14;
		if (gCvar.esp_crosshair)
		{
			gMenu.DrawCheckBox(x + 20, yPos + 55, "Plus", gCvar.esp_plus);
			yPos = yPos + 14;
			gMenu.DrawCheckBox(x + 20, yPos + 55, "Square", gCvar.esp_square);
			yPos = yPos + 14;
		}
	}

	if (gCvar.tabMis)
	{
		gCvar.tabAim = false;
		gCvar.tabESP = false;
		gCvar.tabCre = false;

		int yPos = y;

		gMenu.DrawCheckBox(x + 10, yPos + 40, "Chat Spam", gCvar.misc_chatspam);
		yPos = yPos + 14;

		if (gCvar.misc_chatspam)
		{
			gMenu.DrawCheckBox(x + 20, yPos + 45, "/ooc Mode", gCvar.misc_chatspamooc);
			yPos = yPos + 14;
		}

		gMenu.DrawCheckBox(x + 10, yPos + 50, "Bunny Hop", gCvar.misc_bunnyhop);
		yPos = yPos + 14;

		gMenu.DrawCheckBox(x + 10, yPos + 60, "Name Steal", gCvar.misc_namesteal);
		yPos = yPos + 14;

		gMenu.DrawCheckBox(x + 10, yPos + 70, "WaterMark", gCvar.misc_watermark);
		yPos = yPos + 14;

		gMenu.DrawCheckBox(x + 10, yPos + 80, "Anti-ScreenGrab", gCvar.misc_antisg);
		yPos = yPos + 14;

		gMenu.DrawCheckBox(x + 10, yPos + 90, "FlashLight Spam", gCvar.misc_flashspam);
		yPos = yPos + 14;

		gMenu.DrawCheckBox(x + 10, yPos + 100, "pSpeed(Shift)", gCvar.misc_speed);
		yPos = yPos + 14;

		gMenu.DrawCheckBox(x + 10, yPos + 110, "Fake Lag", gCvar.misc_fakelag);
		yPos = yPos + 14;
	}

	if (gCvar.tabCre)
	{
		gCvar.tabAim = false;
		gCvar.tabESP = false;
		gCvar.tabMis = false;

		gMenu.DrawButton(x + 20, y + 30, 60, 20, "Load Rage", "LoadRage");
		gMenu.DrawButton(x + 20, y + 60, 60, 20, "Load HvH", "LoadHVH");
		gMenu.DrawButton(x + 100, y + 30, 60, 20, "Save Rage", "BEEP");
		gMenu.DrawButton(x + 100, y + 60, 60, 20, "Save HvH", "BEEP");
	}
}

bool cMenu::MouseClick(int x, int y, int w, int h)
{
	POINT Pos;
	RECT mRect;
	HWND hWnd = ::GetActiveWindow();

	GetWindowRect(hWnd, (LPRECT)&mRect);
	GetCursorPos(&Pos);
	int cursorx = Pos.x - 05 - mRect.left;
	int cursory = Pos.y - 30 - mRect.top;
	bool Clicked;

	if (cursorx > x && cursorx < x + w && cursory > y && cursory < y + h && GetAsyncKeyState(VK_LBUTTON) & 1)
		Clicked = true;
	else
		Clicked = false;

	return Clicked;
}

bool cMenu::MouseIn(int x, int y, int w, int h)
{
	POINT Cur;
	GetCursorPos(&Cur);

	if (Cur.x > x && Cur.x < x + w && Cur.y > y && Cur.y < y + h)
	{
		return true;
	}

	return false;
}

void cMenu::GetMouse()
{
	/*POINT Cur;
	GetCursorPos(&Cur);
	gDrawing.FillRGBA(Cur.x, Cur.y, 5, 5, CHEAT_BLACK);*/

	POINT Pos;
	RECT mRect;
	HWND hWnd = ::GetActiveWindow();

	GetWindowRect(hWnd, (LPRECT)&mRect);
	GetCursorPos(&Pos);
	int cursorx = Pos.x - 05 - mRect.left;
	int cursory = Pos.y - 30 - mRect.top;

	//gDrawing.DrawString(cursorx, cursory, CHEAT_WHITE, "X");
}

bool Move[8][2];
POINT Cursor;
bool cMenu::Mover(int &X, int &Y, int W, int H, int index)
{
	for (int i = 0; i < 8; i++)
		if (Move[i][0] && i != index)
			return false;

	POINT Pos;
	RECT mRect;
	HWND hWnd = ::GetActiveWindow();

	GetWindowRect(hWnd, (LPRECT)&mRect);
	GetCursorPos(&Pos);
	int cursorx = Pos.x - 05 - mRect.left;
	int cursory = Pos.y - 30 - mRect.top;

	if (GetAsyncKeyState(VK_LBUTTON) < 0)
	{
		if (cursorx > X && cursorx < X + W && cursory >(Y - 20 + 14) && cursory < (Y - 20 + 21) + H || Move[index][0])
		{
			Move[index][0] = true;

			if (!Move[index][1])
			{
				Cursor.x = cursorx - X;
				Cursor.y = cursory - Y;
				Move[index][1] = true;

			}
		}
		else
		{
			Move[index][0] = false;
			Move[index][1] = false;
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) == 0 && Move[index][0])
	{
		Move[index][0] = false;
		Move[index][1] = false;
	}

	if (Move[index][0])
	{
		X = cursorx - Cursor.x;
		Y = cursory - Cursor.y;
	}

	return true;
}