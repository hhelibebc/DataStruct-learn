#pragma once

#define LIST_INIT_SIZE  10
#define LIST_INCREAMENT 10
class LNode{
public:
	LNode():next(NULL){}
public:
	BaseData data;
	LNode *next;
};
class DLNode{
public:
	DLNode():front(NULL),next(NULL){}
public:
	BaseData data;
	DLNode *front;
	DLNode *next;
};
// 线性表、单链表、双链表
class LinearList{
public:
	LinearList();
	~LinearList();
	void Insert(BaseData* elem,int idx);
	void Delete(int idx);
	void Print();
	BaseData& operator[](int idx);

	BaseData* Data(){return pBase;}
	int Length(){return len;}
	void SetLength(int arg){len = arg;}
	int Size(){return size;}
private:
	void Resize(int newSize);
private:
	BaseData* pBase;
	int len;
	int size;
};
class LinkList{
public:
	LinkList();
	~LinkList();
	void Insert(BaseData* elem,int idx);
	void Delete(int idx);
	LNode* operator[](int idx);
	void Print();
	int Length(){return len;}
private:
	LNode *head,*rear;
	int len;
};
class DLinkList{
public:
	DLinkList();
	~DLinkList();
	void Print();
	void Insert(BaseData* elem,int idx);
	void Delete(int idx);
	DLNode* operator[](int idx);
	int Length(){return len;}
private:
	DLNode *head,*rear;
	int len;
};
