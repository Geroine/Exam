#include "Game.h"

void initGameData(GameData &data, int winX, int winY)
{
	data.state = eGSActive;
	data.options.mainSurface = new GFSurface;
	data.options.mainSurface->ccWidth = winX;
	data.options.mainSurface->ccHeight = winY;
	data.options.mainSurface->bitmap = new char*[winY];
	for (int i = 0; i < winY; i++)
		data.options.mainSurface->bitmap[i] = new char[winX];
	data.menu.posX = 0;
	data.menu.posY = 0;
	data.menu.currentMenu = NULL;
}

void destGameData(GameData &data)
{
	delete2d(data.options.mainSurface->bitmap, data.options.mainSurface->ccHeight);
	delete[] data.options.mainSurface;
	destMMenu(*data.menu.currentMenu);
}

void changeGameMenu(GameData &data, MMenu &menu)
{
	data.menu.currentMenu = &menu;
}