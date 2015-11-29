#include "ProjectHeader.h"

int func1(GameData &data)
{
	cout << "func1" << endl;
	return 0;
}

int func2(GameData &data)
{
	cout << "      func2" << endl;
	return 0;
}

int func3(GameData &data)
{
	cout << "            func3" << endl;
	return 0;
}

int main(int argc, char* args[])
{
	int mainsurfX = 64;
	int mainsurfY = 64;
	GameData data;
	initGameData(data, mainsurfX, mainsurfY);
	//SetConsWinSize(mainsurfX*9, mainsurfY*10);

	for (int i = 0; i < 100; i++)
	{
		picToSurface("pic/mario4.bmp");
	}

	Tasker tasker = processPrepair();

	/*MMenu tMenu1;
	pushElement(tMenu1, "function 1", func1);
	pushElement(tMenu1, "function 2", func2);

	MMenu tMenu2;
	pushElement(tMenu2, "function 1", func1);
	pushElement(tMenu2, "function 3", func3);

	MMenu mMenu;
	pushElement(mMenu, "TestMenu 1", &tMenu1);
	pushElement(mMenu, "TestMenu 2", &tMenu2);

	changeGameMenu(data, mMenu);

	for (int i = 0; i < data.menu.currentMenu->menuSize; i++)
	{
		cout << data.menu.currentMenu->elemList[i].buttonName << endl;
		cout << " - - - - - - - " << endl;
		for (int j = 0; j < data.menu.currentMenu->elemList[i].subMenu->menuSize; j++)
		{
			cout << data.menu.currentMenu->elemList[i].subMenu->elemList[j].buttonName << endl;
			cout << "     _____     _____" << endl;
			data.menu.currentMenu->elemList[i].subMenu->elemList[j].function(data);
			cout << "     _____     _____" << endl;
		}
		cout << endl;
	}*/
	bmpClear();
	destGameData(data);
	return 0;
}