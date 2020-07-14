#pragma once

typedef enum{
	PLR,
	PRL,
	LPR,
	RPL,
	LRP,
	RLP,
	LAYER,
}ORDER;

class DTNode :public TreeADT {
public:
	DTNode():left(NULL),right(NULL){}
	virtual TreeADT* GetChild(int idx);
	virtual BaseData& GetChildData(int idx);
	virtual int GetChildCnt();
	void AddChild(BaseData* elem);
	void AddChild(DTNode* src);
	void DelNode();
public:
	static WORD order;
	BaseData data;
	DTNode* left;
	DTNode* right;
};
class MTNode :public TreeADT {
public:
	MTNode() :child(NULL), brother(NULL) {}
	virtual TreeADT* GetChild(int idx);
	virtual BaseData& GetChildData(int idx);
	virtual int GetChildCnt();
	void AddChild(BaseData* elem);
	void AddBrother(MTNode* elem);
	void DelNode();
public:
	BaseData data;
	MTNode* child;
	MTNode* brother;
};
class TTNode :public TreeADT {
public:
	TTNode():parent(NULL),left(NULL),right(NULL){}
	virtual TreeADT* GetChild(int idx);
	virtual BaseData& GetChildData(int idx);
	virtual int GetChildCnt();
public:
	BaseData data;
	TTNode* parent;
	TTNode* left;
	TTNode* right;
};
