#include "stdafx.h"
#include "tree.h"

WORD DTNode::order = 1;
TreeADT* DTNode::GetChild(int idx)
{
	assert(NULL != this);
	assert(idx < 2);
	DTNode* p = (DTNode*)this;
	if (idx == 0)
		return p->left;
	else
		return p->right;
}
BaseData& DTNode::GetChildData(int idx)
{
	DTNode* p = (DTNode*)GetChild(idx);
	return p->data;
}
int DTNode::GetChildCnt()
{
	assert(NULL != this);
	if (NULL != right)
		return 2;
	else if (NULL != left)
		return 1;
	else
		return 0;
}
void DTNode::AddChild(BaseData* elem)
{
	assert(NULL != elem);
	DTNode* tmp = new DTNode();
	tmp->data = *elem;
	AddChild(tmp);
}
void DTNode::AddChild(DTNode* src)
{
	assert(NULL != src);
	WORD layer = 0, tmp;
	order++;
	tmp = order;
	while (tmp >>= 1)
		layer++;
	DTNode* p = this;
	int i;
	for (i = 1; i < layer; i++) {
		if ((order >> (layer - i)) & 1)
			p = p->right;
		else
			p = p->left;
	}
	if (order & 1)
		p->right = src;
	else
		p->left = src;
}
void DTNode::DelNode()
{
	assert(NULL != this);
	if (NULL != left)
		left->DelNode();
	if (NULL != right)
		right->DelNode();
	delete this;
}

TreeADT* MTNode::GetChild(int idx)
{
	assert(NULL != this);
	MTNode* p = (MTNode*)this;
	p = p->child;
	while (idx-- && NULL != p)
		p = p->brother;
	return p;
}
BaseData& MTNode::GetChildData(int idx)
{
	MTNode* p = (MTNode*)GetChild(idx);
	return p->data;
}
int MTNode::GetChildCnt()
{
	assert(NULL != this);
	MTNode* p = (MTNode*)child;
	int i = 0;
	while (NULL != p) {
		p = p->brother;
		i++;
	}
	return i;
}
void MTNode::AddChild(BaseData* elem)
{
	assert(NULL != elem);
	MTNode* tmp = new MTNode();
	tmp->data = *elem;
	if (NULL == child)
		child = tmp;
	else
		child->AddBrother(tmp);
}
void MTNode::AddBrother(MTNode* src)
{
	MTNode* p = this;
	while (NULL != p->brother)
		p = p->brother;
	p->brother = src;
}
void MTNode::DelNode()
{
	assert(NULL != this);
	if (NULL != brother)
		brother->DelNode();
	else if (NULL != child)
		child->DelNode();
	else
		delete this;
}

TreeADT* TTNode::GetChild(int idx)
{
	assert(NULL != this);
	assert(idx < 2);
	TTNode* p = (TTNode*)this;
	if (idx == 0)
		return p->left;
	else
		return p->right;
}
BaseData& TTNode::GetChildData(int idx)
{
	TTNode* p = (TTNode*)GetChild(idx);
	return p->data;
}
int TTNode::GetChildCnt()
{
	assert(NULL != this);
	TTNode* p = (TTNode*)this;
	if (NULL != p->right)
		return 2;
	else if (NULL != p->left)
		return 1;
	else
		return 0;
}
void TTNode::AddChild(BaseData* elem)
{
	assert(NULL != elem);
	TTNode* tmp = new TTNode();
	tmp->data = *elem;
	AddChild(tmp);
}
void TTNode::AddChild(TTNode* src)
{
	if (src->data > data) {
		if (NULL == right)
			right = src;
		else
			right->AddChild(src);
	}
	else {
		if (NULL == left)
			left = src;
		else
			left->AddChild(src);
	}
	if (left->GetDepth() > right->GetDepth() + 1)
		parent->LeftRotate();
	else if (right->GetDepth() > left->GetDepth() + 1)
		parent->RightRotate();
}
void TTNode::DelNode()
{
}
void TTNode::LeftRotate()
{
}
void TTNode::RightRotate()
{
}
void TTNode::DoubleRotate()
{
}
