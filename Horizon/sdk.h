// ur gay fegit
#pragma once

#ifndef CLIENT_DLL
#define CLIENT_DLL
#endif

#define SECURITY_WIN32
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <stringapiset.h>
#include <math.h>
#include <xstring>
#include <WinUser.h>
#include <stdio.h>
#include <wingdi.h>

// Public
#include "public\\cdll_int.h"
#include "public\\iprediction.h"
#include "public\\bone_setup.h"
#include "public\\icliententitylist.h"
#include "public\\ienginevgui.h"
#include "public\\IGameUIFuncs.h"
#include "public\\dlight.h"
#include "public\\r_efx.h"
#include "public\\igameevents.h"
#include "public\\view_shared.h"
#include "public\\inetchannelinfo.h"
#include "public\\iachievementmgr.h"
#include "public\\steam\\steam_api.h"
#include "public\\steam\\isteamuserstats.h"

// Client
#include "game\\client\\imessagechars.h"
#include "game\\client\\iclientmode.h"
#include "game\\client\\cliententitylist.h"
#include "game\\client\\cdll_client_int.h"
#include "game\\client\\cbase.h"
#include "game\\client\\c_baseanimating.h"
#include "game\\client\\c_basecombatweapon.h"
#include "game\\client\\c_baseplayer.h"
#include "game\\client\\enginesprite.h"
#include "game\\client\\input.h"
#include "game\\client\\c_playerresource.h"
#include "game\\client\\iviewrender.h"
#include "game\\client\\viewrender.h"
#include "game\\client\\game_controls\\commandmenu.h"
#include "game\\client\\hudelement.h"

// Engine
#include "public\\engine\\ivmodelrender.h"
#include "public\\engine\\ivdebugoverlay.h"
#include "public\\engine\\ivmodelinfo.h"
#include "public\\ivrenderview.h"
#include "public\\engine\\IEngineTrace.h"
#include "public\\engine\\IEngineSound.h"

// Material System
#include "public\\materialsystem\\imaterialsystemstub.h"
#include "public\\materialsystem\\itexture.h"
#include "public\\materialsystem\\IMaterialVar.h"
#include "public\\tier1\\checksum_md5.h"
#include "public\\materialsystem\\imaterial.h"
// VGUI
#include "public\\matsys_controls\\matsyscontrols.h"
#include "public\\vgui\\IClientPanel.h"
#include "public\\vgui\\IPanel.h"
#include "public\\vgui\\ISurface.h"
#include "public\\vgui\\ILocalize.h"
#include "public\\collisionutils.h"
#include "public\\vstdlib\\random.h"

//ICVAR
#include "public\\icvar.h"
#include "public\\tier1\\convar.h"
#include "public\\tier1\\iconvar.h"

// VGUI Controls
#include "public\\vgui_controls\\Panel.h"

// VGUI Material Surface
#include "public\\VGuiMatSurface\\IMatSystemSurface.h"
#include "public\\mathlib\\vector.h"
#include "C:\HL-SDK\public\public\mathlib\vector.h"

// Shared
#include "game\\shared\\usermessages.h"
#include "game\\shared\\basecombatweapon_shared.h"
#include "game\\shared\\takedamageinfo.h"
#include "game\\shared\\igamemovement.h"

#pragma comment(lib, "C:/HL-SDK/public/lib/public/tier0.lib")
#pragma comment(lib, "C:/HL-SDK/public/lib/public/tier1.lib")
#pragma comment(lib, "C:/HL-SDK/public/lib/public/tier2.lib")
#pragma comment(lib, "C:/HL-SDK/public/lib/public/tier3.lib")
#pragma comment(lib, "C:/HL-SDK/public/lib/public/mathlib.lib")
#pragma comment(lib, "C:/HL-SDK/public/lib/public/vstdlib.lib")

#define MASK_AIMBOT 0x200400B
#define CONTENTS_HITBOX 0x40000000
#define PI 3.14159265358979323846f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define square( x ) ( x * x )
#define RADPI 57.295779513082f
#define SQUARE( a ) a*a

typedef float matrix3x4[3][4];

typedef void(__fastcall *tPaintTraverse)(void*, void*, unsigned int, bool, bool);
typedef void* (__fastcall* tCreateMove)(void*, DWORD, int, float, bool);
typedef void* (__stdcall* tIN_KeyEvent)(int, int, const char *);
typedef void(__thiscall *tCMatRenderContext_ReadPixels)(void*, int, int, int, int, unsigned char*, void*);
//typedef void(__thiscall *CUserCmd)(void *, DWORD, int);
typedef void(__stdcall *CUserCmd_)(int sequence_number);



extern IBaseClientDLL* g_pClient;
extern vgui::ISurface* g_pSurface;
extern vgui::IPanel* g_pPanel;
extern IVEngineClient* g_pEngine;
extern IVModelInfo* g_pModelInfo;
extern IVDebugOverlay* g_pDebugOverlay;
extern IGameEventManager2* g_pEventManager;
extern CInput* g_pInput;
extern ICvar* g_pICvar;
extern ISteamFriends* g_pSteamFriends;
extern IMaterialSystem* g_pMaterial;
extern IEngineTrace* g_pEngineTrace;

typedef unsigned long HFont;

#define V_CLIENT_INTERFACE_VERSION "VClient017"
#define V_ENGLINE_CLIENT_INTERFACE_VERSION "VEngineClient015"
#define MATH_PI 3.14159265

#define CHEAT_ORANGE    COLORCODE( 255, 100, 000, 255 )
#define CHEAT_YELLOW    COLORCODE( 255, 255, 0, 255 )
#define CHEAT_PURPLE    COLORCODE( 55, 25, 128, 255 )
#define CHEAT_RED       COLORCODE( 255, 0, 0, 255 )
#define CHEAT_GREEN		COLORCODE( 0, 255, 0, 255 )
#define CHEAT_BLUE		COLORCODE( 0, 0, 255, 255 )
#define CHEAT_BLACK		COLORCODE( 0, 0, 0, 255 )
#define CHEAT_WHITE		COLORCODE( 255, 255, 255, 255 )
#define CHEAT_GREY		COLORCODE( 120, 120, 120, 255 )


enum playercontrols
{
	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_ATTACK2 = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_ALT1 = (1 << 14),
	IN_ALT2 = (1 << 15),
	IN_SCORE = (1 << 16),   // Used by client.dll for when scoreboard is held down
	IN_SPEED = (1 << 17),   // Player is holding the speed key
	IN_WALK = (1 << 18),    // Player holding walk key
	IN_ZOOM = (1 << 19),    // Zoom key for HUD zoom
	IN_WEAPON1 = (1 << 20), // weapon defines these bits
	IN_WEAPON2 = (1 << 21), // weapon defines these bits
	IN_BULLRUSH = (1 << 22),
};