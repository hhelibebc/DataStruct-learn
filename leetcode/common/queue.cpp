#include "stdafx.h"
#include "queue.h"

bool Queue::IsFull(){
	return (data.GetLength() >= data.Size());
}
bool Queue::IsEmpty(){
	return (data.GetLength() <= 0);
}
int Queue::GetLength(){
	return data.GetLength();
}
void Queue::Push(BaseData* elem){
	assert(!IsFull() || allowOverlap);
	data.Insert(elem,data.GetLength());
}
BaseData Queue::Pop(){
	assert(!IsEmpty());
	BaseData tmp = data[0];
	data.Delete(0);
	return tmp;
}

void Deque::rPush(BaseData* elem){
	assert(!IsFull() || allowOverlap);
	data.Insert(elem,0);
}
BaseData Deque::rPop(){
	assert(!IsEmpty());
	BaseData tmp = data[data.GetLength()-1];
	data.Delete(data.GetLength()-1);
	return tmp;
}

LoopQueue::LoopQueue(){
	head = rear = 0;
	data.SetLength(data.Size()-1);
}
bool LoopQueue::IsFull(){
	return (GetLength() == data.Size()-1);
}
bool LoopQueue::IsEmpty(){
	return (GetLength() == 0);
}
int LoopQueue::GetLength(){
	if(head <= rear)
		return rear-head;
	else
		return data.Size()-(head-rear);
}
void LoopQueue::Push(BaseData* elem){
	assert(!IsFull() || allowOverlap);
	if(IsFull() && ++head == data.Size())
		head = 0;
	data[rear] = *elem;
	if(++rear == data.Size())
		rear = 0;
}
BaseData LoopQueue::Pop(){
	assert(!IsEmpty());
	BaseData tmp = data[head];
	if(++head == data.Size())
		head = 0;
	return tmp;
}
BaseData& LoopQueue::operator[](int idx)
{
	int t = data.Size();
	assert(idx >= 0 && idx < t - 1);
	if (idx < t - head)
		return data[head + idx];
	else
		return data[idx - (t - head)];
}

void LoopDeque::rPush(BaseData* elem){
	assert(!IsFull() || allowOverlap);
	if(IsFull() && --rear == -1)
		rear = data.GetLength();
	if(--head == -1)
		head = data.GetLength();
	data[head] = *elem;
}
BaseData LoopDeque::rPop(){
	assert(!IsEmpty());
	if(--rear == -1)
		rear = data.GetLength();
	BaseData tmp = data[rear];
	return tmp;
}

void LinkQueue::Push(BaseData* elem){
	data.Insert(elem,data.GetLength());
}
BaseData LinkQueue::Pop(){
	BaseData tmp = data.GetNode(0)->data;
	data.Delete(0);
	return tmp;
}

void LinkDeque::Push(BaseData* elem){
	data.Insert(elem,data.GetLength());
}
BaseData LinkDeque::Pop(){
	BaseData tmp = data[0];
	data.Delete(0);
	return tmp;
}
void LinkDeque::rPush(BaseData* elem){
	data.Insert(elem,0);
}
BaseData LinkDeque::rPop(){
	BaseData tmp = data[data.GetLength()-1];
	data.Delete(data.GetLength()-1);
	return tmp;
}

