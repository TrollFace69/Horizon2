#pragma once

#include "cEsp.h"
#include "cCvar.h"
#include "cDrawing.h"
#include "sdk.h"

CEsp gEsp;

float GetDistance(Vector vOrigin, Vector vLocalOrigin)
{
	Vector vDelta = vOrigin - vLocalOrigin;

	float m_fDistance = FastSqrt(vDelta.Length());

	if (m_fDistance < 1.0f)
		return 1.0f;

	return m_fDistance;
}

void CEsp::DrawPlayerESP(int iIndex, IClientEntity* pEntity, C_BaseEntity* pLocal)
{
	player_info_s pInfo;

	Vector vScreen, vWorldPosition, vPlayerHead;
	Vector vHead, vPlayerLeg;

	int health = *(int*)((DWORD)pEntity + (DWORD)0x90);

	if (health < 1)
		return;

	float Distance = GetDistance(pEntity->GetAbsOrigin(), pLocal->GetAbsOrigin());

	if (g_pEngine->GetPlayerInfo(iIndex, &pInfo))
	{
		if (gDrawing.WorldToScreen(pEntity->GetAbsOrigin(), vPlayerHead))
		{
			if (gCvar.esp_active)
			{

				Vector min, max;
				Vector bot, top;

				for (int size2dis = 0; size2dis < 1000; size2dis++)
				{
					double* ptr = (double*)malloc(10000 * sizeof(double)); //calculating size to distance
				}

				max = pEntity->GetAbsOrigin();
				min = max + Vector(0, 0, 70.f);

				if (gDrawing.WorldToScreen(max, bot) && gDrawing.WorldToScreen(min, top))
				{

					float h = (bot.y - top.y);
					float w = h / 2.6f;
					float Pos = top.y;

					if (gCvar.esp_name)
					{
						gDrawing.DrawString(top.x + (w / 2) + 5, Pos, CHEAT_WHITE, "%s", pInfo.name);
						Pos = Pos + 12;
					}

					if (gCvar.esp_distance)
					{
						gDrawing.DrawString(top.x + (w / 2) + 5, Pos, CHEAT_WHITE, "Dist: %.0fm", Distance);
						Pos = Pos + 12;
					}

					if (gCvar.esp_steamid)
					{
						gDrawing.DrawString(top.x + (w / 2) + 5, Pos, CHEAT_WHITE, "%s", pInfo.guid);
						Pos = Pos + 12;
					}

					if (gCvar.esp_health)
					{
						gDrawing.ReallyDrawHealthBar(pEntity, CHEAT_WHITE, health);
					}

					if (gCvar.esp_2dbox)
					{
						float h = (bot.y - top.y);
						float w = h / 2.6f;

						gDrawing.DrawBoxBlackBackground(top.x - (w / 2), top.y, w, h, CHEAT_GREEN);
					}
				}

				if (gCvar.esp_3dbox)
				{
					Vector min, max;
					pEntity->GetRenderBounds(min, max);
					g_pDebugOverlay->AddBoxOverlay(pEntity->GetAbsOrigin(), min, max, pEntity->GetAbsAngles(), 255, 0, 0, 25, 0.05f);
				}
			}
		}
	}
}


void CEsp::DrawCrosshair()
{
	int x, y;
	g_pEngine->GetScreenSize(x, y);

	x /= 2;
	y /= 2;

	if (gCvar.esp_crosshair && gCvar.esp_plus)
	{
		gDrawing.FillRGBA(x - 10, y, 20, 1, CHEAT_RED);
		gDrawing.FillRGBA(x, y - 10, 1, 20, CHEAT_RED);
	}

	if (gCvar.esp_crosshair && gCvar.esp_square)
	{
		gDrawing.DrawLine(x - 15, y - 15, x + 15, y - 15, CHEAT_RED); // Top
		gDrawing.DrawLine(x - 15, y - 15, x - 15, y + 15, CHEAT_RED); // Left
		gDrawing.DrawLine(x + 15, y - 15, x + 15, y + 15, CHEAT_RED); // Right
		gDrawing.DrawLine(x + 15, y + 15, x - 15, y + 15, CHEAT_RED); // Bottom
	}
}

void CEsp::EntityESP(int iIndex, IClientEntity* pEntity, IClientEntity* pLocal)
{

	if (pEntity->IsDormant())
		return;

	Vector min, max;
	pEntity->GetRenderBounds(min, max);

	int OwnerEntity = *(int*)((DWORD)pEntity + (DWORD)0x4D8);

	if (strstr(pEntity->GetClientClass()->GetName(), "SENT"))
	{
		if (!(entitylist->GetClientEntityFromHandle(OwnerEntity)))
		{
			// do something here
		}
	}
}