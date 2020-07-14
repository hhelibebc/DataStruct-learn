#include "stdafx.h"
#include "..\common\list.h"
#include "..\common\tree.h"

BaseData base;
PrintCtrl pc;
LinkList list1;
MTNode tree1;
DTNode tree2;

void BaseData::Print()
{
	Button button;
	char buf[10];
	sprintf(buf, "%d", var);
	button.text.Set_str(buf);
	button.text.Set_pt(pc.left + 5, pc.top + 5);
	button.border.Set_size(button.text.GetLength() * 20, 32);
	button.border.Set_location(pc.left, pc.top);
	button.Refresh();
	pc.right = pc.left + button.border.GetWidth();
	pc.bottom = pc.top + button.border.GetHigh();
}
void reset() {
	pc.width = app.rect.right - app.rect.left - 20;
	pc.height = app.rect.bottom - app.rect.top - 20;
}
void init() {
	/*for (int i = 0; i < 15; i++) {
		base.var = i;
		list1.Insert(&base, i);
	}*/
	/*MTNode* p = &tree1;
	base.var = 1;
	p->AddChild(&base);
	base.var = 2;
	p->AddChild(&base);
	p = (MTNode * )p->GetChild(0);
	base.var = 3;
	p->AddChild(&base);
	base.var = 4;
	p->AddChild(&base);
	base.var = 5;
	p->AddChild(&base);
	p = p->brother;
	base.var = 6;
	p->AddChild(&base);
	base.var = 7;
	p->AddChild(&base);
	base.var = 8;
	p->AddChild(&base);
	base.var = 9;
	p->AddChild(&base);
	base.var = 10;
	p->AddChild(&base);*/
	for (int i = 0; i < 51; i++) {
		base.var = i;
		tree2.AddChild(&base);
	}
}
void test() {
	//pc.Print(&list1);
	//pc.Print(&tree1);
	pc.Print(&tree2);
}

void PrintCtrl::DrawLine(WORD x1, WORD y1, WORD x2, WORD y2)
{
	line1.Set_pt1(x1, y1);
	line1.Set_pt2(x2, y2);
	line1.Refresh();
}
void PrintCtrl::Print(LinearADT* pLinear)
{
	pLinear->ResetPosition();
	LinearView(pLinear);
}
void PrintCtrl::Print(TreeADT* pTree)
{
	pTree->ResetPosition();
	TreeView(pTree, Rect(left, top, width, height));
}
void PrintCtrl::LinearView(LinearADT* pLinear)
{
	BYTE dir = 0, state = 0;
	(*pLinear)[0].Print();
	for (int i = 1; i < pLinear->GetLength(); i++) {
		switch (state) {
		case 0:
			if (left + 120 >= width) {
				state = 1;
				i--;
				break;
			}
			left += 70;
			DrawLine(right, GetCenter(1),left, GetCenter(1));
			(*pLinear)[i].Print();
			break;
		case 1:
			if (dir == 0) {
				dir = 1;
				state = 2;
			}
			else {
				dir = 0;
				state = 0;
			}
			top += 40;
			DrawLine(GetCenter(0), bottom, GetCenter(0), top);
			(*pLinear)[i].Print();
			i--;
			break;
		case 2:
			if (left < 70) {
				state = 1;
				i--;
				break;
			}
			left -= 70;
			(*pLinear)[i].Print();
			DrawLine(right, GetCenter(1), left + 70, GetCenter(1));
			break;
		}
	}
}
void PrintCtrl::TreeView(TreeADT* src,Rect target)
{
	if (NULL != src) {
		Rect rect;
		DTNode* p = (DTNode*)src;
		left = target.l + target.w / 2;
		top = target.t;
		p->data.Print();
		WORD x1 = GetCenter(0);
		WORD y1 = bottom;
		int cnt = src->GetChildCnt();
		if (cnt == 0)return;
		target.w /= cnt;
		rect.l = target.l;
		rect.t = target.t + 60;
		rect.w = target.w;
		for (int i = 0; i < cnt; i++) {
			DrawLine(x1, y1, rect.l + target.w / 2, rect.t);
			TreeView(src->GetChild(i),rect);
			rect.l += target.w;
		}
	}
}

int TreeADT::GetDepth()
{
	int max = 0, cnt = 0, tmp = 0;
	if (NULL != this) {
		cnt = GetChildCnt();
		for (int i = 0; i < cnt; i++) {
			tmp = GetChild(i)->GetDepth();
			if (tmp > max) max = tmp;
		}
	}
	return max + 1;
}
void TreeADT::ResetPosition()
{
	pc.left = 10;
	pc.top = 10;
	reset();
}

void LinearADT::ResetPosition()
{
	pc.left = 10;
	pc.top = 10;
	reset();
}
