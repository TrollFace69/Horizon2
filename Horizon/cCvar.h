#ifndef __C_CVAR_H
#define __C_CVAR_H

#include "sdk.h"

class CCvars
{
public:
	// Aimbot //
	bool aim_enable;

	// ESP //
	bool esp_active, esp_name, esp_health, esp_steamid, esp_distance, esp_enemyonly, esp_visibilty, esp_2dbox, esp_3dbox, esp_long, esp_playerlight;
	bool esp_crosshair, esp_plus, esp_square;

	// Misc //
	bool misc_bunnyhop, misc_chatspam, misc_chatspamooc;
	bool misc_namesteal = false;
	bool misc_watermark = true;
	bool misc_antisg = true;
	bool misc_flashspam;
	bool misc_speed;
	bool misc_fakelag;

	// Removal //
	float rem_recoil = 0;
	float rem_spread = 0;

	// Menu //
	bool tabAim = false;
	bool tabESP = false;
	bool tabMis = false;
	bool tabCre = false;
	bool IsActive = false;

	int MenuX = 120;
	int MenuY = 120;
};

extern CCvars gCvar;

#endif