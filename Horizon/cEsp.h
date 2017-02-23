#ifndef __C_ESP_H_
#define __C_ESP_H_

#include "sdk.h"
#include "cDrawing.h"

class CEsp
{
public:
	void DrawWatermark(void);
	void DrawPlayerESP(int iIndex, IClientEntity* pEntity, C_BaseEntity* pLocal);
	void EntityESP(int iIndex, IClientEntity* pEntity, IClientEntity* pLocal);
	void DrawCrosshair(void);
private:
};

extern CEsp gEsp;

#endif