#include "stdafx.h"
#include "queue.h"

bool Queue::IsFull(){
	return (data.Length() >= data.Size());
}
bool Queue::IsEmpty(){
	return (data.Length() <= 0);
}
int Queue::Length(){
	return data.Length();
}
void Queue::Push(BaseData* elem){
	assert(!IsFull() || allowOverlap);
	data.Insert(elem,data.Length());
}
BaseData Queue::Pop(){
	assert(!IsEmpty());
	BaseData tmp = data[0];
	data.Delete(0);
	return tmp;
}
void Queue::Print(){
	data.Print();
}

void Deque::rPush(BaseData* elem){
	assert(!IsFull() || allowOverlap);
	data.Insert(elem,0);
}
BaseData Deque::rPop(){
	assert(!IsEmpty());
	BaseData tmp = data[data.Length()-1];
	data.Delete(data.Length()-1);
	return tmp;
}

LoopQueue::LoopQueue(){
	head = rear = 0;
	data.SetLength(data.Size()-1);
}
bool LoopQueue::IsFull(){
	return (Length() == data.Size()-1);
}
bool LoopQueue::IsEmpty(){
	return (Length() == 0);
}
int LoopQueue::Length(){
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
void LoopQueue::Print(){
	int i;
	if(head > rear){
		for(i=head;i<=data.Length();i++)
			data[i].Print();
		for(i=0;i<rear;i++)
			data[i].Print();
	}
	else{
		for(i=head;i<rear;i++)
			data[i].Print();
	}
	printf("\n");
}

void LoopDeque::rPush(BaseData* elem){
	assert(!IsFull() || allowOverlap);
	if(IsFull() && --rear == -1)
		rear = data.Length();
	if(--head == -1)
		head = data.Length();
	data[head] = *elem;
}
BaseData LoopDeque::rPop(){
	assert(!IsEmpty());
	if(--rear == -1)
		rear = data.Length();
	BaseData tmp = data[rear];
	return tmp;
}

void LinkQueue::Push(BaseData* elem){
	data.Insert(elem,data.Length());
}
BaseData LinkQueue::Pop(){
	BaseData tmp = data[0]->data;
	data.Delete(0);
	return tmp;
}
void LinkQueue::Print(){
	data.Print();
}

void LinkDeque::Push(BaseData* elem){
	data.Insert(elem,data.Length());
}
BaseData LinkDeque::Pop(){
	BaseData tmp = data[0]->data;
	data.Delete(0);
	return tmp;
}
void LinkDeque::rPush(BaseData* elem){
	data.Insert(elem,0);
}
BaseData LinkDeque::rPop(){
	BaseData tmp = data[data.Length()-1]->data;
	data.Delete(data.Length()-1);
	return tmp;
}
void LinkDeque::Print(){
	data.Print();
}
