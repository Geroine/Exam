#include "RPG.h"

// По коду цвета индентифицируется тип объекта
int getRPGObjectType(RGBBlock &block)
{
	ObjectKey objkey;
	if (objkey.Solid == getColorCode(block)) return   eObjSolid;
	if (objkey.NoSolid == getColorCode(block)) return eObjNoSolid;
	if (objkey.Heart == getColorCode(block)) return   eObjHeart;
	if (objkey.Start == getColorCode(block)) return    eObjStart;
	if (objkey.Finish == getColorCode(block)) return   eObjFinish;
	return eObjNoSolid;
}

// Возвращает указатель на полную или пустую маску. С помощью масок можно определить столкновения в игровом мире
ObjectMask* getFullMask(int type,int sizeX, int sizeY, int clearcode)
{
	static int size = 0;
	static ObjectMask** maskMap = new ObjectMask*[size];
	if (clearcode == MASK_CLEAR)
	{
		for (int i = 0; i < size; i++)
		{
			delete2d(maskMap[i]->mask, maskMap[i]->sizeY);
		}
		delete2d(maskMap,size);
		size = 0;
		return NULL;
	}

	ObjectMask* newmask = new ObjectMask;
	newmask->sizeX = sizeX;
	newmask->sizeY = sizeY;
	newmask->mask = new bool*[sizeY];
	for (int i = 0; i < sizeY; i++)
	{
		newmask->mask[i] = new bool[sizeX];
		for (int j = 0; j < sizeY; j++)
		{
			if (type == MASK_TYPE_FULL)
			newmask->mask[i][j] = true;
			else
			{
				newmask->mask[i][j] = false;
			}
		}
	}
	addElement(maskMap, size, newmask);
	return newmask;


}
bool blitMask(ObjectMask &dest, ObjectMask &source,
	int posX, int posY,
	int startX, int startY,
	int endX, int endY)
{
	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	if (endX == -1 && endY == -1)
	{
		endX = source.sizeX;
		endY = source.sizeY;
	}

	if (startX >= source.sizeX || startY >= source.sizeY)
		return false;
	for (int i = 0; i < endY - startY; i++)
	{
		if (dest.sizeY > i + posY)
			for (int j = 0; j < endX - startX; j++)
			{
				if (j + startX >= source.sizeX || i + startY >= source.sizeY) break;
				if (dest.sizeX > j + posX)
				{
					dest.mask[i + posY][j + posX]=source.mask[i + startY][j + startX];
				}
			}
	}
	return true;
}
// Не тестировання функция
bool objectCollision(ObjectMask &mask, LevelDynamicObject &obj)
{
	int posX = obj.posX;
	int posY = obj.posY;
	int endX = posX+obj.dynmask->sizeX;
	int endY = posY+obj.dynmask->sizeY;

	for (int i = 0; i < endY - posY; i++)
	{
		if (mask.sizeY > i + posY)
			for (int j = 0; j < endX - posX; j++)
			{
				if (j + posX >= mask.sizeX || i + posY >= mask.sizeY) break;
				if (mask.sizeX > j + posX)
				{
					if (mask.mask[i + posY][j + posX])
						return true;
				}
			}
	}
	return false;
}

bool getTileSet(new_GFSurface &dest, new_GFSurface &source, int sizeX, int sizeY, int tileSetIndex)
{
	int drawStartX = tileSetIndex % 3;
	int drawStartY = tileSetIndex / 3;

	return getChapSurface(dest, source, drawStartX*sizeX, drawStartY*sizeY, (drawStartX*sizeX)+sizeX, (drawStartY*sizeY)+sizeY);
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
	data.stInfo.tileset = convertPicture(*tileset);

	data.stInfo.curTileset = initSurface(SIZE_TILESET_X, SIZE_TILESET_Y, 0, 0);
	//// Возвращается поверхность которая в последствии не удалится. Не забыть!
	getTileSet(*data.stInfo.curTileset, *data.stInfo.tileset, SIZE_TILESET_X, SIZE_TILESET_Y,3);

	data.stInfo.objStatSize = (SIZE_TILESET_X / TILESIZE)*(SIZE_TILESET_Y / TILESIZE);

	LevelStaticObject* staticMap = new LevelStaticObject[data.stInfo.objStatSize];
	
	for (int k = 0, i = 0; k < SIZE_TILESET_Y/TILESIZE; k++)
	{
		for (int m = 0; m < SIZE_TILESET_X/TILESIZE; m++)
		{
			if (i < data.stInfo.objStatSize)
			{
				staticMap[i].objectType = getRPGObjectType(typeset->bitmap[k][m]);
				if (staticMap[i].objectType == eObjSolid)
					staticMap[i].tilemask = getFullMask(MASK_TYPE_FULL);
				else
					staticMap[i].tilemask = getFullMask(MASK_TYPE_EMPTY);
				staticMap[i].index = i++;
			}
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
			stobj.tilemask = stInfo.objStatMap[i].tilemask;
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
	data.lvlInfo.screenPosX = 0;
	data.lvlInfo.screenPosY = 0;
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
	data.lvlInfo.mask = getFullMask(MASK_TYPE_EMPTY, data.lvlInfo.levelSurf->ccWidth, data.lvlInfo.levelSurf->ccHeight);
	refreshLevelMask(data, TILESIZE);
	drawLevel(data);

	return 0;
}

// Перерисовка маски уровня
void refreshLevelMask(LevelData &data, int tilesize)
{
	int drawStartX = 0;
	int drawStartY = 0;
	int tileindex = 0;
	for (int i = 0; i < data.lvlInfo.mapSizeY; i++)
		for (int j = 0; j < data.lvlInfo.mapSizeY; j++)
		{
			drawStartX = (tileindex % data.lvlInfo.mapSizeX)*tilesize;
			drawStartY = (tileindex / data.lvlInfo.mapSizeY)*tilesize;
			bool debag = data.lvlInfo.levelmap[i][j].tilemask->mask[0][0];
			blitMask(*data.lvlInfo.mask, *data.lvlInfo.levelmap[i][j].tilemask, drawStartX, drawStartY, 0, 0, tilesize, tilesize);
			tileindex++;
		}
	showMask(*data.lvlInfo.mask);
}

void drawLevel(LevelData &data)
{
	for (int i = 0; i < data.lvlInfo.mapSizeY; i++)
	{
		for (int j = 0; j < data.lvlInfo.mapSizeX; j++)
		{
			int temp = data.lvlInfo.levelmap[i][j].index;
			blitTile(data, temp, TILESIZE, j, i);
		}
	}
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
			drawStartX = (data.stInfo.objStatMap[i].index % (data.stInfo.curTileset->ccWidth/tilesize))*tilesize;
			drawStartY = (data.stInfo.objStatMap[i].index / (data.stInfo.curTileset->ccWidth/tilesize))*tilesize;
			drawEndX = drawStartX+ tilesize;
			drawEndY = drawStartY+ tilesize;
			blitSurface(*data.lvlInfo.levelSurf, *data.stInfo.curTileset,posX*tilesize, posY*tilesize,
				drawStartX, drawStartY, drawEndX, drawEndY);
			return true;
		}
	}
	return false;
}

LevelData* initLevelData(char* mainname, int winX, int winY)
{
	LevelData* data = new LevelData;
	data->lives = 3;
	data->score = 0;
	data->winX = winX;
	data->winY = winY;
	if (initStatic(*data, mainname) == ERROR_CODE) return NULL;
	if (initLevel(*data, mainname) == ERROR_CODE) return NULL;
	if (initDynamic(*data, mainname) == ERROR_CODE) return NULL;

	return data;
}

int initDynamic(LevelData &data,char* spritename)
{
	char spriteFileName[128];
	strcpy(spriteFileName, spritename);
	strcat(spriteFileName, NAME_CHAR);

	BMPPicture* spriteset = bmpReader(spriteFileName, UP_MIRROR);
	if (!spriteset) return ERROR_CODE;
	data.dyInfo.tileset = convertPicture(*spriteset,&rgbMask());
	data.dyInfo.dynObjSize = 0;
	data.dyInfo.lvlObj = initSurface(data.lvlInfo.levelSurf->ccWidth, data.lvlInfo.levelSurf->ccHeight, 0, 0);

	if (!data.dyInfo.tileset) return ERROR_CODE;
	return NULL;
}

bool addDynamicObject(LevelData &data, LevelDynamicObject *obj, int clear)
{
	if (clear == OBJ_CLEAR)
	{
		delete[] data.dyInfo.dynobj;
		return true;
	}
	addElement(data.dyInfo.dynobj, data.dyInfo.dynObjSize, obj);
	return true;
}

LevelDynamicObject* createDynamicPlayer(LevelData &data, int charIndex, int colorIndex, int posX, int posY)
{
	LevelDynamicObject* player = new LevelDynamicObject;
	player->dynmask = getFullMask(MASK_TYPE_FULL); // В будущем можно будет переделать под различные маски
	player->charIndex = charIndex;
	player->colorIndex = colorIndex;
	player->spriteIndex = 0;
	player->direction = DOWN;
	player->prevX = posX;
	player->prevY = posY;
	player->posX = posX;
	player->posY = posY;
	player->objType = eDynPlayer;
	player->alive = true;
	addDynamicObject(data, player);
	return player;
}
// Для дебага масок
void showMask(ObjectMask &mask)
{
	for (int i = 0; i < mask.sizeY / TILESIZE; i++)
	{
		for (int j = 0; j < mask.sizeX / TILESIZE; j++)
		{
			if (mask.mask[i*TILESIZE][j*TILESIZE])
				cout << '#';
			else cout << '_';
		}
		cout << endl;
	}
}


//int activeRPG(GameData &data)
//{
//	static int screenPosX = 0;
//	static int screenPosY = 0;
//	static bool initialize = true;
//	static new_GFSurface* screen;
//	if (initialize)
//	{
//		screen = pushGameSuface(data, *data.RPG->lvlInfo.screen);
//		initialize = false;
//	}
//
//
//	return 0;
//}


// Возвращает тип объекта, с которым столкнулся
int checkCollision(LevelData &data, LevelDynamicObject &obj)
{
	if (objectCollision(*data.lvlInfo.mask, obj)) return eDynWall;
	for (int i = 0; i < data.dyInfo.dynObjSize; i++)
	{
		if (objectCollision(*data.dyInfo.dynobj[i].dynmask, obj)) return data.dyInfo.dynobj[i].objType;
	}
	return eDynNULL;

}
// Не проверена
void drawDynObjects(LevelData &data)
{
	cleanSurface(*data.dyInfo.lvlObj);

	for (int i = 0; i < data.dyInfo.dynObjSize; i++)
	{
		int dir = data.dyInfo.dynobj[i].direction;
		if (dir == LEFT) dir == RIGHT;
		int drawStartX =
			(data.dyInfo.dynobj[i].spriteIndex +
				(dir*CHAR_STATE))*TILESIZE;
		int drawStartY = data.dyInfo.dynobj[i].charIndex*TILESIZE;
		int drawEndX = drawStartX + TILESIZE;
		int drawEndY = drawStartY + TILESIZE;
		blitSurface(*data.dyInfo.lvlObj, *data.dyInfo.tileset, data.dyInfo.dynobj[i].posX, data.dyInfo.dynobj[i].posY,
			drawStartX, drawStartY, drawEndX, drawEndY);
	}
}

void drawScreen(LevelData &data, new_GFSurface &screen)
{
	//cleanSurface(screen);
	drawDynObjects(data);
	blitSurface(screen, *data.lvlInfo.levelSurf, 0, 0, 
		data.lvlInfo.screenPosX, 
		data.lvlInfo.screenPosY, 
		data.lvlInfo.screenPosX + data.winX,
		data.lvlInfo.screenPosY + data.winY);
	blitSurface(screen, *data.dyInfo.lvlObj, 0, 0,
		data.lvlInfo.screenPosX,
		data.lvlInfo.screenPosY,
		data.lvlInfo.screenPosX + data.winX,
		data.lvlInfo.screenPosY + data.winY);
}

int processPlayer(LevelData &data)
{
	for (int i = 0; i < data.dyInfo.dynObjSize; i++)
	{
		if (data.dyInfo.dynobj[i].objType == eDynPlayer)
		{
			// Код для объекта "игрок"

			if (KB_Pressed(vk_W))
			{
				data.dyInfo.dynobj[i].posY--;
			}
			if (KB_Pressed(vk_A))
			{
				data.dyInfo.dynobj[i].posX--;
			}
			if (KB_Pressed(vk_S))
			{
				data.dyInfo.dynobj[i].posY++;
			}
			if (KB_Pressed(vk_D))
			{
				data.dyInfo.dynobj[i].posX++;
			}

			if (checkCollision(data, data.dyInfo.dynobj[i]) == eDynWall)
			{
				data.dyInfo.dynobj[i].posX = data.dyInfo.dynobj[i].prevX;
				data.dyInfo.dynobj[i].posY = data.dyInfo.dynobj[i].prevY;
			}

			data.dyInfo.dynobj[i].prevX = data.dyInfo.dynobj[i].posX;
			data.dyInfo.dynobj[i].prevY = data.dyInfo.dynobj[i].posY;

			// Конец блока
			return NULL;
		}
	}
	return NULL;
}

int processEnemy(LevelData &data)
{
	return NULL;
}

int processNPC(LevelData &data)
{
	return NULL;
}

int processPickUp(LevelData &data)
{
	return NULL;
}

int activeRPG(GameData &data)
{
	static int tiles = 0;
	static bool initialize = true;
	static new_GFSurface* screen;
	if (initialize)
	{
		screen = pushGameSuface(data, *data.RPG->lvlInfo.screen);
		initialize = false;
		createDynamicPlayer(*data.RPG, 0, 0, 64, 129);
	}
	processPlayer(*data.RPG);
	if (KB_Pressed(VK_RIGHT))
	{
		data.RPG->lvlInfo.screenPosX += 16;
	}
	if (KB_Pressed(VK_LEFT))
	{
		data.RPG->lvlInfo.screenPosX -= 16;
	}
	if (KB_Pressed(VK_UP)) data.RPG->lvlInfo.screenPosY -= 16;
	if (KB_Pressed(VK_DOWN)) data.RPG->lvlInfo.screenPosY += 16;
	if (KB_Hit(VK_LSHIFT))
	{
		if (tiles == 9) tiles = 0;
		getTileSet(*data.RPG->stInfo.curTileset, *data.RPG->stInfo.tileset, SIZE_TILESET_X, SIZE_TILESET_Y, tiles++);
		drawLevel(*data.RPG);

	}
	if (data.RPG->lvlInfo.screenPosX < 0) data.RPG->lvlInfo.screenPosX = 0;
	if (data.RPG->lvlInfo.screenPosY < 0) data.RPG->lvlInfo.screenPosY = 0;
	drawScreen(*data.RPG, *screen);


	return 0;
}