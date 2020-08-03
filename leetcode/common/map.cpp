#include "stdafx.h"
#include "map.h"
#include <queue>

static Point pt1, pt2;
static Line line;
static Shape shape;
static Arrow arrow;
static Text text;

int Map::time = 0;
void Map::Init(float* edge, Point* location, int vertex_cnt, bool d, bool w)
{
	int i, j, k = 0;
	float val;
	CommonInit(vertex_cnt, d, w);
	for (i = 0; i < vertex_cnt; i++) {
		vertex[i].data.var = i;
		vertex[i].SetLocation(location[i].x, location[i].y);
		for (j = 0; j < vertex_cnt; j++) {
			this->edge[k].pow = edge[k];
			k++;
		}
	}
}
void Map::Init(Point* edge, Point* location, int vertex_cnt, int edge_cnt, bool d, bool w)
{
	int i, j, k;
	float val;
	CommonInit(vertex_cnt, d, w);
	for (i = 0; i < vertex_cnt; i++) {
		vertex[i].data.var = i;
		vertex[i].SetLocation(location[i].x, location[i].y);
	}
	for (i = 0; i < edge_cnt; i++) {
		j = edge[i].x;
		k = edge[i].y;
		line.SetParam(vertex[j].prop.x, vertex[j].prop.y,
			vertex[k].prop.x, vertex[k].prop.y);
		GetEdge(j, k)->pow = line.Get_len();
	}
}
void Map::BFS(Vertex* s)
{
}
void Map::DFS()
{
}
void Map::DFS_Visit(Vertex* s)
{
}
Edge* Map::GetEdge(int src, int dest)
{
	return edge + src * num + dest;
}
Vertex* Map::GetVertex(int idx)
{
	return vertex + idx;
}
void Map::Print()
{
	Edge* pEdge1;
	Edge* pEdge2;
	Vertex* pVertex1;
	Vertex* pVertex2;
	char tmpstr[10];
	int i, j;
	// 绘制顶点
	for (i = 0; i < num; i++) {
		pc.left = vertex[i].prop.x;
		pc.top = vertex[i].prop.y;
		vertex[i].data.SetColor(vertex[i].prop.color);
		vertex[i].data.Print();
	}	
	shape.Set_size(pc.nodeHeight, pc.nodeWidth);
	shape.Set_shape(SHAPE_ELLIPSE);
	// 绘制连线
	for (i = 0; i < num; i++) {
		for (j = 0; j < num; j++) {
			pEdge1 = GetEdge(i, j);
			if (pEdge1->pow != 0 && !pEdge1->drew) {
				pEdge1->drew = true;
				pt1.x = vertex[i].prop.x + pc.nodeWidth / 2;
				pt1.y = vertex[i].prop.y + pc.nodeHeight / 2;
				pt2.x = vertex[j].prop.x + pc.nodeWidth / 2;
				pt2.y = vertex[j].prop.y + pc.nodeHeight / 2;
				pEdge2 = GetEdge(j, i);
				if (directional && pEdge2->pow != 0) {
					if (pEdge2->drew) {
						pt1.y -= 10;
						pt2.y -= 10;
					}
					else {
						pt1.y += 10;
						pt2.y += 10;
					}
				}
				line.SetParam(pt1.x, pt1.y, pt2.x, pt2.y);

				shape.Set_location(vertex[i].prop.x, vertex[i].prop.y);
				pt1 = shape.GetCrossPoint(line);
				shape.Set_location(vertex[j].prop.x, vertex[j].prop.y);
				pt2 = shape.GetCrossPoint(line);
				pc.DrawLine(pt1.x, pt1.y, pt2.x, pt2.y);

				if (directional) {
					arrow.SetParam(pt1.x, pt1.y, pt2.x, pt2.y, true);
					arrow.Print();
				}

				if (weighted) {
					sprintf(tmpstr, "%.1f", pEdge1->pow);
					text.Set_str(tmpstr);
					text.Set_pt((pt1.x + pt2.x) / 2, (pt1.y + pt2.y) / 2 - 10);
					text.SetTextProp(TA_CENTER, false, COLOR_RED);
					text.Print();
				}
			}
		}
	}
}
void Map::CommonInit(int cnt, bool d, bool w)
{
	num = cnt;
	vertex = new Vertex[cnt];
	edge = new Edge[cnt * cnt];
	directional = d;
	weighted = w;
}

void Vertex::SetLocation(WORD x, WORD y)
{
	prop.x = x;
	prop.y = y;
}
