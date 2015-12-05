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
	halfSurface(*data.RPG->lvlInfo.screen);
	return 0;
}

int main(int argc, char* args[])
{
	int mainsurfX = 90;
	int mainsurfY = 75;

	GameData data;
	initGameData(data, mainsurfX, mainsurfY);
	data.RPG = initLevelData("rpg", "rpg", mainsurfX, mainsurfY);
	SetConsWinSize(mainsurfX*9, mainsurfY*10);
	
	new_GFSurface* surf = initBackground(mainsurfX, mainsurfY, CC_Cyan);
	
	pushGameSuface(data, *surf);
	//pushGameSuface(data, *picToSurface("pic/pict.bmp", UP_MIRROR));



	//int mainsurfX = 128;
	//int mainsurfY = 64;
	//GameData data;
	//initGameData(data, mainsurfX, mainsurfY);
	//SetConsWinSize(mainsurfX * 9, mainsurfY * 10);

	//new_GFSurface* cpic = picToSurface("spr/RPG_main.bmp", UP_MIRROR);
	//new_GFSurface* back = initSurface(mainsurfX, mainsurfY, 0, 0);
	//blitSurface(*back, *cpic, 16, 2, 48, 48, 64, 64);
	//blitSurface(*back, *cpic, 25, 41, 48+16, 48, 64 + 16, 64);
	//blitSurface(*back, *cpic, 13, 2, 80, 0, 80 + 16, 16);
	//back = pushGameSuface(data, *back);
	Tasker tasker = processPrepair();
	//
	processPush(tasker, activeRPG, "RPG");
	processPush(tasker, activeGraphic, "graph");
	while (true)
	{

		processIterator(data, tasker);
	}
	return 0;
}

//int mainsurfX = 168;
//int mainsurfY = 168;
//GameData data;
//initGameData(data, mainsurfX, mainsurfY);
//SetConsWinSize(mainsurfX*9, mainsurfY*10);


//new_GFSurface* cpic = picToSurface("spr/RPG_main.bmp", UP_MIRROR);

//pushGameSuface(data, *initBackground(mainsurfX,mainsurfY,CC_Black));
//pushGameSuface(data, *cpic);

//Tasker tasker = processPrepair();
//processPush(tasker, activeGraphic, "graph");
//while (true)
//{
//	processIterator(data, tasker);
//}

//destGameData(data);

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