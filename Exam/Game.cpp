#include "Game.h"

void initGameData(GameData &data, int winX, int winY)
{
	data.state = eGSActive;
	data.options.mainSurface = initSurface(winX, winY, 0, 0);
	data.options.stackSize = 0;
	data.options.redraw = true;

	data.menu.currentMenu = NULL;
}

new_GFSurface* pushGameSuface(GameData &data, new_GFSurface &surface)
{
	new_GFSurface* copy = initSurface(surface.ccWidth, surface.ccHeight, surface.posX, surface.posY);
	blitSurface(*copy, surface, 0, 0);
	addElement(data.options.stackSurface, data.options.stackSize, copy);
	return copy;
}

void destGameData(GameData &data)
{
	delete2d(data.options.mainSurface->symbmap, data.options.mainSurface->ccHeight);
	delete[] data.options.mainSurface;
	if (data.options.stackSize > 0)
	{
		for (int i = 0; i < data.options.stackSize; i++)
		delete2d(data.options.stackSurface[i]->symbmap, data.options.mainSurface->ccHeight);
		delete[] data.options.stackSurface;
	}
	if (data.menu.currentMenu != NULL)
	destMMenu(*data.menu.currentMenu);
	clearSurface();
}

void changeGameMenu(GameData &data, MMenu &menu)
{
	data.menu.currentMenu = &menu;
}
// Разовый показ содержимого в main surface
int activeGraphic(GameData &data)
{
	static new_GFSurface* copy = initSurface(data.options.mainSurface->ccWidth, data.options.mainSurface->ccHeight, 0, 0);
	blitSurface(*copy,*data.options.mainSurface, 0, 0);
	if (data.options.redraw)
	{
		initSurface(*copy, data.options.mainSurface->ccWidth, data.options.mainSurface->ccHeight, 0, 0);
		data.options.redraw = false;
	}
//	initSurface(*data.options.mainSurface, data.options.mainSurface->ccWidth, data.options.mainSurface->ccHeight, 0, 0);
	for (int i = 0; i < data.options.stackSize; i++)
	{
		blitSurface(*data.options.mainSurface, *data.options.stackSurface[i],
			data.options.stackSurface[i]->posX, data.options.stackSurface[i]->posY);
	}

	for (int i = 0; i < data.options.mainSurface->ccHeight; i++)
	{
		for (int j = 0; j < data.options.mainSurface->ccWidth; j++)
		{
			if (!equalG4Block(copy->symbmap[i][j], data.options.mainSurface->symbmap[i][j]))
			{
				SetConsCurPos(j, i);
				SetColorBgTex(data.options.mainSurface->symbmap[i][j].bCol, data.options.mainSurface->symbmap[i][j].sCol);
				cout << data.options.mainSurface->symbmap[i][j].symb;
			}
		}
	}
	return 0;
}