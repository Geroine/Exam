#include "Menu.h"

void initMMenu(MMenu &menu)
{
	menu.elemList = NULL;
	menu.MMtype = eMMMainMenu;
	menu.menuSize = 0;
}

void pushElement(MMenu &menu, char* name, mainFunctionType func)
{
	if (menu.MMtype == -1)
		initMMenu(menu);

	MElement* newElement = new MElement;
	newElement->MEtype = eMEFunction;
	newElement->buttonName = name;
	newElement->function = func;
	newElement->subMenu = NULL;
	addElement(menu.elemList, menu.menuSize, newElement);
}

void pushElement(MMenu &menu, char* name, MMenu *addMenu)
{
	if (menu.MMtype == -1)
		initMMenu(menu);

	MElement* newElement = new MElement;
	newElement->MEtype = eMESubMenu;
	newElement->buttonName = name;
	newElement->function = NULL;
	newElement->subMenu = addMenu;
	addElement(menu.elemList, menu.menuSize, newElement);
}

bool destMMenu(MMenu &menu)
{
	if (menu.menuSize < 1) return false;
	for (int i = 0; i < menu.menuSize; i++)
	{
		//if (menu.elemList[i].buttonName != 0)        Имена кнопок я передаю в самом коде, и выходит, что эти строки - константные.
		//	delete[] menu.elemList[i].buttonName;		Я не могу их удалять. Но в будущем возможно я внутри игры буду создавать и
		//												редактировать меню, тогда то я сюда и вернусь. Буду что-то думать...

		if (menu.elemList[i].MEtype == eMESubMenu)
		{
			destMMenu(*menu.elemList[i].subMenu);
		}
	}
	delete[] menu.elemList;
	return true;
}


int activeMenu(GameData &options)
{
	static bool isActive = false;
	static MMenu *activeMenu = options.menu.currentMenu;
	static int height = options.menu.height;
	static int width = options.menu.width;
	static new_GFSurface menuSurface;

	if (isActive == true)
	{
		activeMenu = options.menu.currentMenu;
		height = options.menu.height;
		width = options.menu.width;

		delete2d(menuSurface.symbmap, menuSurface.ccHeight);
		menuSurface.symbmap = new G4Block*[height];
		for (int i = 0; i < height; i++)
		{
			menuSurface.symbmap[i] = new G4Block[width];
		}
	}
	// Тут не закончено

	return 0;
}

int ElementDown(GameData &options)
{
	return 0;
}