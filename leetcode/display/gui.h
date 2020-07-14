#pragma once
#include "core.h"

typedef enum {
	SOLID,
	DOT,
	DASH,
	DOT_DASH,
	DDOT_DASH,
}LineStyle;
typedef enum {
	BORDER = 1,
	FILL = 2,
	DOTTED = 4,
	ELLIPSE = 8,
}RectStyle;
typedef enum {
	TS_LEFT = 0,
	TS_CENTER = 2,
	TS_RIGHT = 6,
	TS_TOP = 0,
	TS_BOTTOM = 8,
	TS_MIDDLE = 24,
}TextStyle;

class GUIBase {
public:
	GUIBase() :GUID(0x12345678) {}
	virtual void Print() = 0;
	void Refresh() {
		app.Show(this);
	}
public:
	DWORD GUID;
};

class Point{
public:
	Point() :x(0), y(0) {}
	Point(WORD sx, WORD sy) {
		x = sx;
		y = sy;
	}
public:
	WORD x,y;
};
class Rect {
public:
	Rect() :l(0), t(0), w(0), h(0) {}
	Rect(WORD left, WORD top, WORD width, WORD height) {
		l = left;
		t = top;
		w = width;
		h = height;
	}
public:
	WORD l, t, w, h;
};
class Line :public GUIBase {
public:
	virtual void Print();
	Line() {
		pt1.x = 0;
		pt1.y = 0;
		pt2.x = 1;
		pt2.y = 1;
		lw = 1;
		ls = SOLID;
		color = 0x000000;
	}
	Line(WORD x1, WORD y1, WORD x2, WORD y2) {
		pt1.x = x1;
		pt1.y = y1;
		pt2.x = x2;
		pt2.y = y2;
		lw = 1;
		ls = SOLID;
		color = 0x000000;
	}
	float GetLength();
	void Set_pt1(WORD x, WORD y);
	void Set_pt2(WORD x, WORD y);
	void Set_lw(BYTE w);
	void Set_ls(BYTE s);
	void Set_color(COLORREF c);
private:
	Point pt1, pt2;
	COLORREF color;
	BYTE lw;
	BYTE ls;
};
class Shape :public GUIBase {
public:
	Shape() {
		rect.l = 0;
		rect.t = 0;
		rect.w = 70;
		rect.h = 30;
		bColor = 0x000000;
		fColor = 0xffffff;
		lw = 1;
		rs = BORDER | FILL;
	}
	Shape(WORD left, WORD top, WORD width, WORD height) {
		rect.l = left;
		rect.t = top;
		rect.w = width;
		rect.h = height;
		bColor = 0x000000;
		fColor = 0xffffff;
		lw = 1;
		rs = BORDER | FILL;
	}
	virtual void Print();
	WORD GetWidth();
	WORD GetHigh();
	void Set_location(WORD left, WORD top);
	void Set_size(WORD width, WORD height);
	void Set_lw(BYTE w);
	void Set_rs(BYTE s);
	void Set_bColor(COLORREF bc);
	void Set_fColor(COLORREF fc);
private:
	Rect rect;
	COLORREF bColor, fColor;
	BYTE lw;
	BYTE rs;
};
class Text :public GUIBase {
public:
	Text() {
		pt.x = 0;
		pt.y = 0;
		str = "test";
		len = 4;
		ts = TS_LEFT | TS_TOP;
		color = 0x000000;
	}
	Text(WORD l, WORD t) {
		pt.x = l;
		pt.y = t;
		str = "test";
		len = 4;
		ts = TS_LEFT | TS_TOP;
		color = 0x000000;
	}
	BYTE GetLength() { return len; }
	virtual void Print();
	void Set_pt(WORD x, WORD y);
	void Set_str(const char* p);
	void Set_color(COLORREF c);
	void Set_ts(DWORD s);
private:
	Point pt;
	const char* str;
	COLORREF color;
	BYTE len;
	BYTE ts;
};
class Button :public GUIBase{
public:
	Button() {
		multiline = 0;
	}
	virtual void Print();
public:
	Shape border;
	Text text;
	BYTE multiline;
};
