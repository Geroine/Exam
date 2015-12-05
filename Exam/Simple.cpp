#pragma once
#include "Simple.h"

int average(int a, int b)
{
	return (a + b) / 2;
}

bool isNum(char* num)
{
	if (num == NULL) return false;
	if (strcmp("0", num) && !atoi(num)) return false;
	return true;
}

void bufclean()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
}



NumberArray readlvlFile(char* filename)
{
	NumberArray level;
	level.sizeX = 0;
	level.sizeY = 0;
	level.idArray = NULL;

	char* lvldata = NULL;
	int size = 0;

	FILE* file = fopen(filename, "r");
	if (file)
	{
		while (!feof(file))
		{
			char buff = fgetc(file);
			addElement(lvldata, size, buff);
		}
		char* textHeight = _strdup(lvldata);
		textHeight = strtok(textHeight, "\n");
		while (textHeight)
		{
			level.sizeY++;
			textHeight = strtok(NULL, "\n");
		}
		delete[] textHeight;

		char* textWidth = _strdup(lvldata);
		textWidth = strtok(textWidth, ",\n");
		level.sizeX++;
		while (!strchr(textWidth, (char)'\n'))
		{
			level.sizeX++;
			textWidth = strtok(NULL, ",");
		}

		level.idArray = new int*[level.sizeY];
		for (int i = 0; i < level.sizeY; i++)
		{
			level.idArray[i] = new int[level.sizeX];
		}
		lvldata = strtok(lvldata, "\n,");
		for (int i = 0; i < level.sizeY; i++)
		{
			for (int j = 0; j < level.sizeX; j++)
			{
				if (isNum(lvldata))
					level.idArray[i][j] = atoi(lvldata);
				lvldata = strtok(NULL, "\n,");
			}
		}
		fclose(file);
	}
	return level;
}