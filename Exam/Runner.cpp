#include "Runner.h"

//Готово
int getRunnerObjectType(RGBBlock &block)
{
	ObjectKey objkey;
	if (objkey.Solid == getColorCode(block)) return   eObjSolid;
	if (objkey.NoSolid == getColorCode(block)) return eObjNoSolid;
	if (objkey.Enemy == getColorCode(block)) return   eObjEnemy;
	if (objkey.Coin == getColorCode(block)) return    eObjCoin;
	if (objkey.Bonus == getColorCode(block)) return   eObjBonus;
	return eObjNoSolid;
}

//Готово
IndexTile getRunnerTileIndex(BMPPicture &mapset, RGBBlock &block)
{
	int index = 0;
	IndexTile itile;
	for (int i = 0; i < mapset.info.biHeight; i++)
	{
		for (int j = 0; j < mapset.info.biWidth; j++)
		{
			if (equalRGBBlock(mapset.bitmap[i][j], block))
			{
				itile.picIndex = index;
				itile.code = getColorCode(block);
				return itile;
			}
			index++;
		}
	}
	itile.picIndex = index;
	itile.code = getColorCode(rgbMask());
	return itile;
}
 
//Готово
int initStatic(LevelData &data, char* mainname)
{
	char tilefileName[128];
	strcpy(tilefileName, mainname);
	strcat(tilefileName, NAME_TILE);
	char mapfileName[128];
	strcpy(mapfileName, mainname);
	strcat(mapfileName, NAME_MAP);
	char typefileName[128];
	strcpy(typefileName, mainname);
	strcat(typefileName, NAME_TYPE);

	BMPPicture* tileset = bmpReader(tilefileName, UP_MIRROR);
	BMPPicture* mapset = bmpReader(mapfileName, UP_MIRROR);
	BMPPicture* typeset = bmpReader(typefileName, UP_MIRROR);
//	BMPPicture* levelmap = bmpReader(levelname, UP_MIRROR);
	 
	// Возвращается поверхность которая в последствии не удалится. Не забыть!
	data.stInfo.tileset = convertPicture(*tileset, &rgbMask());

	if (mapset->info.biHeight != typeset->info.biHeight) return ERROR_CODE; // Минное поле для ошибок
	if (mapset->info.biWidth != typeset->info.biWidth) return ERROR_CODE;
	if (mapset->info.biHeight*TILESIZE != tileset->info.biHeight) return ERROR_CODE;
	if (mapset->info.biWidth*TILESIZE != tileset->info.biWidth) return ERROR_CODE;

	data.stInfo.objStatSize = mapset->info.biHeight*mapset->info.biWidth;

	LevelStaticObject* staticMap = new LevelStaticObject[data.stInfo.objStatSize];

	for (int k = 0, i = 0; k < mapset->info.biHeight; k++)
	{
		for (int m = 0; m < mapset->info.biWidth; m++)
		{
			staticMap[i].objectType = getRunnerObjectType(typeset->bitmap[k][m]);
			staticMap[i].tileInfo = getRunnerTileIndex(*mapset, mapset->bitmap[k][m]);
			i++;
		}
	}
	data.stInfo.objStatMap = staticMap;
	return 0;
}

// Готово
LevelStaticObject cleanStaticObject()
{
	LevelStaticObject stobj;
	stobj.objectType = eObjNoSolid;
	stobj.tileInfo.code = getColorCode(rgbMask());
	stobj.tileInfo.picIndex = -1;
	return stobj;
}

// Готово
LevelStaticObject getStaticObject(LevelData &data, unsigned code)
{
	if (code == getColorCode(rgbMask())) return cleanStaticObject();
	LevelStaticObject stobj;
	for (int i = 0; i < data.stInfo.objStatSize;i++)
	{
		if (data.stInfo.objStatMap[i].tileInfo.code == code)
		{
			stobj.objectType = data.stInfo.objStatMap[i].objectType;
			stobj.tileInfo = data.stInfo.objStatMap[i].tileInfo;
			return stobj;
		}
	}
	return cleanStaticObject();
}



int initLevel(LevelData &data, char* levelname)
{
	char backFileName[128];
	strcpy(backFileName, levelname);
	strcat(backFileName, NAME_BKG);
	char mapFileName[128];
	strcpy(mapFileName, levelname);
	strcat(mapFileName, NAME_LEVEL);
	data.lvlInfo.background = picToSurface(backFileName, UP_MIRROR);
	if (!data.lvlInfo.background) return ERROR_CODE;
	BMPPicture* levelmap = bmpReader(mapFileName, UP_MIRROR);
	if (!levelmap) return ERROR_CODE;
	data.lvlInfo.mapSizeY = levelmap->info.biHeight;
	data.lvlInfo.mapSizeX = levelmap->info.biWidth;
	data.lvlInfo.levelmap = new LevelStaticObject*[data.lvlInfo.mapSizeY];
	for (int i = 0; i < data.lvlInfo.mapSizeY; i++)
	{
		data.lvlInfo.levelmap[i] = new LevelStaticObject[data.lvlInfo.mapSizeX];
	}
	data.lvlInfo.screen = initSurface(data.winX, data.winY, 0, 0);

	for (int i = 0; i < data.lvlInfo.mapSizeY; i++)
	{
		for (int j = 0; j < data.lvlInfo.mapSizeX; j++)
		{
			data.lvlInfo.levelmap[i][j] = getStaticObject(data, getColorCode(levelmap->bitmap[i][j]));
		}
	}
	data.lvlInfo.levelSurf = initSurface(data.lvlInfo.mapSizeX*TILESIZE, data.lvlInfo.mapSizeY*TILESIZE, 0, 0);

	for (int i = 0; i < data.lvlInfo.mapSizeY; i++)
	{
		for (int j = 0; j < data.lvlInfo.mapSizeX; j++)
		{
			blitTile(data,getColorCode(levelmap->bitmap[i][j]), TILESIZE,j,i);
		}
	}

	return 0;
}

bool blitTile(LevelData &data, unsigned code, int tilesize, int posX,int posY)
{
	if (code == getColorCode(rgbMask())) return true;
	int drawStartX = 0;
	int drawStartY = 0;
	int drawEndX = 0;
	int drawEndY = 0;

	for (int i = 0; i < data.stInfo.objStatSize; i++)
	{
		if (data.stInfo.objStatMap[i].tileInfo.code == code)
		{
			drawStartX = (data.stInfo.objStatMap[i].tileInfo.picIndex % (data.stInfo.tileset->ccWidth/tilesize))*tilesize;
			drawStartY = (data.stInfo.objStatMap[i].tileInfo.picIndex / (data.stInfo.tileset->ccWidth/tilesize))*tilesize;
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

	data->gravity = 8;
	data->friction = 0.5;
	data->lives = 3;
	data->score = 0;
	data->winX = winX;
	data->winY = winY;
	if (initStatic(*data, mainname) == ERROR_CODE) return NULL;
	if (initLevel(*data, levelname) == ERROR_CODE) return NULL;

	return data;
}

int activeRunner(GameData &data)
{
	static int screenPosX = 0;
	static int screenPosY = 0;
	static bool initialize = true;
	static new_GFSurface* screen;
	if (initialize)
	{
		screen = pushGameSuface(data, *data.runner->lvlInfo.screen);
		initialize = false;
	}

	if (KB_Pressed(VK_RIGHT)) screenPosX--;
	if (KB_Pressed(VK_LEFT)) screenPosX++;
	blitSurface(*screen, *data.runner->lvlInfo.levelSurf, screenPosX, screenPosY);




	return 0;
}