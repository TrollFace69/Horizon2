#ifndef __PANELS_H_
#define __PANELS_H_


#include "sdk.h"

#pragma once

typedef struct CScreenSize_t
{
	int m_iHeight;
	int m_iWidth;
} CScreenSize;

extern CScreenSize_t gScreenSize;

#endif