#include "GraphicFunc.h"
#define ALGORITHM 2
#define CC_TRUE 127
#define CC_HALF 127
#define CC_1W 191
#define CC_2W 127
#define CC_3W 50


void convertPicture(GFSurface &cpic, BMPPicture &bpic, int cc_true = CC_TRUE, int cc_half = CC_HALF)
{
	cpic.ccHeight = bpic.info.biHeight;
	cpic.ccWidth = bpic.info.biWidth;
	cpic.bitmap = new char*[cpic.ccHeight];
	for (int i = 0; i < cpic.ccHeight; i++)
	{
		cpic.bitmap[i] = new char[cpic.ccWidth];
	}

	char ccResult = 0;

#if ALGORITHM == 2
	int cc1, cc2, cc3, cc12, cc13, cc23, cc123;
	for (int i = 0; i < cpic.ccHeight; i++)
	{
		for (int j = 0; j < cpic.ccWidth; j++)
		{
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


			cpic.bitmap[i][j] = ccResult;
		}
	}
#elif ALGORITHM == 1

int ccSum;
for (int i = 0; i < cpic.ccHeight; i++)
{
	for (int j = 0; j < cpic.ccWidth; j++)
	{
		ccSum = (bpic.bitmap[i][j].rgbRed +
			bpic.bitmap[i][j].rgbGreen +
			bpic.bitmap[i][j].rgbBlue) / 3;


		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum <= 127)
			ccResult = CC_DarkBlue;

		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum <= 127)
			ccResult = CC_DarkGreen;

		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum <= 127)
			ccResult = CC_DarkCyan;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum <= 127)
			ccResult = CC_DarkRed;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum <= 127)
			ccResult = CC_DarkMagenta;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum <= 127)
			ccResult = CC_DarkYellow;

		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum > 127)
			ccResult = CC_Blue;

		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum > 127)
			ccResult = CC_Green;

		if (bpic.bitmap[i][j].rgbRed <= 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum > 127)
			ccResult = CC_Cyan;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum > 127)
			ccResult = CC_Red;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen <= 127 &&
			bpic.bitmap[i][j].rgbBlue > 127 &&
			ccSum > 127)
			ccResult = CC_Magenta;

		if (bpic.bitmap[i][j].rgbRed > 127 &&
			bpic.bitmap[i][j].rgbGreen > 127 &&
			bpic.bitmap[i][j].rgbBlue <= 127 &&
			ccSum > 127)
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


		cpic.bitmap[i][j] = ccResult;
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

void convertBMP(BMPPicture &bpic, int cc_true, int cc_half)
{
	GFSurface cpic;
	convertPicture(cpic, bpic, cc_true, cc_half);

	for (int i = 0; i < cpic.ccHeight; i++)
	{
		for (int j = 0; j < cpic.ccWidth; j++)
		{
			bpic.bitmap[i][j] = getColor(cpic.bitmap[i][j]);
		}
	}
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
}