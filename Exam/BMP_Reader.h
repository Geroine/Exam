#pragma once
#include "ProjectHeader.h"

struct BMPFile
{
	unsigned short    bfType;
	unsigned long   bfSize;
	unsigned short    bfReserved1;
	unsigned short    bfReserved2;
	unsigned long   bfOffBits;
};

struct BMPInfo
{
	unsigned int    biSize;
	int             biWidth;
	int             biHeight;
	unsigned short  biPlanes;
	unsigned short  biBitCount;
	unsigned int    biCompression;
	unsigned int    biSizeImage;
	int             biXPelsPerMeter;
	int             biYPelsPerMeter;

	//short			biReserved;
	unsigned int    biClrUsed;
	unsigned int    biClrImportant;
};

struct RGBBlock
{
	int   rgbBlue;
	int   rgbGreen;
	int   rgbRed;
	int   rgbReserved;
};

struct BMPPicture
{
	BMPFile file;
	BMPInfo info;
	RGBBlock** bitmap;
};

bool bmpReader(BMPPicture &picture, char* filename);
void bmpRotate(BMPPicture &picture);
void bmpMirror(BMPPicture &picture);

static unsigned short read_u16(FILE *fp);
static unsigned int   read_u32(FILE *fp);
static int            read_s32(FILE *fp);