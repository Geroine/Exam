#pragma once
#include "ProjectHeader.h"

template <typename T>
bool removeElement(T* &arr, int &size, int id)
{
	if (size == 0)
		return false;

	if (size == 1 && id == 0)
	{
		delete[] arr;
		size--;
		return true;
	}

	T* newArr = new T[size - 1];
	if (id < 0 || id > size - 1) return false;
	for (int i = 0, k = 0; i < size; i++)
	{
		if (i != id)
			newArr[k++] = arr[i];
	}
	size--;
	delete[] arr;
	arr = newArr;
	return true;
}

template <typename T>
void addElement(T* &arr, int &size, T elem)
{
	if (size == 0)
	{
		T* newArr = new T[++size];
		newArr[0] = elem;
		arr = newArr;
		return;
	}

	T* newArr = new T[++size];
	for (int i = 0; i < size-1; i++)
	{
			newArr[i] = arr[i];
	}
	newArr[size - 1] = elem;

	delete[] arr;
	arr = newArr;
	return;
}

template <typename T>
void addElement(T* &arr, int &size, T* elem)
{
	if (size == 0)
	{
		T* newArr = new T[++size];
		newArr[0] = *elem;
		arr = newArr;
		return;
	}

	T* newArr = new T[++size];
	for (int i = 0; i < size - 1; i++)
	{
		newArr[i] = arr[i];
	}
	newArr[size - 1] = *elem;

	delete[] arr;
	arr = newArr;
	return;
}

template <typename T>
void addElementest(T* &arr, int &size, T* elem)
{
	if (size == 0)
	{
		T* newArr = new T[++size];
		newArr[0] = *elem;
		arr = newArr;
		return;
	}

	T* newArr = new T[++size];
	for (int i = 0; i < size - 1; i++)
	{
		newArr[i] = arr[i];
	}
	newArr[size - 1] = *elem;

	delete[] arr;
	arr = newArr;
	return;
}

template <typename T>
bool swapElement(T* &arr, int size, int index1, int index2)
{
	if (index1 < 0 || index2 < 0) return false;
	if (index1 > size || index2 > size) return false;
	T buff;

	buff = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = buff;

	return true;
}

template <typename T>
bool delete2d(T* &arr, int size)
{
	if (size < 1) return false;
	for (int i = 0; i < size; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
	size = 0;
	return true;
}