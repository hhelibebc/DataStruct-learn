#pragma once

#include "list.h"
// 基础队列、双向队列、循环队列、双向循环队列
class Queue{
public:
	Queue():allowOverlap(false){}
	bool IsFull();
	bool IsEmpty();
	int GetLength();
	void Push(BaseData* elem);
	BaseData Pop();
	void Print();
	void SetAllowOverlap(bool flag){allowOverlap = flag;}
protected:
	LinearList data;
	bool allowOverlap;
};
class Deque:public Queue{
public:
	void rPush(BaseData* elem);
	BaseData rPop();
};
class LoopQueue:public Queue{
public:
	LoopQueue();
	bool IsFull();
	bool IsEmpty();
	int GetLength();
	void Push(BaseData* elem);
	BaseData Pop();
	void Print();
protected:
	int head;
	int rear;
};
class LoopDeque:public LoopQueue{
public:
	void rPush(BaseData* elem);
	BaseData rPop();
};
// 链队、双向链队
class LinkQueue{
public:
	void Push(BaseData* elem);
	BaseData Pop();
	void Print();
private:
	LinkList data;
};
class LinkDeque{
public:
	void Push(BaseData* elem);
	BaseData Pop();
	void rPush(BaseData* elem);
	BaseData rPop();
	void Print();
private:
	DLinkList data;
};
