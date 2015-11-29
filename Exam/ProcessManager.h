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

Tasker processPrepair();

void processPush(Tasker &tasker, mainFunctionType function, char* functioName);

void processIterator(GameData &options, Tasker &tasker);

bool processSwap(Tasker &tasker, int id1, int id2);

