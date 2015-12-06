#pragma once
#include "ProjectHeader.h"
#define NAME_TILE "_map3.bmp"
#define SIZE_TILESET_X 272
#define SIZE_TILESET_Y 144
#define NAME_TYPE "_type2.bmp"
#define NAME_CHAR "_char.bmp"
#define NAME_LEVEL "_level"
#define TILESIZE 16
#define ERROR_CODE -1
#define MASK_TYPE_FULL 1
#define MASK_TYPE_EMPTY 0
#define MASK_CLEAR -1
#define OBJ_CLEAR -1

#define SIZE_SPRITESET_X 144
#define SIZE_SPRITESET_Y 128

#define CHAR_COUNT 8
#define CHAR_COLOR 12
#define CHAR_DIR 4
#define CHAR_STATE 3

#define UP 2
#define DOWN 0
#define LEFT 3
#define RIGHT 1

enum eObjType
{
	eObjSolid = 1,
	eObjNoSolid,
	eObjHeart,
	eObjStart,
	eObjFinish
};
//Дополнительный bmp файл, который содержит цвет совпадающий с кодом в соответствующей позиции. Так я узнаю тип объекта.
const struct ObjectKey
{
	unsigned Solid       = 0xff7a00;
	unsigned NoSolid	 = 0x00a300;
	unsigned Heart		 = 0xff1e00;
	unsigned Start		 = 0xf5ef00;
	unsigned Finish		 = 0xffc000;
};

struct ObjectMask
{
	int sizeX;
	int sizeY;
	bool** mask;
};

// Статический объект, который не должен менятся на протяжении всего уровня. Тайлы берет с LevelStaticInfo
struct LevelStaticObject
{
	ObjectMask* tilemask;
	int objectType;
	int index;
};

enum eDynObjType
{
	eDynPlayer = 1,
	eDynEnemy,
	eDynWall, 
	eDynNPC, 
	eDynObject,
	eDynNULL
};
// Динамический объект содержит собственные спрайты, текущие координаты и предыдущие.
struct LevelDynamicObject
{
	ObjectMask* dynmask;
	int charIndex; // Для этого проекта (0-7)
	int colorIndex; // Для  этого проекта существует 12 различных раскрасок (0-11)
	int spriteIndex;// Один из трёх спрайтов. 0 - покой, 1 и 2 - движение (для персонажей)
	int direction;
	double prevX;
	double prevY;
	double posX;
	double posY;
	int objType;
	bool alive;
};

// Массив динамических объектов в сцене.
struct LevelDynamicInfo
{
	int dynObjSize;
	LevelDynamicObject* dynobj;
	new_GFSurface* tileset;
	new_GFSurface* lvlObj;
};

// Массив статических объектов, откуда мы берем информацию от объектов
struct LevelStaticInfo
{
	int objStatSize;
	LevelStaticObject* objStatMap;
	new_GFSurface* tileset;
	new_GFSurface* curTileset;
};

/*
levelmap - массив статических объектов
и его размеры. По ним будем рисовать карту и сверять столкновения на уровне
screen - surface, что мы будем передавать на отрисовку в activeGraphics
levelSurf - surface всего игрового уровня и его размеры
mask - маска мира, чтобы определять столкновения
*/
struct LevelScreen
{
	LevelStaticObject** levelmap;
	ObjectMask* mask;
	int mapSizeX;
	int mapSizeY;
	new_GFSurface* screen;
	int screenPosX;
	int screenPosY;
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
	LevelStaticInfo stInfo;
	LevelDynamicInfo dyInfo;
	LevelScreen lvlInfo;
	int score;
	int lives;
	int winX;
	int winY;
};

ObjectMask* getFullMask(int type,int sizeX = TILESIZE, int sizeY = TILESIZE, int clearcode = NULL);
int getRPGObjectType(RGBBlock &block);
int initStatic(LevelData &data, char* mainname);
LevelStaticObject cleanStaticObject();
LevelStaticObject getStaticObject(LevelStaticInfo &stInfo, int id);
int initLevel(LevelData &data, char* levelname);
int initDynamic(LevelData &data, char* spritename);
bool blitTile(LevelData &data, int index, int tilesize, int posX, int posY);
LevelData* initLevelData( char* mainname, int winX, int winY);
bool addDynamicObject(LevelData &data, LevelDynamicObject *obj = NULL, int clear = 0);
bool objectCollision(ObjectMask &mask, LevelDynamicObject &obj);
void refreshLevelMask(LevelData &data, int tilesize);
void drawDynObjects(LevelData &data);
void drawScreen(LevelData &data, new_GFSurface &screen);
int activeRPG(GameData &data);
bool blitMask(ObjectMask &dest, ObjectMask &source,
	int posX = 0, int posY = 0,
	int startX = 0, int startY = 0,
	int endX = -1, int endY = -1);
void showMask(ObjectMask &mask);
void drawLevel(LevelData &data);