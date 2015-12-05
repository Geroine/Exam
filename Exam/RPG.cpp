#include "RPG.h"

// По коду цвета индентифицируется тип объекта
int getRPGObjectType(RGBBlock &block)
{
	ObjectKey objkey;
	if (objkey.Solid == getColorCode(block)) return   eObjSolid;
	if (objkey.NoSolid == getColorCode(block)) return eObjNoSolid;
	if (objkey.Enemy == getColorCode(block)) return   eObjEnemy;
	if (objkey.Coin == getColorCode(block)) return    eObjCoin;
	if (objkey.Bonus == getColorCode(block)) return   eObjBonus;
	return eObjNoSolid;
}

 
//Инициализация статической карты мира
int initStatic(LevelData &data, char* mainname)
{
	char tilefileName[128];
	strcpy(tilefileName, mainname);
	strcat(tilefileName, NAME_TILE);
	char typefileName[128];
	strcpy(typefileName, mainname);
	strcat(typefileName, NAME_TYPE);

	BMPPicture* typeset = bmpReader(typefileName, UP_MIRROR);
	BMPPicture* tileset = bmpReader(tilefileName, UP_MIRROR);

	 
	//// Возвращается поверхность которая в последствии не удалится. Не забыть!
	data.stInfo.tileset = convertPicture(*tileset);

	data.stInfo.objStatSize = (tileset->info.biHeight/TILESIZE)*(tileset->info.biWidth/TILESIZE);

	LevelStaticObject* staticMap = new LevelStaticObject[data.stInfo.objStatSize];

	for (int k = 0, i = 0; k < typeset->info.biHeight; k++)
	{
		for (int m = 0; m < typeset->info.biWidth; m++)
		{
			staticMap[i].objectType = getRPGObjectType(typeset->bitmap[k][m]);
			staticMap[i].index = i++;
		}
	}
	data.stInfo.objStatMap = staticMap;
	return 0;
}

// В случае ошибок вызывается эта функция, чтобы вернуть рабочий но чистый объект
LevelStaticObject cleanStaticObject()
{
	LevelStaticObject stobj;
	stobj.objectType = eObjNoSolid;
	stobj.index = -1;
	return stobj;
}

// Возвращает объект по его индексу
LevelStaticObject getStaticObject(LevelStaticInfo &stInfo, int id)
{
	for (int i = 0; i < stInfo.objStatSize;i++)
	{
		if (stInfo.objStatMap[i].index == id)
		{
			LevelStaticObject stobj;
			stobj.objectType = stInfo.objStatMap[i].objectType;
			stobj.index = stInfo.objStatMap[i].index;
			return stobj;
		}
	}
	return cleanStaticObject();
}


/* 
Инициализация уровня
*/
int initLevel(LevelData &data, char* levelname)
{
	char mapFileName[128];
	strcpy(mapFileName, levelname);
	strcat(mapFileName, NAME_LEVEL);

	NumberArray level = readlvlFile(mapFileName);

	data.lvlInfo.mapSizeY = level.sizeY;
	data.lvlInfo.mapSizeX = level.sizeX;
	data.lvlInfo.levelmap = new LevelStaticObject*[level.sizeY];
	for (int i = 0; i < level.sizeY; i++)
	{
		data.lvlInfo.levelmap[i] = new LevelStaticObject[level.sizeX];
	}

	data.lvlInfo.screen = initSurface(data.winX, data.winY, 0, 0);

	for (int i = 0; i < data.lvlInfo.mapSizeY; i++)
	{
		for (int j = 0; j < data.lvlInfo.mapSizeX; j++)
		{
			data.lvlInfo.levelmap[i][j] = getStaticObject(data.stInfo, level.idArray[i][j]);
		}
	}
	int pixelSizeX = data.lvlInfo.mapSizeX*TILESIZE;
	int pixelSizeY = data.lvlInfo.mapSizeY*TILESIZE;
	data.lvlInfo.levelSurf = initSurface(pixelSizeX, pixelSizeY, 0, 0);

	for (int i = 0; i < data.lvlInfo.mapSizeY; i++)
	{
		for (int j = 0; j < data.lvlInfo.mapSizeX; j++)
		{
			int temp = data.lvlInfo.levelmap[i][j].index;
			blitTile(data,temp, TILESIZE,j,i);
		}
	}

	return 0;
}

// Функция принимает код тайла, размер, и позицию, где его записать
bool blitTile(LevelData &data, int index, int tilesize, int posX,int posY)
{
	int drawStartX = 0;
	int drawStartY = 0;
	int drawEndX = 0;
	int drawEndY = 0;

	for (int i = 0; i < data.stInfo.objStatSize; i++)
	{
		if (data.stInfo.objStatMap[i].index == index)
		{
			drawStartX = (data.stInfo.objStatMap[i].index % (data.stInfo.tileset->ccWidth/tilesize))*tilesize;
			drawStartY = (data.stInfo.objStatMap[i].index / (data.stInfo.tileset->ccWidth/tilesize))*tilesize;
			drawEndX = drawStartX+ tilesize;
			drawEndY = drawStartY+ tilesize;
			blitSurface(*data.lvlInfo.levelSurf, *data.stInfo.tileset,posX*tilesize, posY*tilesize,
				drawStartX, drawStartY, drawEndX, drawEndY);
			return true;
		}
	}
	return false;
}

LevelData* initLevelData(char* levelname, char* mainname, int winX, int winY)
{

	LevelData* data = new LevelData;
	data->lives = 3;
	data->score = 0;
	data->winX = winX;
	data->winY = winY;
	if (initStatic(*data, mainname) == ERROR_CODE) return NULL;
	if (initLevel(*data, levelname) == ERROR_CODE) return NULL;

	return data;
}



int activeRPG(GameData &data)
{
	static int screenPosX = 0;
	static int screenPosY = 0;
	static bool initialize = true;
	static new_GFSurface* screen;
	if (initialize)
	{
		screen = pushGameSuface(data, *data.RPG->lvlInfo.screen);
		initialize = false;
	}

	if (KB_Pressed(VK_RIGHT))
	{
		screenPosX += 16;
	}
	if (KB_Pressed(VK_LEFT)) 
	{
		screenPosX -= 16;
	}
	if (KB_Pressed(VK_UP)) screenPosY -= 16;
	if (KB_Pressed(VK_DOWN)) screenPosY += 16;
	if (screenPosX < 0) screenPosX = 0;
	if (screenPosY < 0) screenPosY = 0;
	blitSurface(*screen, *data.RPG->lvlInfo.levelSurf, 0, 0, screenPosX, screenPosY, data.RPG->lvlInfo.levelSurf->ccWidth, data.RPG->lvlInfo.levelSurf->ccHeight);


	return 0;
}