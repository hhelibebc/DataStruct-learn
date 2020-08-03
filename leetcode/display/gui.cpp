#include "..\common\stdafx.h"
#include "gui.h"
#include <math.h>

static RECT tmp;
static HPEN pen;
static HBRUSH brush;
static Line line;
static PAINTSTRUCT ps;

void Line::Print()
{
	BeginPaint(app.wnd.hwnd, &ps);
	pen = CreatePen(style, width, color);
	app.pen = (HPEN)SelectObject(app.hdc, pen);
	MoveToEx(app.hdc, pt1.x, pt1.y, NULL);
	LineTo(app.hdc, pt2.x, pt2.y);
	SelectObject(app.hdc, app.pen);
	EndPaint(app.wnd.hwnd, &ps);
}
Line::Line()
{
	Init();
}
Line::Line(WORD x1, WORD y1, WORD x2, WORD y2)
{
	Init();
	SetParam(x1, y1, x2, y2);
}
Line::Line(WORD x1, WORD y1, float angle, float len)
{
	Init();
	SetParam(x1, y1, angle, len);
}
void Line::SetParam(WORD x1, WORD y1, WORD x2, WORD y2)
{
	int dx = x2 - x1, dy = y2 - y1;
	pt1.x = x1;
	pt1.y = y1;
	pt2.x = x2;
	pt2.y = y2;
	len = sqrtf(pow(dx, 2) + pow(dy, 2));
	angle = atanf(fabs((double)dy / dx)) * 180 / PI;
	if (dx >= 0 && dy >= 0)
		;
	else if (dx < 0 && dy >= 0)
		angle = 180 - angle;
	else if (dx < 0 && dy < 0)
		angle = angle - 180;
	else if (dx >= 0 && dy < 0)
		angle = -angle;
}
void Line::SetParam(WORD x1, WORD y1, float angle, float len)
{
	pt1.x = x1;
	pt1.y = y1;
	this->angle = angle;
	this->len = len;
	pt2.x = pt1.x + len * cosf(angle * PI / 180);
	pt2.y = pt1.y + len * sinf(angle * PI / 180);
}
void Line::Init()
{
	CLEAROBJ(*this);
	width = 1;
}

void Shape::Print()
{
	BeginPaint(app.wnd.hwnd, &ps);
	pen = CreatePen(PenProp::style, PenProp::width, PenProp::color);
	brush = CreateSolidBrush(BrushProp::color);
	app.pen = (HPEN)SelectObject(app.hdc, pen);
	app.brush = (HBRUSH)SelectObject(app.hdc, brush);
	if (shape == SHAPE_ELLIPSE)
		Ellipse(app.hdc, rect.l, rect.t, rect.l + rect.w, rect.t + rect.h);
	else
		Rectangle(app.hdc, rect.l, rect.t, rect.l + rect.w, rect.t + rect.h);
	SelectObject(app.hdc, app.pen);
	SelectObject(app.hdc, app.brush);
	EndPaint(app.wnd.hwnd, &ps);
}
WORD Shape::GetWidth()
{
	return rect.w;
}
WORD Shape::GetHigh()
{
	return rect.h;
}
Point Shape::GetCrossPoint(Line line)
{
	float a, b, c, d, e, f, a1, b1, c1, d1;
	Point pt1 = line.Get_pt1();
	Point pt2 = line.Get_pt2();
	c = rect.w / 2;
	e = rect.h / 2;
	d = rect.l + c;
	f = rect.t + e;
	if (pt2.x == pt1.x) {
		if (shape == SHAPE_ELLIPSE) {
			b1 = e * sqrt(1 - pow((pt1.x - d) / c, 2));
			a1 = f + b1;
			if (INRANGE(a1, pt1.y, pt2.y))
				pt1.y = a1;
			else
				pt1.y = a1 - 2 * b1;
		}
		else {
			if (INRANGE(rect.t, pt1.y, pt2.y))
				pt1.y = rect.t;
			else
				pt1.y = f + e;
		}
	}
	else if (pt2.y == pt1.y) {
		if (shape == SHAPE_ELLIPSE) {
			b1 = c * sqrt(1 - pow((pt1.y - f) / e, 2));
			a1 = d + b1;
			if (INRANGE(a1, pt1.x, pt2.x))
				pt1.x = a1;
			else
				pt1.x = a1 - 2 * b1;
		}
		else {
			if (INRANGE(rect.l, pt1.x, pt2.x))
				pt1.x = rect.l;
			else
				pt1.x = d + c;
		}
	}
	else {
		a = (float)(pt2.y - pt1.y) / (pt2.x - pt1.x);
		b = pt1.y - pt1.x * a;
		if (shape == SHAPE_ELLIPSE) {
			if (FLOAT_EQUAL(f, a * d + b)) {
				a1 = line.Get_angle();
				b1 = c * cos(a1 * PI / 180);
				c1 = e * sin(a1 * PI / 180);
				d1 = d + b1;
				if (INRANGE(d1, pt1.x, pt2.x)) {
					pt1.x = d1;
					pt1.y = f + c1;
				}
				else {
					pt1.x = d - b1;
					pt1.y = f - c1;
				}
			}
			else {
				d1 = b - f;
				f = pow(e, 2);
				a1 = pow(a * c, 2) + f;
				b1 = 2 * a * d1 * pow(c, 2) - 2 * d * f;
				c1 = pow(c * d1, 2) + (d + c) * (d - c) * f;
				c = sqrt(b1 * b1 - 4 * a1 * c1);
				d = (-b1 + c) / (2 * a1);
				if (INRANGE(d, pt1.x, pt2.x))
					pt1.x = d;
				else
					pt1.x = d - c / a1;
				pt1.y = a * pt1.x + b;
			}
		}
		else {
			a1 = d + c;
			b1 = f + e;
			if (INRANGE(rect.l, pt1.x, pt2.x)) {
				pt1.x = rect.l;
				pt1.y = a * rect.l + b;
			}
			else if (INRANGE(a1, pt1.x, pt2.x)) {
				pt1.x = a1;
				pt1.y = a * a1 + b;
			}
			if (INRANGE(rect.t, pt1.y, pt2.y)) {
				pt1.x = (rect.t - b) / a;
				pt1.y = rect.t;
			}
			else if (INRANGE(b1, pt1.y, pt2.y)) {
				pt1.x = (b1 - b) / a;
				pt1.y = b1;
			}
		}
	}
	return pt1;
}
void Shape::Set_location(WORD left, WORD top)
{
	rect.l = left;
	rect.t = top;
}
void Shape::Set_size(WORD width, WORD height)
{
	rect.w = width;
	rect.h = height;
}
void Shape::Set_shape(SHAPE_TYPE s)
{
	shape = s;
}

void Text::Print()
{
	BeginPaint(app.wnd.hwnd, &ps);
	UINT old_align = SetTextAlign(app.hdc, style & 0x1f);
	COLORREF old_color = SetTextColor(app.hdc, color);
	int old = SetBkMode(app.hdc, TRANSPARENT);
	if(BigFont)
		SelectObject(app.hdc, app.font1);
	else
		SelectObject(app.hdc, app.font2);
	TextOut(app.hdc, pt.x, pt.y, str, strlen(str));
	SetTextAlign(app.hdc, old_align);
	SetTextColor(app.hdc, old_color);
	SetBkMode(app.hdc, old);
	EndPaint(app.wnd.hwnd, &ps);
}
void Text::Set_pt(WORD x, WORD y)
{
	pt.x = x;
	pt.y = y;
}
void Text::Set_str(const char* p)
{
	str = p;
	len = strlen(str);
}

void Button::Print()
{
	border.Print();
	text.Print();
}

float Curve::s1_angle = 0;
float Curve::s2_angle = 0;
float Curve::s3_length = 0;
bool Curve::s4_dir = true;
void Curve::Print()
{
	pen = CreatePen(0, 1, COLOR_BLACK);
	app.pen = (HPEN)SelectObject(app.hdc, pen);
	if (s4_dir) {
		Arc(app.hdc, org.x - radius, org.y - radius,
			org.x + radius, org.y + radius,
			pt1.x, pt1.y, pt2.x, pt2.y);
	}
	else {
		Arc(app.hdc, org.x - radius, org.y - radius,
			org.x + radius, org.y + radius,
			pt2.x, pt2.y, pt1.x, pt1.y);
	}
	SelectObject(app.hdc, app.pen);
}
Curve::Curve()
{
	Init();
}
Curve::Curve(WORD x1, WORD y1, WORD x2, WORD y2, bool dir, float angle)
{
	Init();
	SetParam(x1, y1, x2, y2, dir, angle);
}
Curve::Curve(WORD x1, WORD y1, WORD x2, WORD y2, float rad, bool dir)
{
	Init();
	SetParam(x1, y1, x2, y2, rad, dir);
}
void Curve::SetParam(WORD x1, WORD y1, WORD x2, WORD y2, bool dir, float angle)
{
	pt1.x = x1;
	pt1.y = y1;
	pt2.x = x2;
	pt2.y = y2;
	s4_dir = dir;
	this->angle = angle;
	GetLine();
	GetRadius();
	GetOrg();
}
void Curve::SetParam(WORD x1, WORD y1, WORD x2, WORD y2, float rad, bool dir)
{
	pt1.x = x1;
	pt1.y = y1;
	pt2.x = x2;
	pt2.y = y2;
	s4_dir = dir;
	radius = rad;
	GetLine();
	GetAngle();
	GetOrg();
}
void Curve::Init()
{
	CLEAROBJ(*this);
}
void Curve::GetRadius()
{
	radius = (s3_length / 2) / sinf(angle * PI / 360);
}
void Curve::GetOrg()
{
	s2_angle = 90 - angle / 2;
	if (s4_dir)
		s2_angle = s2_angle - s1_angle;
	else
		s2_angle = 0 - s1_angle - s2_angle;
	line.SetParam(pt1.x, pt1.y, s2_angle, radius);
	org = line.Get_pt2();
}
void Curve::GetLine()
{
	line.SetParam(pt1.x, pt1.y, pt2.x, pt2.y);
	s3_length = line.Get_len();
	s1_angle = line.Get_angle();
}
void Curve::GetAngle()
{
	angle = asinf(s3_length / (2 * radius)) * 360 / PI;
}

Arrow::Arrow()
{
	Init();
}
Arrow::Arrow(WORD x1, WORD y1, WORD x2, WORD y2, bool mode)
{
	Init();
	SetParam(x1, y1, x2, y2, mode);
}
void Arrow::Print()
{
	line.SetParam(pt1.x, pt1.y, pt2.x, pt2.y);
	float A1 = line.Get_angle() + 180;
	if (type) {
		line.SetParam(pt2.x, pt2.y, A1 - 15, 15);
		line.Print();
		line.SetParam(pt2.x, pt2.y, A1 + 15, 15);
		line.Print();
	}
	else {
		line.SetParam(pt1.x, pt1.y, A1 - 15, 15);
		line.Print();
		line.SetParam(pt1.x, pt1.y, A1 + 15, 15);
		line.Print();
	}
}
void Arrow::SetParam(WORD x1, WORD y1, WORD x2, WORD y2, bool mode)
{
	pt1.x = x1;
	pt1.y = y1;
	pt2.x = x2;
	pt2.y = y2;
	type = mode;
}
void Arrow::Init()
{
	CLEAROBJ(*this);
}

void PenProp::SetPenProp(BYTE s, BYTE w, COLORREF c)
{
	style = s;
	width = w;
	color = c;
}
void BrushProp::SetBrushProp(COLORREF c)
{
	color = c;
}
void TextProp::SetTextProp(BYTE s,bool size, COLORREF c)
{
	style = s;
	BigFont = size;
	color = c;
}
