// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#include "..\display\gui.h"

typedef enum {
	WHITE,
	GRAY,
	BLACK,
	RED,
}COLOR;
class BaseData{
public:
	BaseData():var(0),str(NULL){}
	BaseData(int v,char* s):var(v),str(s){}
	~BaseData(){}
	void Print();
	bool operator>(BaseData& src);
	static void SetColor(COLOR c);
public:
	static Button button;
	int var;
	char* str;
};
class LinearADT {
public:
	virtual BaseData& operator[](int idx) = 0;
	virtual int GetLength() = 0;
	void Reset();
};
class TreeADT {
public:
	virtual TreeADT* GetChild(int idx) = 0;
	virtual BaseData& GetChildData(int idx) = 0;
	virtual int GetChildCnt() = 0;
	virtual COLOR GetColor() = 0;
	int GetDepth();
	void Reset();
};
class MapADT {
public:
	virtual void Print() = 0;
	void Reset();
};
class PrintCtrl {
public:
	WORD GetCenter(BYTE mode) {
		if (mode == 0)
			return (left + right) / 2;
		else
			return (top + bottom) / 2;
	}
	void DrawLine(WORD x1, WORD y1, WORD x2, WORD y2);
	void Print(LinearADT* pLinear);
	void Print(TreeADT* pTree);
	void Print(MapADT* pMap);
private:
	void LinearView(LinearADT* pLinear);
	void TreeView(TreeADT* pTree, Rect target);
public:
	Line line1;
	WORD left, top, right, bottom, width, height;
	bool EllipseNode;
	WORD nodeWidth, nodeHeight;
};

#define CLEAROBJ(p) memset(&p,0,sizeof(p))
#define PI 3.1415926
#define FLOAT_EQUAL(a,b) (fabs((a)-(b))<1e-5)
#define INRANGE(x,v1,v2) ((x>v1&&x<v2)||(x>v2&&x<v1))

extern PrintCtrl pc;
extern void reset();
extern void init();
extern void test();
