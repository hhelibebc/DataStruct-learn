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
class LinearList: public LinearADT{
public:
	LinearList();
	~LinearList();
	void Insert(BaseData* elem,int idx);
	void Delete(int idx);
	BaseData& operator[](int idx);

	BaseData* Data(){return pBase;}
	int GetLength(){return len;}
	void SetLength(int arg){len = arg;}
	int Size(){return size;}
private:
	void Resize(int newSize);
private:
	BaseData* pBase;
	int len;
	int size;
};
class LinkList : public LinearADT {
public:
	LinkList();
	~LinkList();
	void Insert(BaseData* elem,int idx);
	void Delete(int idx);
	LNode* GetNode(int idx);
	BaseData& operator[](int idx);
	int GetLength(){return len;}
private:
	LNode *head,*rear;
	int len;
};
class DLinkList : public LinearADT {
public:
	DLinkList();
	~DLinkList();
	void Insert(BaseData* elem,int idx);
	void Delete(int idx);
	DLNode* GetNode(int idx);
	BaseData& operator[](int idx);
	int GetLength(){return len;}
private:
	DLNode *head,*rear;
	int len;
};
