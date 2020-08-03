#pragma once

#include "list.h"
// �������С�˫����С�ѭ�����С�˫��ѭ������
class Queue{
public:
	Queue():allowOverlap(false){}
	bool IsFull();
	bool IsEmpty();
	int GetLength();
	void Push(BaseData* elem);
	BaseData Pop();
	void SetAllowOverlap(bool flag){allowOverlap = flag;}
	LinearList* GetData() { return &data; }
protected:
	LinearList data;
	bool allowOverlap;
};
class Deque:public Queue{
public:
	void rPush(BaseData* elem);
	BaseData rPop();
};
class LoopQueue :public Queue, public LinearADT {
public:
	LoopQueue();
	bool IsFull();
	bool IsEmpty();
	int GetLength();
	void Push(BaseData* elem);
	BaseData Pop();
	BaseData& operator[](int idx);
protected:
	int head;
	int rear;
};
class LoopDeque:public LoopQueue{
public:
	void rPush(BaseData* elem);
	BaseData rPop();
};
// ���ӡ�˫������
class LinkQueue{
public:
	void Push(BaseData* elem);
	BaseData Pop();
	LinkList* GetData() { return &data; }
private:
	LinkList data;
};
class LinkDeque{
public:
	void Push(BaseData* elem);
	BaseData Pop();
	void rPush(BaseData* elem);
	BaseData rPop();
	DLinkList* GetData() { return &data; }
private:
	DLinkList data;
};
