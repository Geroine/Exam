#include "ProcessManager.h"

typedef int(*func)(GameData);

func processManagerMemory(GameData &options)
{
	int memSize = 0;
	func* funmass = new func[memSize];
	return funmass[1];
}

void processManagerApp(GameData &options)
{
	int memSize = 0;
	func* funmass = new func[memSize];

	if (!memSize)
	{
		for (int i = 0; i < memSize; i++)
		{
			int result = funmass[i](options);
			if (result == -1)
			{

			}
		}	
	}
}