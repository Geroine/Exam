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
			addElement(KBHitBase, BaseSize, Key);
			return true;
		}
		if (BaseSize && !KB_Pressed(Key))
		{
			for (int i = 0; i < BaseSize; i++)
			{
				if (KBHitBase[i] == Key)
				{
					removeElement(KBHitBase, BaseSize, i);
					break;
				}
			}
		}
	
	return false;
}
