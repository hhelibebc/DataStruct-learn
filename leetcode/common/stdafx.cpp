#include "stdafx.h"
#include "..\common\list.h"
#include "..\common\tree.h"
#include "..\common\queue.h"
#include "..\common\map.h"

Button BaseData::button = Button();
BaseData base;
PrintCtrl pc;
Map map1;

float map_data[] = {
	0,-4,0,0,0,0,0,0,
	0,0,0,0,0,4,0,0,
	3,0,0,5,0,0,2,0,
	0,0,0,0,6,0,0,0,
	0,0,0,-3,0,8,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,3,
	0,0,0,0,0,7,-6,0,
};
Point map_addr[] = {
	{100,0},{200,0},{0,100},{100,100},
	{200,100},{300,100},{100,200},{200,200},
};
Point map1_addr[] = {
	{56,151},{42,600},{86,500},{96,306},{118,230},
	{119,414},{136,345},{183,301},{196,465},{214,230},
	{269,292},{306,351},{306,425},{328,278},{380,315},
	{390,449},{390,516},{405,270},{416,135},{436,353},
	{440,401},{450,305},{454,583},{472,229},{484,73},
	{488,466},{502,287},{522,348},{524,402},{555,183},
	{564,260},{567,507},{574,577},{576,307},{590,128},
	{602,373},{606,216},{611,65},{624,449},{639,322},
	{653,273},{689,187},{700,343},{719,286},{738,450},
	{770,35},{775,337},{795,585},
};
Point map1_edge[] = {
	{0,4},
	{1,2},
	{2,1},{2,5},
	{3,4},{3,6},{3,7},
	{4,0},{4,3},{4,9},
	{5,2},{5,6},{5,8},
	{6,3},{6,5},{6,7},
	{7,3},{7,10},{7,11},
	{8,5},{8,12},
	{9,4},{9,10},
	{10,7},{10,9},{10,13},
	{11,7},{11,12},{11,14},{11,19},
	{12,8},{12,11},{12,15},
	{13,10},{13,14},{13,17},
	{14,11},{14,13},{14,19},{14,21},
	{15,12},{15,16},{15,20},{15,25},
	{16,15},{16,22},
	{17,13},{17,18},{17,21},{17,23},
	{18,17},{18,23},{18,24},
	{19,11},{19,14},{19,20},{19,27},
	{20,15},{20,19},{20,25},{20,28},
	{21,14},{21,17},{21,26},{21,27},
	{22,16},{22,25},
	{23,17},{23,18},{23,26},{23,29},{23,30},
	{24,18},{24,34},{24,37},
	{25,15},{25,20},{25,22},{25,28},{25,31},
	{26,21},{26,23},{26,33},
	{27,19},{27,21},{27,33},{27,35},
	{28,20},{28,25},{28,38},
	{29,23},{29,30},{29,34},{29,36},{29,41},
	{30,23},{30,29},{30,33},{30,36},{30,40},
	{31,25},{31,32},{31,38},
	{32,31},
	{33,26},{33,27},{33,30},{33,40},
	{34,24},{34,29},{34,37},{34,41},
	{35,27},{35,38},{35,39},{35,42},
	{36,29},{36,30},{36,40},
	{37,24},{37,34},{37,45},
	{38,28},{38,31},{38,35},{38,42},{38,44},
	{39,35},{39,40},{39,42},
	{40,33},{40,36},{40,39},{40,41},{40,43},
	{41,29},{41,34},{41,40},{41,43},
	{42,35},{42,38},{42,39},{42,43},{42,46},
	{43,40},{43,41},{43,42},
	{44,38},{44,46},{44,47},
	{45,37},
	{46,42},{46,44},
	{47,44},
};

void BaseData::Print()
{
	char buf[10];
	sprintf(buf, "%d", var);
	button.text.Set_str(buf);
	button.text.Set_pt(pc.left + 12, pc.top + 1);
	button.border.Set_size(pc.nodeWidth, pc.nodeHeight);
	button.border.Set_location(pc.left, pc.top);
	button.Print();
	pc.right = pc.left + pc.nodeWidth;
	pc.bottom = pc.top + pc.nodeHeight;
}
bool BaseData::operator>(BaseData& src)
{
	return var > src.var;
}
void BaseData::SetColor(COLOR c)
{
	COLORREF bc = COLOR_BLACK, fc = COLOR_WHITE;
	switch (c)
	{
	case GRAY:
		bc = COLOR_BLACK;
		fc = COLOR_GRAY;
		break;
	case BLACK:
		bc = COLOR_WHITE;
		fc = COLOR_BLACK;
		break;
	case RED:
		bc = COLOR_BLACK;
		fc = COLOR_RED;
		break;
	default:
		break;
	}
	if (pc.EllipseNode)
		button.border.Set_shape(SHAPE_ELLIPSE);
	button.text.SetTextProp(TA_CENTER, true, bc);
	button.border.SetPenProp(PS_SOLID, 1, bc);
	button.border.SetBrushProp(fc);
}

void reset() {
	pc.width = app.rect.right - app.rect.left - 20;
	pc.height = app.rect.bottom - app.rect.top - 20;
}
void init() {
	//map1.Init(map_data, map_addr, 8, true, true);
	map1.Init(map1_edge, map1_addr, 48, 154, false, true);
}
void test() {
	pc.Print(&map1);
}

void PrintCtrl::DrawLine(WORD x1, WORD y1, WORD x2, WORD y2)
{
	line1.SetParam(x1, y1, x2, y2);
	line1.Print();
}
void PrintCtrl::Print(LinearADT* pLinear)
{
	pLinear->Reset();
	LinearView(pLinear);
}
void PrintCtrl::Print(TreeADT* pTree)
{
	pTree->Reset();
	TreeView(pTree, Rect(left, top, width, height));
}
void PrintCtrl::Print(MapADT* pMap)
{
	pMap->Reset();
	pMap->Print();
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
void PrintCtrl::TreeView(TreeADT* pTree,Rect target)
{
	if (NULL != pTree) {
		Rect rect;
		DTNode* p = (DTNode*)pTree;
		left = target.l + target.w / 2;
		top = target.t;
		BaseData::SetColor(pTree->GetColor());
		p->data.Print();
		WORD x1 = GetCenter(0);
		WORD y1 = bottom;
		int cnt = pTree->GetChildCnt();
		if (cnt == 0)return;
		target.w /= cnt;
		rect.l = target.l;
		rect.t = target.t + 60;
		rect.w = target.w;
		for (int i = 0; i < cnt; i++) {
			DrawLine(x1, y1, rect.l + target.w / 2 + 20, rect.t);
			TreeView(pTree->GetChild(i),rect);
			rect.l += target.w;
		}
	}
}

void LinearADT::Reset()
{
	pc.left = 10;
	pc.top = 10;
	reset();
	pc.nodeWidth = 50;
	pc.nodeHeight = 30;
	pc.EllipseNode = false;
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
void TreeADT::Reset()
{
	pc.left = 10;
	pc.top = 10;
	reset();
	pc.nodeWidth = 50;
	pc.nodeHeight = 30;
	pc.EllipseNode = false;
}
void MapADT::Reset()
{
	pc.nodeWidth = 30;
	pc.nodeHeight = 30;
	pc.EllipseNode = true;
}
