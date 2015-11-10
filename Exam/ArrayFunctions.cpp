#include "ArrayFunctions.h"

template <typename T>
void removeElement(T* &arr, int &size, int id)
{
	if (size == 0)
		return ;

	if (size == 1 && id == 0)
	{
		delete[] arr;
		size--;
		return ;
	}

	T* newArr = new T[size - 1];
	if (id < 0 || id > size - 1) return ;
	for (int i = 0, k = 0; i < size; i++)
	{
		if (i != id)
			newArr[k++] = arr[i];
	}
	size--;
	delete[] arr;
	arr = newArr;
	return ;
}