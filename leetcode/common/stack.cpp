#include "stdafx.h"
#include "stack.h"

void Stack::Push(BaseData* elem){
	data.Insert(elem,data.Length());
}
BaseData Stack::Pop(){
	BaseData tmp = Top();
	data.Delete(data.Length()-1);
	return tmp;
}
BaseData& Stack::Top(){
	return data[data.Length()-1];
}
void Stack::Print(){
	data.Print();
}
