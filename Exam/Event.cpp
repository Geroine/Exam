#include "Event.h"

bool KB_Pressed(int Key)
{
	short keyState = GetAsyncKeyState(Key);
	return ((keyState & 0x8000) > 0);
}

bool KB_Hit(int Key)
{
	static int BaseSize = 0;
	static int *KBHitBase = new int[BaseSize];
		if (KB_Pressed(Key))
		{
			for (int j = 0; j < BaseSize; j++)
			{
				if (KBHitBase[j] == Key)
					return false;
			}
			int* newBase = new int[++BaseSize];
			for (int i = 0; i < BaseSize - 1; i++)
			{
				newBase[i] = KBHitBase[i];
			}
			newBase[BaseSize - 1] = Key;
			if (BaseSize > 1)
			{
				delete[] KBHitBase;
			}
			KBHitBase = newBase;
			return true;
		}
		if (BaseSize && !KB_Pressed(Key))
		{
			for (int i = 0; i < BaseSize; i++)
			{
				if (KBHitBase[i] == Key)
				{
					if (BaseSize == 1)
					{
						delete[] KBHitBase;
						BaseSize--;
						return false;
					}
					int* newBase = new int[--BaseSize];
					for (int j = 0, k = 0; j < BaseSize+1; j++)
					{
						if (j != i)
							newBase[k++] = KBHitBase[j];
					}
					delete[] KBHitBase;
					KBHitBase = newBase;
					break;
				}
			}
		}
	
	return false;
}
