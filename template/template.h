#pragma once
#include "include.h"

typedef const char* CPCHAR; 
template<typename T>
int Compare(T src, T dest) {
	if (src > dest)
		return 1;
	else if (src == dest)
		return 0;
	else
		return -1;
}
template<typename T>
int Compare(T* src, T* dest) {
	return memcmp(src, dest, sizeof(T));
}
template<>
extern int Compare(CPCHAR src, CPCHAR dest);

template<typename T>
int Find(T* arr, int cnt, T dest) {
	int ret;
	for (int i = 0; i < cnt; i++) {
		ret = Compare(dest, arr[i]);
		if (ret == 0)
			return i;
		if (ret == -1)
			return -1;
	}
}

template<typename T>
class MyList{
public:
	MyList() :pData(NULL), size(0), capacity(0) {  }
	~MyList() { delete(pData); }
	void Push(T& data);
	T& Pop();
	T& operator[](int idx) { return pData[idx]; }
private:
	void Resize(int newsize);
	T* pData;
	int size;
	int capacity;
};

template<typename T>
inline void MyList<T>::Push(T& data)
{
	if (size == 0)
		Resize(10);
	else if (size == capacity)
		Resize(capacity * 2);
	pData[size++] = data;
}
template<typename T>
inline T& MyList<T>::Pop()
{
	T tmp;
	if (size > 0) {
		tmp = pData[0];
		size--;
		memmove(pData + 1, pData, size * sizeof(T));
	}
	return tmp;
}
template<typename T>
inline void MyList<T>::Resize(int newsize)
{
	delete[] pData;
	capacity = newsize;
	pData = new T[capacity];
}
