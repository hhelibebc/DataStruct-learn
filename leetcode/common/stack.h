#pragma once
#include "list.h"

class Stack{
public:
	Stack(){}
	~Stack(){}
	void Push(BaseData* elem);
	BaseData Pop();
	BaseData& Top();
	LinearList* GetData() { return &data; };
private:
	LinearList data;
};
