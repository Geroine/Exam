#pragma once
#include "ProjectHeader.h"

typedef int(*mainFunctionType)(GameData& options);

enum eMenuButtons
{
	eMBNewGame = 0,
	eMBLoadGame,
	eMBOptions,
	eMBAbout,
	eMBExit
};

enum eMElementType
{
	eMESubMenu = 0,
	eMEFunction = 1
};

enum eMMlementType
{
	eMMMainMenu = 0,
	eMMSecMenu
};

struct MElement;

struct MMenu
{
	int MMtype = -1;
	int menuSize;
	MElement* elemList;
};

struct MElement
{
	int MEtype;
	char* buttonName;
	int(*function)(GameData &options);
	MMenu* subMenu; // Не забыть удалить меню
};

void initMMenu(MMenu &menu);

void pushElement(MMenu &menu, char* name, mainFunctionType func);

void pushElement(MMenu &menu, char* name, MMenu *addMenu);

bool destMMenu(MMenu &menu);

struct new_GFSurface;

int activeMenu(GameData &options);
