#pragma once
#include "ProjectHeader.h"
#define NO_POS -1


enum eConsoleColor
{
	CC_Black = 0,
	CC_DarkBlue = 1,
	CC_DarkGreen = 2,
	CC_DarkCyan = 3,
	CC_DarkRed = 4,
	CC_DarkMagenta = 5,
	CC_DarkYellow = 6,
	CC_Gray = 7,
	CC_DarkGray = 8,
	CC_Blue = 9,
	CC_Green = 10,
	CC_Cyan = 11,
	CC_Red = 12,
	CC_Magenta = 13,
	CC_Yellow = 14,
	CC_White = 15
};

struct G4Block
{
	char symb;
	char sCol;
	char bCol;
	bool visible = false;
};

struct new_GFSurface
{
	int posX;
	int posY;
	int ccWidth;
	int ccHeight;
	G4Block** symbmap = NULL;
	bool nextRemove;
};


struct GFSurface
{
	int ccWidth;
	int ccHeight;
	char** bitmap;
};

struct BMPPicture;
struct RGBBlock;
struct GameData;

// Добавил новую структуру G4Surface,надо не забыть переделать эту функцию, чтобы конвертация цвета была вынесена отдельно
void convertPicture(new_GFSurface &cpic, BMPPicture &bpic, int cc_true, int cc_half, RGBBlock* key);

RGBBlock getColor(char id);

void initSurface(new_GFSurface &surface, int sizeX, int sizeY, int posX, int posY); // Удалим

new_GFSurface* initSurface(int sizeX, int sizeY, int posX, int posY);

void clearSurface();

void convertBMP(BMPPicture &bpic, int cc_true, int cc_half);

bool equalG4Block(G4Block &a, G4Block &b);

G4Block emptyG4Block();

void copyG4Block(G4Block &a, G4Block &b);

void blitSurface(new_GFSurface &mainSurf, new_GFSurface &subSurf, int posX, int posY);

bool blitSurface(new_GFSurface &mainSurf, new_GFSurface &subSurf,
	int posX, int posY,
	int startX, int startY,
	int endX, int endY);

new_GFSurface* cutChapSurface(new_GFSurface &source,
	int startX, int startY,
	int endX, int endY);

new_GFSurface* picToSurface(char* filename);

void setPosSurface(int posX, int posY);

void SetColorBgTex(int Bg, int Tex);

void SetConsCurPos(int x, int y);

void SetConsWinSize(int XSize, int YSize);