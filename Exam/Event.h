#pragma once
#include "ProjectHeader.h"

enum eKBKeys
{
	vk_W = 0x57,
	vk_A = 0x41,
	vk_S = 0x53,
	vk_D = 0x44
};

bool KB_Pressed(int Key);
bool KB_Hit(int Key);