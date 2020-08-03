#pragma once
#include "core.h"

typedef enum {
	SHAPE_RECTANGLE,
	SHAPE_ELLIPSE,
}SHAPE_TYPE;
typedef enum {
	COLOR_WHITE = 0xffffff,
	COLOR_BLACK = 0x000000,
	COLOR_GRAY  = 0xc8c8c8,
	COLOR_RED   = 0x0000ff,
}DEFAULT_COLOR;

class PenProp {
public:
	PenProp() :style(0), width(1), color(COLOR_BLACK) {}
	void SetPenProp(BYTE s, BYTE w, COLORREF c);
protected:
	BYTE style, width;
	COLORREF color;
};
class BrushProp {
public:
	BrushProp() :color(COLOR_WHITE) {}
	void SetBrushProp(COLORREF c);
protected:
	COLORREF color;
};
class TextProp {
public:
	TextProp() :style(0), BigFont(true), color(COLOR_BLACK) {}
	void SetTextProp(BYTE s,bool size, COLORREF c);
protected:
	BYTE style;
	bool BigFont;
	COLORREF color;
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
class Line : public PenProp {
public:
	void Print();
	Line();
	Line(WORD x1, WORD y1, WORD x2, WORD y2);
	Line(WORD x1, WORD y1, float angle, float len);
	void SetParam(WORD x1, WORD y1, WORD x2, WORD y2);
	void SetParam(WORD x1, WORD y1, float angle, float len);
	float Get_len() { return len; }
	float Get_angle() { return angle; }
	Point& Get_pt1() { return pt1; }
	Point& Get_pt2() { return pt2; }
private:
	void Init();
	Point pt1, pt2;
	float angle, len;
};
class Curve {
public:
	Curve();
	Curve(WORD x1, WORD y1, WORD x2, WORD y2, bool dir, float angle);
	Curve(WORD x1, WORD y1, WORD x2, WORD y2, float rad, bool dir);
	void Print();
	void SetParam(WORD x1, WORD y1, WORD x2, WORD y2, bool dir, float angle);
	void SetParam(WORD x1, WORD y1, WORD x2, WORD y2, float rad, bool dir);
private:
	void Init();
	void GetRadius();
	void GetOrg();
	void GetLine();
	void GetAngle();
	static float s1_angle, s2_angle, s3_length;
	static bool s4_dir;
	float angle, radius;
	Point pt1, pt2, org;
};
class Shape :public PenProp, public BrushProp {
public:
	Shape() {
		rect.l = 0;
		rect.t = 0;
		rect.w = 70;
		rect.h = 30;
		shape = SHAPE_RECTANGLE;
	}
	Shape(WORD left, WORD top, WORD width, WORD height) {
		rect.l = left;
		rect.t = top;
		rect.w = width;
		rect.h = height;
		shape = SHAPE_RECTANGLE;
	}
	void Print();
	WORD GetWidth();
	WORD GetHigh();
	Point GetCrossPoint(Line line);
	void Set_location(WORD left, WORD top);
	void Set_size(WORD width, WORD height);
	void Set_shape(SHAPE_TYPE s);
private:
	Rect rect;
	SHAPE_TYPE shape;
};
class Text :public TextProp {
public:
	void Print();
	Text() {
		pt.x = 0;
		pt.y = 0;
		str = "test";
		len = 4;
	}
	Text(WORD l, WORD t) {
		pt.x = l;
		pt.y = t;
		str = "test";
		len = 4;
	}
	BYTE GetLength() { return len; }
	void Set_pt(WORD x, WORD y);
	void Set_str(const char* p);
private:
	Point pt;
	const char* str;
	BYTE len;
};
class Button {
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
class Arrow {
public:
	Arrow();
	Arrow(WORD x1, WORD y1, WORD x2, WORD y2, bool mode);
	void Print();
	void SetParam(WORD x1, WORD y1, WORD x2, WORD y2, bool mode);
private:
	void Init();
	Point pt1, pt2;
	bool type;
};
