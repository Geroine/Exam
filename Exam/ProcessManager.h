#pragma once
#include "ProjectHeader.h"

struct GameData;

typedef int(*mainFunctionType)(GameData& options);

enum eTaskAnswer
{
	eDeleteSelf = -1,
	eActive = 0,
	ePauseSelf,
	eRepeatSelf
};

struct Tasker
{
	int memSize;
	mainFunctionType* activeFunctions;
	char** nameFunctions;
};

struct TaskerGraph
{
	int xSize;
	int ySize;
	char** graphicTasker;
};

void processGraphicPrepair(Tasker &tasker, TaskerGraph &graphic);

void processGraphicDelete(TaskerGraph &graphic);

void processPrepair(Tasker &tasker);

void processPush(Tasker &tasker, mainFunctionType function, char* functioName);

bool processSwap(Tasker &tasker, int id1, int id2);

void processIterator(Tasker &tasker, GameData &options);