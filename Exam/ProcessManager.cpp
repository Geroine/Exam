#include "ProcessManager.h"

Tasker processPrepair()
{
	Tasker tasker;
	tasker.memSize = 0;
	tasker.activeFunctions = NULL;
	tasker.nameFunctions = new char*[tasker.memSize];
	return tasker;
}

void processGraphicPrepair(Tasker &tasker, TaskerGraph &graphic)
{
	graphic.xSize = 32;
	graphic.ySize = 22;
	graphic.graphicTasker = new char*[graphic.ySize];
	for (int i = 0; i < graphic.ySize; i++)
	{
		graphic.graphicTasker[i] = new char[graphic.xSize + 1];
	}
}

void processGraphicDelete(TaskerGraph &graphic)
{
	delete2d(graphic.graphicTasker, graphic.ySize);
}

void processPush(Tasker &tasker, mainFunctionType function, char* functioName)
{
	addElement(tasker.activeFunctions, tasker.memSize, function);
	int charMem = tasker.memSize;
	addElement(tasker.nameFunctions, charMem, functioName);
}

void processIterator(GameData &options, Tasker &tasker)
{
	for (int i = 0; i < tasker.memSize; i++)
	{
		int result = tasker.activeFunctions[i](options);
		if (result == -1)
		{
			removeElement(tasker.activeFunctions, tasker.memSize, i);
			int charMem = tasker.memSize;
			removeElement(tasker.nameFunctions, charMem, i);
		}
	}
}

bool processSwap(Tasker &tasker, int id1, int id2)
{
	if (id1 < 0 || id2 < 0) return false;
	if (id1 > tasker.memSize || id2 > tasker.memSize) return false;

	swapElement(tasker.activeFunctions, tasker.memSize, id1, id2);

	return true;
}
