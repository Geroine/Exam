#pragma once
#include "ProjectHeader.h"

// Вспомогательная структура для временного хранения числового массива, для инициализации игрового уровня
bool isNum(char* num);

int average(int a, int b);

void bufclean();

struct NumberArray
{
	int** idArray;
	int sizeY;
	int sizeX;
};

NumberArray readlvlFile(char* filename);