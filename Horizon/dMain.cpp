#include "sdk.h"
#include "cDrawing.h"
#include "vmthook.h"
#include "cEsp.h"
#include "cCvar.h"
#include "cMenu.h"
#include "cName.h"

IBaseClientDLL*                                 g_pClient = NULL;
ISurface*										g_pSurface = NULL;
IPanel*											g_pPanel = NULL;
IVEngineClient*                                 g_pEngine = NULL;
IClientEntityList*                              entitylist = NULL;
IEngineTrace*                                   g_pEngineTrace = NULL;
IVModelInfo*                                    g_pModelInfo = NULL;
CInput*                                         g_pInput = NULL;
IVDebugOverlay*                                 g_pDebugOverlay = NULL;
IGameEventManager2*                             g_pEventManager = NULL;
ICvar*                                          g_pICvar = NULL;
ISteamFriends*                                  g_pSteamFriends = NULL;
IMaterialSystem*                                g_pMaterial = NULL;

//=============================================//
tPaintTraverse			oPaintTraverse;
tCreateMove				oCreateMove;
tCMatRenderContext_ReadPixels oCMatRenderContext_ReadPixels;

HANDLE DebugConsole;
DWORD dw_msg_size;

typedef void(__thiscall *tCMatRenderContext_ReadPixels)(void *_this, int x, int y, int w, int h, unsigned char *buffer, void *format);

void BuildDebugConsole(void)
{
	//create the console
	AllocConsole();
	DebugConsole = (HANDLE)::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTitle("Horizon Hack");
}

void SendConsoleMessage(const char* msg, ...)
{
	::WriteConsole(DebugConsole, msg, strlen(msg), &dw_msg_size, NULL);
}

bool bKeyPress[256];
bool IsKeyPressed(int iKey)
{
	if (GetAsyncKeyState(iKey))
	{
		if (!bKeyPress[iKey])
		{
			bKeyPress[iKey] = true;
			return true;
		}
	}
	else
		bKeyPress[iKey] = false;
	return false;
}

inline int rand_range(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

static bool bOnceCM = false;
void _fastcall hkCreateMove(void* thisptr, DWORD _EDX, int sequence_number, float input_sample_frametime, bool active)
{
	oCreateMove(thisptr, _EDX, sequence_number, input_sample_frametime, active);

	if (gCvar.misc_speed && GetAsyncKeyState(VK_LSHIFT))
		g_pEngine->ClientCmd("say +Speed");

	if (gCvar.misc_fakelag)
		g_pEngine->ClientCmd("say +Lag");

	if (gCvar.misc_flashspam)
	{
		g_pEngine->ClientCmd("impulse 100");
		g_pEngine->ClientCmd("impulse 100");
	}

	if (gCvar.misc_namesteal)
		g_pEngine->ClientCmd("echo I am Stealing names!");

	if (!bOnceCM)
	{
		SendConsoleMessage("-CreateMove Hooked!\n");
		bOnceCM = true;
	}

	if (g_pEngine->IsInGame() || g_pEngine->IsConnected())
	{

		if (gCvar.misc_chatspam)
		{
			if (!gCvar.misc_chatspamooc)
			{
				g_pEngine->ClientCmd("say NerdPaste Leaked by TeslaEngineerCoder MultiPlayerGameSnacking.com");
			}
			else
			{
				g_pEngine->ClientCmd("say /ooc NerdPaste Leaked by TeslaEngineerCoder at MultiPlayerGameSnacking.com");
			}
		}

		if (gCvar.misc_bunnyhop)
		{
			//nigger shit
		}
	}
}

static bool bOnce = false;
void __fastcall hkPaintTraverse(void* thisptr, void* EDX, VPANEL vguiPanel, bool forceRepaint, bool allowForce)
{
	try
	{
		oPaintTraverse(thisptr, EDX, vguiPanel, forceRepaint, allowForce);

		static VPANEL OverlayPopupPanel;
		const char* pszPanelN = g_pPanel->GetClassName(vguiPanel);
		if (pszPanelN[0] == 'O' && pszPanelN[7] == 'P')
		{
			if (vguiPanel == OverlayPopupPanel)
				OverlayPopupPanel = vguiPanel;
			if (bOnce == false || !bOnce)
			{
				gDrawing.Init();
				SendConsoleMessage("-PaintTraverse Hooked!\n");
				bOnce = true;
			}

			if (IsKeyPressed(VK_INSERT))
				gCvar.IsActive = !gCvar.IsActive;

			if (gCvar.IsActive)
			{
				gMenu.Render(gCvar.MenuX, gCvar.MenuY, 450, 300);
			}

			if (g_pEngine->IsInGame() || g_pEngine->IsConnected())
			{
				for (int iIndex = 0; iIndex < entitylist->GetHighestEntityIndex(); iIndex++)
				{
					CBaseEntity* pPlayer = (C_BaseEntity*)entitylist->GetClientEntity(g_pEngine->GetLocalPlayer());

					if (!pPlayer)
						continue;

					CBaseEntity* pBaseEntity = (C_BaseEntity*)entitylist->GetClientEntity(iIndex);

					if (pBaseEntity == NULL)
						continue;

					if (!gCvar.esp_long)
					{
						if (pBaseEntity->IsDormant())
							continue;
					}

					if (pBaseEntity == pPlayer)
						continue;

					gEsp.DrawPlayerESP(iIndex, pBaseEntity, pPlayer);
					gEsp.EntityESP(iIndex, pBaseEntity, pPlayer);
				}

				if (gCvar.misc_watermark)
				{
					gDrawing.DrawString(20, 20, COLORCODE(255, 0, 0, 255), "Horizon Hack Beta");
				}
				gEsp.DrawCrosshair();
			}
		}
	}
	catch (...)
	{
		Beep(750, 2000);
	}
}

DWORD WINAPI init(LPVOID lpArguments)
{

	if (g_pClient == NULL)
	{
		CreateInterfaceFn EngineFactory = Sys_GetFactory("engine.dll");
		g_pEngine = (IVEngineClient*)EngineFactory("VEngineClient015", NULL);
		SendConsoleMessage("Intilazing...\n");
		SendConsoleMessage("--------------------\n");
		SendConsoleMessage("-->engine.dll\n");
		SendConsoleMessage("-Got IVEngineClient!\n");
		g_pEngineTrace = (IEngineTrace*)EngineFactory(INTERFACEVERSION_ENGINETRACE_CLIENT, NULL);
		SendConsoleMessage("-Got IEngineTrace!\n");
		g_pModelInfo = (IVModelInfo*)EngineFactory(VMODELINFO_CLIENT_INTERFACE_VERSION, NULL);
		SendConsoleMessage("-Got IVModelInfo!\n");
		g_pDebugOverlay = (IVDebugOverlay*)EngineFactory(VDEBUG_OVERLAY_INTERFACE_VERSION, NULL);
		SendConsoleMessage("-Got IVDebugOverlay!\n");
		g_pEventManager = (IGameEventManager2*)EngineFactory(INTERFACEVERSION_GAMEEVENTSMANAGER2, NULL);
		SendConsoleMessage("-Got IGameEventManager2!\n");

		CreateInterfaceFn ClientFactory = Sys_GetFactory("client.dll");
		SendConsoleMessage("--------------------\n");
		SendConsoleMessage("-->client.dll\n");
		entitylist = (IClientEntityList*)ClientFactory("VClientEntityList003", NULL);
		SendConsoleMessage("-Got IClientEntityList!\n");
		g_pClient = (IBaseClientDLL*)ClientFactory(V_CLIENT_INTERFACE_VERSION, NULL);
		SendConsoleMessage("-Got IBaseClientDLL!\n");

		CreateInterfaceFn VGUIMatFactory = Sys_GetFactory("vguimatsurface.dll");
		SendConsoleMessage("--------------------\n");
		SendConsoleMessage("-->vguimatsurface.dll\n");
		g_pSurface = (ISurface*)VGUIMatFactory("VGUI_Surface030", NULL);
		SendConsoleMessage("-Got ISurface!\n");

		CreateInterfaceFn VGUI2Factory = Sys_GetFactory("vgui2.dll");
		SendConsoleMessage("--------------------\n");
		SendConsoleMessage("-->vgui2.dll\n");

		CreateInterfaceFn VStd = Sys_GetFactory("vstdlib.dll");
		SendConsoleMessage("--------------------\n");
		SendConsoleMessage("-->vstdlib.dll\n");
		g_pICvar = (ICvar*)VStd(CVAR_INTERFACE_VERSION, NULL);
		SendConsoleMessage("-Got ICvar!\n");
		SendConsoleMessage("--------------------\n");

		if (!g_pPanel)
		{
			g_pPanel = (IPanel*)VGUI2Factory("VGUI_Panel009", NULL);
			if (g_pPanel)
			{
				void __fastcall hkPaintTraverse(void* thisptr, void* EDX, VPANEL vguiPanel, bool forceRepaint, bool allowForce);

				CVMTHookManager* pPanelHook = new CVMTHookManager;
				if (pPanelHook->bInitialize((PDWORD*)g_pPanel)) 
				{ 
					oPaintTraverse = (tPaintTraverse)pPanelHook->dwHookMethod((DWORD)hkPaintTraverse, 41); 
				}
				::WriteConsole(DebugConsole, "-PaintTraverse Ready!\n", strlen("-PaintTraverse Ready!\n"), &dw_msg_size, NULL);
			}
		}

		if (g_pClient)
		{
			void __fastcall hkCreateMove(void* pThis, DWORD EDX, int sequence_number, float f01, bool b01); 

			CVMTHookManager* pClientHook = new CVMTHookManager;
			if (pClientHook->bInitialize((PDWORD*)g_pClient))
			{
				oCreateMove = (tCreateMove)pClientHook->dwHookMethod((DWORD)hkCreateMove, 21);
			}
			SendConsoleMessage("-CreateMove Ready!\n");
		}

	}
	return 0;
}

DWORD WINAPI DllMain(HMODULE hDll, DWORD dwReasonForCall, LPVOID lpReserved)
{

	static HANDLE hThread = INVALID_HANDLE_VALUE;
	static DWORD dwExitCode;
	if (dwReasonForCall == DLL_PROCESS_ATTACH)
	{
		BuildDebugConsole();
		DisableThreadLibraryCalls(hDll);
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)init, NULL, 0, NULL);
		return (hThread != INVALID_HANDLE_VALUE);
	}
	return 0;
}