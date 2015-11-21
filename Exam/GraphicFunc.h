#pragma once
#include "ProjectHeader.h"


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

struct GFSurface
{
	int ccWidth;
	int ccHeight;
	char** bitmap;
};

struct BMPPicture;
struct RGBBlock;

void convertPicture(GFSurface &cpic, BMPPicture &bpic, int cc_true, int cc_half);

RGBBlock getColor(char id);

void convertBMP(BMPPicture &bpic, int cc_true, int cc_half);

void SetColorBgTex(int Bg, int Tex);

void SetConsCurPos(int x, int y);

void SetConsWinSize(int XSize, int YSize);
