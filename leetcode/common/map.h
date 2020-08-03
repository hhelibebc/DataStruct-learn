#pragma once

typedef enum {
	NULL_EDGE,
	TREE_EDGE,
	BACK_EDGE,
	FORWARD_EDGE,
	CROSS_EDGE,
}EdgeType;
typedef struct {
	WORD x, y;
	BYTE d;
	BYTE f;
	BYTE pi;
	BYTE ind;
	COLOR color;
}VertexProp;

class Edge {
public:
	Edge() :pow(0.0), type(NULL_EDGE), drew(false) {  }
public:
	float pow;
	EdgeType type;
	bool drew;
};
class Vertex {
public:
	Vertex(){
		CLEAROBJ(prop);
	}
	void SetLocation(WORD x, WORD y);
public:
	BaseData data;
	VertexProp prop;
};
class Map :public MapADT {
public:
	Map() :num(0), vertex(NULL), edge(NULL), directional(false), weighted(false) { }
	void Init(float* edge, Point* addr, int vertex_cnt, bool d, bool w);
	void Init(Point* edge, Point* addr, int vertex_cnt, int edge_cnt, bool d, bool w);
	void BFS(Vertex* s);
	void DFS();
	void DFS_Visit(Vertex* s);
	Edge* GetEdge(int src, int dest);
	Vertex* GetVertex(int idx);
	virtual void Print();
private:
	void CommonInit(int cnt, bool d, bool w);
	static int time;
	BYTE num;
	Vertex* vertex;
	Edge* edge;
	bool directional, weighted;
};
