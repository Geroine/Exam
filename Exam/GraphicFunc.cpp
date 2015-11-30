#include "GraphicFunc.h"
#define ALGORITHM 1
#define CC_TRUE 127
#define CC_HALF 94
#define CC_1W 100
#define CC_2W 127
#define CC_3W 50

new_GFSurface* convertPicture(BMPPicture &bpic, RGBBlock* key)
{
	new_GFSurface* cpic = initSurface(bpic.info.biWidth, bpic.info.biHeight, 0, 0);
	convertPicture(*cpic, bpic, 127, 127, key);
	return cpic;
}

// Эта функция создает surface внутри функции, а не через initSurface. Такие поверхности будут оставаться в памяти.
// Очень кривая функция, надо будет исправить
void convertPicture(new_GFSurface &cpic, BMPPicture &bpic, int cc_true, int cc_half, RGBBlock* key)
{
	bool newPic = false;
	if (cpic.symbmap != NULL)
	{
		delete2d(cpic.symbmap, cpic.ccHeight);
	}
	cpic.ccHeight = bpic.info.biHeight;
	cpic.ccWidth = bpic.info.biWidth;
	cpic.posX = 0;
	cpic.posY = 0;
	cpic.symbmap = new G4Block*[cpic.ccHeight];
	for (int i = 0; i < cpic.ccHeight; i++)
	{
		cpic.symbmap[i] = new G4Block[cpic.ccWidth];
	}
	for (int i = 0; i < cpic.ccHeight; i++)
	{
		for (int j = 0; j < cpic.ccWidth; j++)
		{
			cpic.symbmap[i][j] = emptyG4Block();
		}
	}

		char ccResult = 0;

#if ALGORITHM == 3
		int cc1, cc2, cc3, cc12, cc13, cc23, cc123;
		for (int i = 0; i < cpic.ccHeight; i++)
		{
			for (int j = 0; j < cpic.ccWidth; j++)
			{
				if (key != NULL)
				{
					if (!equalRGBBlock(bpic.bitmap[i][j], *key)) cpic.symbmap[i][j].visible = true;
				}
				else cpic.symbmap[i][j].visible = true;
				cc1 = bpic.bitmap[i][j].rgbRed;
				cc2 = bpic.bitmap[i][j].rgbGreen;
				cc3 = bpic.bitmap[i][j].rgbBlue;
				cc123 = (bpic.bitmap[i][j].rgbRed +
					bpic.bitmap[i][j].rgbGreen +
					bpic.bitmap[i][j].rgbBlue) / 3;
				
				if		(cc1 - CC_HALF > cc2 && cc1 - CC_HALF > cc3 && cc123 <= CC_TRUE) ccResult = CC_DarkRed;
				else if (cc2 - CC_HALF > cc3 && cc2 - CC_HALF > cc1 && cc123 <= CC_TRUE) ccResult = CC_DarkGreen;
				else if (cc3 - CC_HALF > cc1 && cc3 - CC_HALF > cc2 && cc123 <= CC_TRUE) ccResult = CC_DarkBlue;
				else if (cc1 - CC_HALF > cc3 && cc2 - CC_HALF > cc3 && cc123 <= CC_TRUE) ccResult = CC_DarkYellow;
				else if (cc1 - CC_HALF > cc2 && cc3 - CC_HALF > cc2 && cc123 <= CC_TRUE) ccResult = CC_DarkMagenta;
				else if (cc2 - CC_HALF > cc1 && cc3 - CC_HALF > cc1 && cc123 <= CC_TRUE) ccResult = CC_DarkCyan;
					
				else if (cc1 - CC_HALF > cc2 && cc1 - CC_HALF > cc3 && cc123 > CC_TRUE) ccResult = CC_Red;
				else if (cc2 - CC_HALF > cc3 && cc2 - CC_HALF > cc1 && cc123 > CC_TRUE) ccResult = CC_Green;
				else if (cc3 - CC_HALF > cc1 && cc3 - CC_HALF > cc2 && cc123 > CC_TRUE) ccResult = CC_Blue;
				else if (cc1 - CC_HALF > cc3 && cc2 - CC_HALF > cc3 && cc123 > CC_TRUE) ccResult = CC_Yellow;
				else if (cc1 - CC_HALF > cc2 && cc3 - CC_HALF > cc2 && cc123 > CC_TRUE) ccResult = CC_Magenta;
				else if (cc2 - CC_HALF > cc1 && cc3 - CC_HALF > cc1 && cc123 > CC_TRUE) ccResult = CC_Cyan;

				else if (cc123 > 196)		   ccResult = CC_White;
				else if (cc123 > 150)		   ccResult = CC_Gray;
				else if (cc123 > 100)		   ccResult = CC_DarkGray;
				else						   ccResult = CC_Black;


				cpic.symbmap[i][j].bCol = ccResult;
			}
		}
#elif ALGORITHM == 2
	int cc1, cc2, cc3, cc12, cc13, cc23, cc123;
	for (int i = 0; i < cpic.ccHeight; i++)
	{
		for (int j = 0; j < cpic.ccWidth; j++)
		{
			if (key != NULL)
			{
				if (!equalRGBBlock(bpic.bitmap[i][j], *key)) cpic.symbmap[i][j].visible = true;
			}
			else cpic.symbmap[i][j].visible = true;
			cc1 = bpic.bitmap[i][j].rgbRed;
			cc2 = bpic.bitmap[i][j].rgbGreen;
			cc3 = bpic.bitmap[i][j].rgbBlue;
			cc12 = average(bpic.bitmap[i][j].rgbRed, bpic.bitmap[i][j].rgbGreen);
			cc13 = average(bpic.bitmap[i][j].rgbRed, bpic.bitmap[i][j].rgbBlue);
			cc23 = average(bpic.bitmap[i][j].rgbGreen, bpic.bitmap[i][j].rgbBlue);
			cc123 = (bpic.bitmap[i][j].rgbRed +
					 bpic.bitmap[i][j].rgbGreen +
					 bpic.bitmap[i][j].rgbBlue) / 3;

			     if (cc1 - cc23 > cc_true && cc123 <= cc_half) ccResult = CC_DarkRed;
			else if (cc2 - cc13 > cc_true && cc123 <= cc_half) ccResult = CC_DarkGreen;
			else if (cc3 - cc12 > cc_true && cc123 <= cc_half) ccResult = CC_DarkBlue;
			else if (cc12 - cc3 > cc_true && cc123 <= cc_half) ccResult = CC_DarkYellow;
			else if (cc13 - cc2 > cc_true && cc123 <= cc_half) ccResult = CC_DarkMagenta;
			else if (cc23 - cc1 > cc_true && cc123 <= cc_half) ccResult = CC_DarkCyan;
								  
			else if (cc1 - cc23 > cc_true && cc123 > cc_half) ccResult = CC_Red;
			else if (cc2 - cc13 > cc_true && cc123 > cc_half) ccResult = CC_Green;
			else if (cc3 - cc12 > cc_true && cc123 > cc_half) ccResult = CC_Blue;
			else if (cc12 - cc3 > cc_true && cc123 > cc_half) ccResult = CC_Yellow;
			else if (cc13 - cc2 > cc_true && cc123 > cc_half) ccResult = CC_Magenta;
			else if (cc23 - cc1 > cc_true && cc123 > cc_half) ccResult = CC_Cyan;

			else if (cc123 > CC_1W)		   ccResult = CC_White;
			else if (cc123 > CC_2W)		   ccResult = CC_Gray;
			//else if (cc123 > CC_3W)		   ccResult = CC_DarkGray;
			else						   ccResult = CC_Black;


			cpic.symbmap[i][j].bCol = ccResult;
		}
	}
#elif ALGORITHM == 1

int ccSum;
for (int i = 0; i < cpic.ccHeight; i++)
{
	for (int j = 0; j < cpic.ccWidth; j++)
	{
		if (key != NULL)
		{
			if (!equalRGBBlock(bpic.bitmap[i][j], *key)) cpic.symbmap[i][j].visible = true;
		}
		else
		{
			cpic.symbmap[i][j].visible = false;
			continue;
		}

		ccSum = (bpic.bitmap[i][j].rgbRed +
			bpic.bitmap[i][j].rgbGreen +
			bpic.bitmap[i][j].rgbBlue) / 3;


		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum <= CC_1W)
			ccResult = CC_DarkBlue;

		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum <= CC_1W)
			ccResult = CC_DarkGreen;

		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum <= CC_HALF)
			ccResult = CC_DarkCyan;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum <= CC_1W)
			ccResult = CC_DarkRed;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum <= CC_HALF)
			ccResult = CC_DarkMagenta;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum <= CC_HALF)
			ccResult = CC_DarkYellow;

		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum > CC_1W)
			ccResult = CC_Blue;

		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum > CC_1W)
			ccResult = CC_Green;

		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum > CC_HALF)
			ccResult = CC_Cyan;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum > CC_1W)
			ccResult = CC_Red;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum > CC_HALF)
			ccResult = CC_Magenta;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum > CC_HALF)
			ccResult = CC_Yellow;
		// Grays

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum * 3 > 383)
			ccResult = CC_White;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum * 3 > 255 &&
			ccSum * 3 <= 383)
			ccResult = CC_Gray;

		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum * 3 > 127 &&
			ccSum * 3 <= 255)
			ccResult = CC_Black;

		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum * 3 <= 127)
			ccResult = CC_Black;

		cpic.symbmap[i][j].bCol = ccResult;
	}
}

#endif
}

RGBBlock getColor(char id)
{
	RGBBlock b;
	if (id == CC_White)
	{
		b.rgbRed = 255;
		b.rgbGreen = 255;
		b.rgbBlue = 255;
		return b;
	}
	if (id == CC_Red)
	{
		b.rgbRed = 255;
		b.rgbGreen = 0;
		b.rgbBlue = 0;
		return b;
	}
	if (id == CC_Yellow)
	{
		b.rgbRed = 255;
		b.rgbGreen = 255;
		b.rgbBlue = 0;
		return b;
	}
	if (id == CC_Green)
	{
		b.rgbRed = 0;
		b.rgbGreen = 255;
		b.rgbBlue = 0;
		return b;
	}
	if (id == CC_Cyan)
	{
		b.rgbRed = 0;
		b.rgbGreen = 255;
		b.rgbBlue = 255;
		return b;
	}
	if (id == CC_Blue)
	{
		b.rgbRed = 0;
		b.rgbGreen = 0;
		b.rgbBlue = 255;
		return b;
	}
	if (id == CC_Magenta)
	{
		b.rgbRed = 255;
		b.rgbGreen = 0;
		b.rgbBlue = 255;
		return b;
	}
	if (id == CC_Gray)
	{
		b.rgbRed = 192;
		b.rgbGreen = 192;
		b.rgbBlue = 192;
		return b;
	}
	if (id == CC_DarkGray)
	{
		b.rgbRed = 128;
		b.rgbGreen = 128;
		b.rgbBlue = 128;
		return b;
	}
	if (id == CC_DarkRed)
	{
		b.rgbRed = 128;
		b.rgbGreen = 0;
		b.rgbBlue = 0;
		return b;
	}
	if (id == CC_DarkYellow)
	{
		b.rgbRed = 128;
		b.rgbGreen = 128;
		b.rgbBlue = 0;
		return b;
	}
	if (id == CC_DarkGreen)
	{
		b.rgbRed = 0;
		b.rgbGreen = 128;
		b.rgbBlue = 0;
		return b;
	}
	if (id == CC_DarkCyan)
	{
		b.rgbRed = 0;
		b.rgbGreen = 128;
		b.rgbBlue = 128;
		return b;
	}
	if (id == CC_DarkBlue)
	{
		b.rgbRed = 0;
		b.rgbGreen = 0;
		b.rgbBlue = 128;
		return b;
	}
	if (id == CC_DarkMagenta)
	{
		b.rgbRed = 128;
		b.rgbGreen = 0;
		b.rgbBlue = 128;
		return b;
	}
	b.rgbRed = 0;
	b.rgbGreen = 0;
	b.rgbBlue = 0;
	return b;
}

void convertBMP(BMPPicture &bpic, int cc_true, int cc_half) // Сжимает BMP
{
	new_GFSurface cpic;
	convertPicture(cpic, bpic, cc_true, cc_half, NULL);

	for (int i = 0; i < cpic.ccHeight; i++)
	{
		for (int j = 0; j < cpic.ccWidth; j++)
		{
			bpic.bitmap[i][j] = getColor(cpic.symbmap[i][j].bCol);
		}
	}
}

G4Block emptyG4Block()
{
	G4Block empty;
	empty.symb = ' ';
	empty.bCol = CC_Black;
	empty.sCol = CC_Gray;
	empty.visible = false;
	return empty;
}


void initSurface(new_GFSurface &surface,int sizeX, int sizeY, int posX, int posY)
{
	surface.ccHeight = sizeY;
	surface.ccWidth = sizeX;
	surface.nextRemove = false;
	surface.posX = posX;
	surface.posY = posY;

	surface.symbmap = new G4Block*[surface.ccHeight];
	for (int i = 0; i < surface.ccHeight; i++)
		surface.symbmap[i] = new G4Block[surface.ccWidth];
	for (int i = 0; i < surface.ccHeight; i++)
	{
		for (int j = 0; j < surface.ccWidth; j++)
		{
			surface.symbmap[i][j] = emptyG4Block();
		}
	}
}

new_GFSurface* initSurface(int sizeX, int sizeY, int posX, int posY)
{
	static int size = 0;
	static new_GFSurface* surfacemass = new new_GFSurface[size];

	if (sizeX == -2 && sizeY == 0 && posX == -1 && posY == -2)
	{
		for (int i = 0; i < size; i++)
		{
			delete2d(surfacemass[i].symbmap, surfacemass[i].ccHeight);
		}
		delete[] surfacemass;
		size = 0;
		surfacemass = new new_GFSurface[size];
		return NULL;
	}

	new_GFSurface* surface;
	surface = new new_GFSurface;
	surface->ccHeight = sizeY;
	surface->ccWidth = sizeX;
	surface->nextRemove = false;
	surface->posX = posX;
	surface->posY = posY;

	surface->symbmap = new G4Block*[surface->ccHeight];

	G4Block block = emptyG4Block();

	for (int i = 0; i < surface->ccHeight; i++)
		surface->symbmap[i] = new G4Block[surface->ccWidth];
	for (int i = 0; i < surface->ccHeight; i++)
	{
		for (int j = 0; j < surface->ccWidth; j++)
		{
			surface->symbmap[i][j] = block;
		}
	}
	addElementest(surfacemass, size, surface);
	return surface;
}

// Говнокод
new_GFSurface* initBackground(int sizeX, int sizeY, int color)
{
	new_GFSurface* surface = initSurface(sizeX, sizeY, 0, 0);
	for (int i = 0; i < surface->ccHeight; i++)
	{
		for (int j = 0; j < surface->ccWidth; j++)
		{
			surface->symbmap[i][j].bCol = color;
			surface->symbmap[i][j].visible = true;
		}
	}
	return surface;
}

void clearSurface()
{
	initSurface(-2, 0, -1, -2);
}

bool equalG4Block(G4Block &a, G4Block &b)
{
	if (a.bCol != b.bCol) return false;
	if (a.sCol != b.sCol) return false;
	if (a.symb != b.symb) return false;
	if (a.visible != b.visible) return false;
	return true;
}

void copyG4Block(G4Block &a, G4Block &b)
{
	a.bCol = b.bCol;
	a.sCol = b.sCol;
	a.symb = b.symb;
	a.visible = b.visible;
}

void halfSurface(new_GFSurface &surf)
{
	new_GFSurface* trimSurf = initSurface(surf.ccWidth/2, surf.ccHeight/2, 0, 0);
	trimSurf->posX = surf.posX;
	trimSurf->posY = surf.posY;
	for (int i = 0,m = 0; i < surf.ccHeight; i++)
	{
		if (i % 2 != 0)
		{
			for (int j = 0, k = 0; j < surf.ccWidth; j++)
			{
				if (j % 2 != 0)
				{
					copyG4Block(trimSurf->symbmap[m][k++], surf.symbmap[i][j]);
				}
			}
			m++;
		}
	}
	delete2d(surf.symbmap, surf.ccHeight);
	surf = *trimSurf;
}

void blitSurface(new_GFSurface &mainSurf, new_GFSurface &subSurf, int posX = 0, int posY = 0)
{
	blitSurface(mainSurf, subSurf,
		posX, posY, 0, 0, subSurf.ccWidth, subSurf.ccHeight);
}

void blitSurfFull(new_GFSurface &mainSurf, new_GFSurface &subSurf, int posX = 0, int posY = 0)
{
	for (int i = 0; i < subSurf.ccHeight; i++)
	{
		if (mainSurf.ccHeight > i + posY)
			for (int j = 0; j < subSurf.ccWidth; j++)
			{
				if (mainSurf.ccWidth > j + posX)
					copyG4Block(mainSurf.symbmap[i + posY][j + posX], subSurf.symbmap[i][j]);
			}
	}
}



bool blitSurface(new_GFSurface &mainSurf, new_GFSurface &subSurf, 
	int posX, int posY, 
	int startX, int startY, 
	int endX, int endY)
{
	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	
	if (startX >= subSurf.ccWidth || startY >= subSurf.ccHeight)
		return false;
	for (int i = 0; i < endY-startY; i++)
	{
		if (mainSurf.ccHeight > i + posY)
			for (int j = 0; j < endX - startX; j++)
			{
				if (j + startX >= subSurf.ccWidth || i + startY >= subSurf.ccHeight) break;
				if (mainSurf.ccWidth > j + posX && subSurf.symbmap[i + startY][j + startX].visible)
					// Вот тут забыл добавит стартовую позицию! 2 ДНЯ СТРАДАЛ. Думал, блин, чего же функция копирует не верный параметр
					// Visible. Наконец то нашел. Боже, как я счастлив!!!
					// На этом страдания не закончились, я вернулся сюда спустя еще 4 часа... Тут где то баг...
				{
					copyG4Block(mainSurf.symbmap[i + posY][j + posX], subSurf.symbmap[i + startY][j + startX]);
				}

			}
	}
	return true;
}

new_GFSurface* cutChapSurface(new_GFSurface &source,
	int startX, int startY,
	int endX, int endY)
{
	int sizeX = endX - startX;
	int sizeY = endY - startY;
	if (sizeX < 1 || sizeY < 1) return NULL;
	new_GFSurface* surf = initSurface(sizeX, sizeY, 0, 0);
	blitSurface(*surf, source, 0, 0, startX, startY, endX,endY);
	return surf;
}


bool getChapSurface(new_GFSurface &dest,
	new_GFSurface &source,
	int startX, int startY,
	int endX, int endY)
{
	if (startX < 1 || startY < 1) return false;
	blitSurface(dest, source, 0, 0, startX, startY, endX, endY);
	return true;
}

bool getChapSurface(new_GFSurface &dest,
	new_GFSurface &source,
	int startX, int startY)
{
	blitSurface(dest, source, 0, 0, startX, startY, source.ccWidth, source.ccHeight);
	return true;
}

new_GFSurface* picToSurface(char* filename, int pre_open_moves)
{
	BMPPicture* bpic = bmpReader(filename);
	if (!bpic) return NULL;
	if (pre_open_moves == UP_MIRROR)
	{
		bmpRotate(*bpic);
		bmpMirror(*bpic);
		bmpRotate(*bpic);
	}
	new_GFSurface* cpic = initSurface(bpic->info.biWidth, bpic->info.biHeight, 0, 0);
	convertPicture(*cpic, *bpic, 127, 127, &rgbMask());
	// bmpClear(); // Это лучше тут не оставлять
	return cpic;
}

void posSurface(new_GFSurface &surf, int posX, int posY)
{
	if (!NO_POS) surf.posX = posX;
	if (!NO_POS) surf.posY = posY;
}

void SetColorBgTex(int Bg = 0, int Tex = 15) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Bg = Bg << 4 | Tex;
	SetConsoleTextAttribute(hConsole, Bg);
}
void SetConsCurPos(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { (short)x, (short)y };
	SetConsoleCursorPosition(hConsole, coord);
}
void SetConsWinSize(int XSize = 20, int YSize = 10) {
	HWND hWnd = GetForegroundWindow();
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetWindowPos(hWnd, NULL, 0, 0, XSize, YSize, NULL);
	SMALL_RECT windowSize;
	windowSize.Bottom = YSize;
	windowSize.Left = 0;
	windowSize.Right = XSize;
	windowSize.Top = 0;
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	COORD bufferSize = { (short)XSize + 1, (short)YSize + 1 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	SetColorBgTex(0,15);
}
//void GetWindowSize