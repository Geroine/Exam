#pragma once
#include "ProjectHeader.h"
#define NAME_TILE "_tile.bmp"
#define NAME_TYPE "_type.bmp"
#define NAME_LEVEL "_level"
#define TILESIZE 16
#define ERROR_CODE -1


enum eObjType
{
	eObjSolid = 1,
	eObjNoSolid,
	eObjEnemy,
	eObjCoin,
	eObjBonus
};

const struct ObjectKey
{
	unsigned Solid       = 0xff7a00;
	unsigned NoSolid	 = 0x00a300;
	unsigned Enemy		 = 0xff1e00;
	unsigned Coin		 = 0xf5ef00;
	unsigned Bonus		 = 0xffc000;
};

// Статический объект, который не должен менятся на протяжении всего уровня. Тайлы берет с LevelStaticInfo
struct LevelStaticObject
{
	int objectType;
	int index;
};

// Динамический объект содержит собственные спрайты, текущие координаты и предыдущие.
struct LevelDynamicObject
{
	int spritesize;
	int index;
	double prevX;
	double prevY;
	double posX;
	double posY;
};

// Массив динамических объектов в сцене.
struct LevelDynamicInfo
{
	int dynObjSize;
	LevelDynamicObject* dynobj;
};

// Массив статических объектов, откуда мы берем информацию от объектов
struct LevelStaticInfo
{
	int objStatSize;
	LevelStaticObject* objStatMap;
	new_GFSurface* tileset;
};

/*
levelmap - массив статических объектов
и его размеры. По ним будем рисовать карту и сверять столкновения на уровне
screen - surface, что мы будем передавать на отрисовку в activeGraphics
levelSurf - surface всего игрового уровня и его размеры
*/
struct LevelScreen
{
	LevelStaticObject** levelmap;
	int mapSizeX;
	int mapSizeY;
	new_GFSurface* screen;
	new_GFSurface* levelSurf;
};

/*
Cтруктура игровой логики и спрайтов.
LSI содержит тайлсет и информацию о каждом статическом объекте
LDI содержит массив объектов с собственными данными
LS информация о уровне, каждый уровень загружатеся заново.
*/
struct NumberArray;
struct LevelData
{	
	NumberArray* leveltemp;
	LevelStaticInfo stInfo;
	LevelDynamicInfo dyInfo;
	LevelScreen lvlInfo;
	int score;
	int lives;
	int winX;
	int winY;
};

int getRPGObjectType(RGBBlock &block);
int initStatic(LevelData &data, char* mainname);
LevelStaticObject cleanStaticObject();
LevelStaticObject getStaticObject(LevelStaticInfo &stInfo, int id);
int initLevel(LevelData &data, char* levelname);
bool blitTile(LevelData &data, int index, int tilesize, int posX, int posY);
LevelData* initLevelData(char* levelname, char* mainname, int winX, int winY);
int activeRPG(GameData &data);