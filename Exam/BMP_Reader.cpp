#include "BMP_Reader.h"

BMPPicture* bmpReader(char* filename)
{
	static int size = 0;
	static BMPPicture** bpicmass = new BMPPicture*[size];
	if (!strcmp(filename, "_DELETE_BMP_BUFFER_"))
	{
		for (int i = 0; i < size; i++)
		{
			delete2d(bpicmass[i]->bitmap, bpicmass[i]->info.biHeight);
		}
		delete2d(bpicmass, size);
		bpicmass = new BMPPicture*[size];
		size = 0;
		return NULL;
	}

	BMPPicture* bpic = new BMPPicture;
	if (bmpReader(*bpic, filename))
	{
		addElement(bpicmass, size, bpic);
		return bpic;
	}
	else
	{
		delete bpic;
		return NULL;
	}
}

BMPPicture* bmpReader(char*filename, int mode)
{
	BMPPicture* bpic = bmpReader(filename);
	if (!bpic) return NULL;
	if (mode == UP_MIRROR)
		bmpUpMirror(*bpic);
	return bpic;
}

void bmpClear()
{
	bmpReader("_DELETE_BMP_BUFFER_");
}

RGBBlock rgbMask()
{
	RGBBlock rgb;
	rgb.rgbRed = 255;
	rgb.rgbGreen = 10;
	rgb.rgbBlue = 255;
	return rgb;
}

int getColorCode(RGBBlock &block)
{
	return (block.rgbRed << 16) | (block.rgbGreen << 8) | (block.rgbBlue);
}

bool equalRGBBlock(RGBBlock &a, RGBBlock &b)
{
	if (a.rgbBlue != b.rgbBlue) return false;
	if (a.rgbGreen != b.rgbGreen) return false;
	if (a.rgbRed != b.rgbRed) return false;
	return true;
}

bool bmpReader(BMPPicture &picture, char* filename)
{
	if (picture.bitmap != NULL)
		delete2d(picture.bitmap, picture.info.biHeight);

	FILE* pFile = fopen(filename, "rb");
	if (!pFile) return false;

	picture.file.bfType = read_u16(pFile);
	picture.file.bfSize = read_u32(pFile);
	picture.file.bfReserved1 = read_u16(pFile);
	picture.file.bfReserved2 = read_u16(pFile);
	picture.file.bfOffBits = read_u32(pFile);


	picture.info.biSize = read_u32(pFile);
	picture.info.biWidth = abs(read_s32(pFile));
	picture.info.biHeight = abs(read_s32(pFile));
	picture.info.biPlanes = read_u16(pFile);
	picture.info.biBitCount = read_u16(pFile);
	picture.info.biCompression = read_u32(pFile);
	picture.info.biSizeImage = read_u32(pFile);
	picture.info.biXPelsPerMeter = read_s32(pFile);
	picture.info.biYPelsPerMeter = read_s32(pFile);

	//picture.info.biReserved = read_u16(pFile);
	picture.info.biClrUsed = read_u32(pFile);
	picture.info.biClrImportant = read_u32(pFile);


	picture.bitmap = new RGBBlock*[picture.info.biHeight];
	for (int i = 0; i < picture.info.biHeight; i++) {
		picture.bitmap[i] = new RGBBlock[picture.info.biWidth];
	}

	for (int i = 0; i < picture.info.biHeight; i++) {
		for (int j = 0; j < picture.info.biWidth; j++) {
			picture.bitmap[i][j].rgbBlue = getc(pFile);
			picture.bitmap[i][j].rgbGreen = getc(pFile);
			picture.bitmap[i][j].rgbRed = getc(pFile);
		}
	}

	fclose(pFile);
	return true;
}



void bmpRotate(BMPPicture &picture)
{

	RGBBlock** bmpbuff = new RGBBlock*[picture.info.biWidth];
	for (int i = 0; i < picture.info.biWidth; i++) {
		bmpbuff[i] = new RGBBlock[picture.info.biHeight];
	}

	for (int i = 0; i < picture.info.biHeight; i++)
	{
		for (int j = 0; j < picture.info.biWidth; j++)
		{
			bmpbuff[j][i] = picture.bitmap[i][j];
		}
	}

	delete2d(picture.bitmap, picture.info.biHeight);
	picture.bitmap = bmpbuff;

	int buff = picture.info.biWidth;
	picture.info.biWidth = picture.info.biHeight;
	picture.info.biHeight = buff;
}

void bmpMirror(BMPPicture &picture)
{

	RGBBlock** bmpbuff = new RGBBlock*[picture.info.biHeight];
	for (int i = 0; i < picture.info.biHeight; i++) {
		bmpbuff[i] = new RGBBlock[picture.info.biWidth];
	}

	for (int i = 0; i < picture.info.biHeight; i++)
	{
		for (int j = 0, k = picture.info.biWidth-1; j < picture.info.biWidth; j++, k--)
		{
			bmpbuff[i][k] = picture.bitmap[i][j];
		}
	}

	delete2d(picture.bitmap, picture.info.biHeight);
	picture.bitmap = bmpbuff;
}

void bmpUpMirror(BMPPicture &bpic)
{
	bmpRotate(bpic);
	bmpMirror(bpic);
	bmpRotate(bpic);
}

static unsigned short read_u16(FILE *fp)
{
	unsigned char b0, b1;

	b0 = getc(fp);
	b1 = getc(fp);

	return ((b1 << 8) | b0);
}


static unsigned int read_u32(FILE *fp)
{
	unsigned char b0, b1, b2, b3;

	b0 = getc(fp);
	b1 = getc(fp);
	b2 = getc(fp);
	b3 = getc(fp);

	return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}


static int read_s32(FILE *fp)
{
	unsigned char b0, b1, b2, b3;

	b0 = getc(fp);
	b1 = getc(fp);
	b2 = getc(fp);
	b3 = getc(fp);

	return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}