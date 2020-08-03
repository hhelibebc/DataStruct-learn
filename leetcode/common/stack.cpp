#include "stdafx.h"
#include "stack.h"

void Stack::Push(BaseData* elem){
	data.Insert(elem,data.GetLength());
}
BaseData Stack::Pop(){
	BaseData tmp = Top();
	data.Delete(data.GetLength()-1);
	return tmp;
}
BaseData& Stack::Top(){
	return data[data.GetLength()-1];
}
