#pragma once
#include "ProjectHeader.h"
#define UP_MIRROR 1

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
	unsigned   rgbBlue;
	unsigned   rgbGreen;
	unsigned   rgbRed;
	unsigned   rgbReserved;
};

struct BMPPicture
{
	BMPFile file;
	BMPInfo info;
	RGBBlock** bitmap = NULL;
};

BMPPicture* bmpReader(char* name);
BMPPicture* bmpReader(char*filename, int mode);
bool bmpReader(BMPPicture &picture, char* filename);
void bmpClear();
RGBBlock rgbMask();
int getColorCode(RGBBlock &block);
bool equalRGBBlock(RGBBlock &a, RGBBlock &b);
void bmpRotate(BMPPicture &picture);
void bmpMirror(BMPPicture &picture);
void bmpUpMirror(BMPPicture &bpic);


static unsigned short read_u16(FILE *fp);
static unsigned int   read_u32(FILE *fp);
static int            read_s32(FILE *fp);

