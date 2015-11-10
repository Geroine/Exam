#pragma once
#include "ProjectHeader.h"

void startMenu(GameData &options);

enum eMenuButtons
{
eMenuNewGame = 0,
eMenuLoadGame,
eMenuOptions,
eMenuAbout,
eMenuExit
};

struct MElement
{
	char buttonName[_CHARSIZE_];
	int(*function)(GameData &options);
};

struct MMenu
{
	int MenuSize;
	MElement* ElemList;
};
