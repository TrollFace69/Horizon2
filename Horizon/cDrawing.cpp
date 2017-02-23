#include "cDrawing.h"
#include "cMenu.h"

CDrawing gDrawing;

void CDrawing::Init()
{
	g_pEngine->GetScreenSize(gScreenSize.m_iWidth, gScreenSize.m_iHeight);

	m_pNormal = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(m_pNormal, "Arial", 14, 150, 0, 0, 0x200);

	m_pMenu = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(m_pMenu, "Arial", 16, 150, 0, 0, 0x200);
}

void CDrawing::SetFont(const char* facename, int tall, int weight, int flags)
{
	g_pSurface->SetFontGlyphSet(m_pNormal, facename, tall, weight, 0, 0, flags);
}

void CDrawing::DrawString(int x, int y, DWORD col, const char* pszText, ...)
{
	if (pszText == NULL)
		return;

	va_list va_alist;
	char buf[1024];
	va_start(va_alist, pszText);
	_vsnprintf(buf, sizeof(buf), pszText, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);
	g_pSurface->DrawSetTextFont(m_pNormal);
	g_pSurface->DrawSetTextColor(RED(col), GREEN(col), BLUE(col), ALPHA(col));
	g_pSurface->DrawSetTextPos(x, y);
	g_pSurface->DrawPrintText(wbuf, wcslen(wbuf));
}

void CDrawing::DrawString_w(int x, int y, DWORD dwColor, const char* pszText)
{
	if (pszText == NULL)
		return;

	va_list va_alist;
	char buf[1024];
	va_start(va_alist, pszText);
	_vsnprintf(buf, sizeof(buf), pszText, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);
	g_pSurface->DrawSetTextFont(m_pMenu);
	g_pSurface->DrawSetTextColor(RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor));
	g_pSurface->DrawSetTextPos(x, y);
	g_pSurface->DrawPrintText(wbuf, wcslen(wbuf));
}

/*void CDrawing::DrawString_i(int x, int y, DWORD dwColor, int pszText)
{
	if (pszText == NULL)
		return;

	va_list va_alist;
	char buf[1024];
	va_start(va_alist, pszText);
	_vsnprintf(buf, sizeof(buf), pszText, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);
	g_pSurface->DrawSetTextFont(m_pNormal);
	g_pSurface->DrawSetTextColor(RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor));
	g_pSurface->DrawSetTextPos(x, y);
	g_pSurface->DrawPrintText(wbuf, wcslen(wbuf));
}*/

void CDrawing::DrawLine(int x0, int y0, int x1, int y1, DWORD dwColor)
{
	g_pSurface->DrawSetColor(RED(dwColor), BLUE(dwColor), GREEN(dwColor), ALPHA(dwColor));
	g_pSurface->DrawLine(x0, y0, x1, y1);
}

void CDrawing::FillRGBA(int x, int y, int w, int h, DWORD dwColor)
{
	g_pSurface->DrawSetColor(RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor));
	g_pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void CDrawing::Border(int x, int y, int w, int h, DWORD dwColor)
{
	gDrawing.FillRGBA(x - 1, y - 1, w + 2, 1, dwColor);
	gDrawing.FillRGBA(x - 1, y, 1, h - 1, dwColor); 
	gDrawing.FillRGBA(x + w, y, 1, h - 1, dwColor);
	gDrawing.FillRGBA(x - 1, y + h - 1, w + 2, 1, dwColor);
}

bool CDrawing::ScreenTransform(CONST Vector& point, OUT Vector& screen)
{
	const VMatrix& worldToScreen = g_pEngine->WorldToScreenMatrix();
	screen.x = worldToScreen.m[0][0] * point.x + worldToScreen.m[0][1] * point.y + worldToScreen.m[0][2] * point.z + worldToScreen.m[0][3];
	screen.y = worldToScreen.m[1][0] * point.x + worldToScreen.m[1][1] * point.y + worldToScreen.m[1][2] * point.z + worldToScreen.m[1][3];

	FLOAT w;
	w = worldToScreen.m[3][0] * point.x + worldToScreen.m[3][1] * point.y + worldToScreen.m[3][2] * point.z + worldToScreen.m[3][3];
	screen.z = 0.0f;

	BOOL behind = FALSE;
	if (w < 0.001f)
	{
		behind = TRUE;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		FLOAT invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}

	return behind;
}

bool CDrawing::WorldToScreen(CONST Vector &origin, OUT Vector &screen)
{
	BOOL bRet = FALSE;

	if (!ScreenTransform(origin, screen))
	{
		INT width, height;
		g_pEngine->GetScreenSize(width, height);

		float fScreenX = width / 2;
		float fScreenY = height / 2;

		fScreenX += 0.5f * screen.x * width + 0.5f;
		fScreenY -= 0.5f * screen.y * height + 0.5f;

		screen.x = fScreenX;
		screen.y = fScreenY;

		bRet = TRUE;
	}

	return bRet;
}

void CDrawing::DrawBox(int x, int y, int x2, int y2, DWORD Color)
{
	gDrawing.FillRGBA(x - 1, y - 1, x2 + 2, 1, Color);
	gDrawing.FillRGBA(x - 1, y, 1, y2 - 1, Color);
	gDrawing.FillRGBA(x + x2, y, 1, y2 - 1, Color);
	gDrawing.FillRGBA(x - 1, y + y2 - 1, x2 + 2, 1, Color);
}

void CDrawing::DrawBoxBlackBackground(int x, int y, int width, int height, DWORD dwColor)
{
	gDrawing.FillRGBA(x, y + height - 1, width + 1, 1 + 2, COLORCODE(0, 0, 0, 255));
	gDrawing.FillRGBA(x - 1 - 1, y - 1, 1 + 2, height + 2, COLORCODE(0, 0, 0, 255));
	gDrawing.FillRGBA(x, y - 1 - 1, width + 1, 1 + 2, COLORCODE(0, 0, 0, 255));
	gDrawing.FillRGBA(x + width + 1 - 1, y - 1, 1 + 2, height + 2, COLORCODE(0, 0, 0, 255));

	gDrawing.FillRGBA(x, y + height, width + 1, 1, dwColor);
	gDrawing.FillRGBA(x - 1, y - 1, 1, height + 2, dwColor);
	gDrawing.FillRGBA(x, y - 1, width + 1, 1, dwColor);
	gDrawing.FillRGBA(x + width + 1, y - 1, 1, height + 2, dwColor);
}

void CDrawing::DrawHealthBar(int x, int y, float health, int w, int h, DWORD color)
{
	x -= w / 2;
	y -= h / 2;
	gDrawing.FillRGBA(x, y, w, h, COLORCODE(0, 0, 0, 255));
	UINT hw = (UINT)(((h - 2) * health) / 100);
	gDrawing.FillRGBA(x + 1, y + 1, w - 1, hw, color);
}

void CDrawing::DrawPlayerBox(CBaseEntity *pEnt, DWORD dwColor)
{
	if (pEnt == NULL)
		return;

	Vector min, max;

	max = pEnt->GetAbsOrigin();
	min = max + Vector(0, 0, 72.f);

	Vector bot, top;

	if (gDrawing.WorldToScreen(max, bot) && gDrawing.WorldToScreen(min, top))
	{
		float h = (bot.y - top.y);
		float w = h / 2.6f;

		gDrawing.DrawBoxBlackBackground(top.x - (w / 2), top.y, w, h, dwColor);
	}
}

void CDrawing::ReallyDrawHealthBar(IClientEntity *pEnt, DWORD dwColor, float health)
{

	if (pEnt == NULL)
		return;

	Vector min, max;

	max = pEnt->GetAbsOrigin();

	min = max + Vector(0, 0, 70.f);

	Vector bot, top;

	if (gDrawing.WorldToScreen(max, bot) && gDrawing.WorldToScreen(min, top))
	{

		float h = (bot.y - top.y);
		float w = h / 2.5f;

		int Red = 255 - (health*2.55);
		int Green = health*2.55;

		//Note to self: x is left and right, y is up and down
		gDrawing.DrawHealthBar(top.x - (w / 2) - 4, top.y - (h / -2) - 1.5, health, 5, h + 1, COLORCODE(Red, Green, 0, 255));
	}
}

bool CDrawing::GetBonePosition(CBaseEntity* pPlayer, Vector& Hitbox, int Bone)
{
	matrix3x4_t MatrixArray[128];

	if (!pPlayer->SetupBones(MatrixArray, 128, 0x00000100, g_pEngine->Time()))
		return FALSE;

	Hitbox = Vector(MatrixArray[Bone][0][3], MatrixArray[Bone][1][3], MatrixArray[Bone][2][3]);

	return true;
}

/*float sliderx = 0;
float SliderValue = 0;
char SliderValue[101];
void CDrawing::DrawSlider(float x, float y, float w, int min, int max, int rgb)
{
	float sliderw = 10.f;
	float sliderh = 15.f;

	POINT Pos;
	RECT mRect;
	HWND hWnd = ::GetActiveWindow();

	GetWindowRect(hWnd, (LPRECT)&mRect);
	GetCursorPos(&Pos);

	int cursorx = Pos.x - 05 - mRect.left;
	int cursory = Pos.y - 30 - mRect.top;

	if (rgb == 1)
	{
		float clickx = sliderx - cursorx;
		float moveto = sliderx - clickx - sliderw / 2;
		if (cursorx >= x - sliderw / 2 && cursory >= y - 2 && cursorx <= x + w + sliderw / 2 && cursory <= y + sliderh + 2)
		{
			if (GetAsyncKeyState(0x1))
			{
				sliderx = moveto;
			}
		}
		if (sliderx < x - sliderw / 2){ sliderx = x - sliderw / 2; }
		if (sliderx > x + w - sliderw / 2){ sliderx = x + w - sliderw / 2; }
		//Time To Draw
		gDrawing.FillRGBA(x, y, w, sliderh, CHEAT_GREY);
		gDrawing.FillRGBA(x, y, sliderx - x, sliderh, CHEAT_RED);
		//DrawBorderBox(x, y, w, sliderh, 1, fontBlack);
		gMenu.DrawButton(sliderx, y, sliderw, sliderh, "", NULL);
		SliderValue = ((max - min) / (w))*(sliderx - x + sliderw / 2);
		//sprintf(SliderValue, "  [%1.0f]", SliderValue);
		DrawString(SliderValue, x + w + 120, y + 1, fontRed, m_pfont);
		gDrawing.DrawString(x + w + 120, y + 1, CHEAT_WHITE, SliderValue);
		gDrawing.DrawString_w(x + 2, y + 3, CHEAT_WHITE, "HorizonHack");
	}
}*/