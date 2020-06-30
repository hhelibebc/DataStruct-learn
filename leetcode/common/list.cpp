#include "stdafx.h"
#include "list.h"

LinearList::LinearList(){
	size = 0;
	len = 0;
	Resize(LIST_INIT_SIZE);
}
LinearList::~LinearList(){
	for(int i=0;i<len;i++){
		(pBase+i)->~BaseData();
	}
	free(pBase);
	pBase = 0;
	len = 0;
	size = 0;
}
void LinearList::Resize(int newSize){
	assert(newSize >= 0);
	if(0 == newSize)
		this->~LinearList();
	else{
		BaseData* p;
		p = (BaseData*)realloc(pBase,newSize*sizeof(BaseData));
		if(NULL != p){
			pBase = p;
			size = newSize;
			if(len>size)
				len = size;
		}
	}
}
void LinearList::Insert(BaseData* elem,int idx){
	assert(idx>=0 && idx<=len);
	assert(NULL != elem);
	if(len == size)
		Resize(size + LIST_INCREAMENT);
	if(idx < len)
		memmove(pBase+idx+1,pBase+idx,sizeof(BaseData)*(len-idx));
	pBase[idx] = *elem;
	len++;
}
void LinearList::Delete(int idx){
	assert(idx>=0 && idx<len);
	pBase[idx].~BaseData();
	memmove(pBase+idx,pBase+idx+1,sizeof(BaseData)*(len-idx-1));
	CLEAROBJ(pBase+len-1);
	len--;
}
BaseData& LinearList::operator[](int idx){
	assert(idx>=0 && idx<=len);
	return *(pBase+idx);
}
void LinearList::Print(){
	for(int i=0;i<len;i++)
		pBase[i].Print();
	printf("\n");
}

LinkList::LinkList(){
	head = rear = new LNode();
	len = 0;
}
LinkList::~LinkList(){
	LNode* tmp;
	while(len--){
		tmp = head;
		head = head->next;
		delete tmp;
	}
}
LNode* LinkList::operator[](int idx){
	assert(idx<=len);
	LNode* tmp = head->next;
	while(idx-- > 0){
		tmp = tmp->next;
	}
	return tmp;
}
void LinkList::Print(){
	LNode* tmp = head->next;
	for(int i=0;i<len;i++){
		tmp->data.Print();
		tmp = tmp->next;
	}
	printf("\n");
}
void LinkList::Insert(BaseData* elem,int idx){
	assert(idx>=0 && idx<=len);
	LNode* tmp = new LNode();
	tmp->data = *elem;
	LNode* pf;
	LNode* pb;

	if(0 == idx)
		pf = head;
	else if(len == idx)
		pf = rear;
	else
		pf = this->operator[](idx);
	pb = pf->next;

	pf->next = tmp;
	tmp->next = pb;
	if(NULL == pb)
		rear = tmp;
	len++;
}
void LinkList::Delete(int idx){
	assert(idx>=0 && idx<len);
	LNode* pf;
	LNode* pb;
	if(0 == idx)
		pf = head;
	else
		pf = this->operator[](idx-1);
	pb = pf->next;

	pf->next = pb->next;
	if(NULL == pf->next)
		rear = pf;
	delete pb;
	len--;
}

DLinkList::DLinkList(){
	head = rear = new DLNode();
	len = 0;
}
DLinkList::~DLinkList(){
	DLNode* tmp;
	while(len--){
		tmp = head;
		head = head->next;
		delete tmp;
	}
}
void DLinkList::Print(){
	DLNode* tmp = head->next;
	for(int i=0;i<len;i++){
		tmp->data.Print();
		tmp = tmp->next;
	}
	printf("\n");
}
DLNode* DLinkList::operator[](int idx){
	assert(idx<=len);
	DLNode* tmp;
	if(idx <= len/2){
		tmp = head->next;
		while(idx-- > 0){
			tmp = tmp->next;
		}
	}
	else{
		tmp = rear;
		idx = len - idx - 1;
		while(idx-- > 0){
			tmp = tmp->front;
		}
	}
	return tmp;
}
void DLinkList::Insert(BaseData* elem,int idx){
	assert(idx>=0 && idx<=len);
	DLNode* tmp = new DLNode();
	DLNode* pf;
	DLNode* pb;

	tmp->data = *elem;
	if(0 == idx)
		pf = head;
	else if(len == idx)
		pf = rear;
	else
		pf = this->operator[](idx);
	pb = pf->next;

	pf->next = tmp;
	tmp->front = pf;
	if(NULL != pb){
		tmp->next = pb;
		pb->front = tmp;
	}
	else{
		rear = tmp;
	}
	len++;
}
void DLinkList::Delete(int idx){
	assert(idx>=0 && idx<len);
	DLNode* tmp;
	DLNode* pf;
	DLNode* pb;

	tmp = this->operator[](idx);
	pf = tmp->front;
	pb = tmp->next;

	pf->next = pb;
	if(NULL != pb)
		pb->front = pf;
	else
		rear = pf;
	delete tmp;
	len--;
}
