#include "..\common\stdafx.h"
#include "gui.h"
#include <math.h>

static RECT tmp;
static HPEN pen;
static HBRUSH brush;

void Line::Print()
{
	pen = CreatePen(ls, lw, color);
	app.pen = (HPEN)SelectObject(app.hdc, pen);
	MoveToEx(app.hdc, pt1.x, pt1.y, NULL);
	LineTo(app.hdc, pt2.x, pt2.y);
	SelectObject(app.hdc, app.pen);
}
float Line::GetLength()
{
	return sqrtf(pow((pt2.x - pt1.x), 2.0) + pow((pt2.y - pt1.y), 2.0));
}
void Line::Set_pt1(WORD x, WORD y) {
	pt1.x = x;
	pt1.y = y;
}
void Line::Set_pt2(WORD x, WORD y) {
	pt2.x = x;
	pt2.y = y;
}
void Line::Set_lw(BYTE w)
{
	lw = w;
}
void Line::Set_ls(BYTE s)
{
	ls = s;
}
void Line::Set_color(COLORREF c)
{
	color = c;
}

void Shape::Print()
{
	COLORREF tmp;
	if (rs & BORDER)
		tmp = bColor;
	else
		tmp = 0xffffff;
	pen = CreatePen(rs & DOTTED, lw, tmp);
	if (rs & FILL)
		tmp = fColor;
	else
		tmp = 0xffffff;
	brush = CreateSolidBrush(tmp);
	app.pen = (HPEN)SelectObject(app.hdc, pen);
	app.brush = (HBRUSH)SelectObject(app.hdc, brush);
	if (rs & ELLIPSE)
		Ellipse(app.hdc, rect.l, rect.t, rect.l + rect.w, rect.t + rect.h);
	else
		Rectangle(app.hdc, rect.l, rect.t, rect.l + rect.w, rect.t + rect.h);
	SelectObject(app.hdc, app.pen);
	SelectObject(app.hdc, app.brush);
}
WORD Shape::GetWidth()
{
	return rect.w;
}
WORD Shape::GetHigh()
{
	return rect.h;
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
void Shape::Set_lw(BYTE w)
{
	lw = w;
}
void Shape::Set_rs(BYTE s)
{
	rs = s;
}
void Shape::Set_bColor(COLORREF bc)
{
	bColor = bc;
}
void Shape::Set_fColor(COLORREF fc)
{
	fColor = fc;
}

void Text::Print()
{
	UINT old_align = SetTextAlign(app.hdc, ts & 0x1f);
	COLORREF old_color = SetTextColor(app.hdc, color);
	SelectObject(app.hdc, app.font);
	TextOut(app.hdc, pt.x, pt.y, str, strlen(str));
	SetTextAlign(app.hdc, old_align);
	SetTextColor(app.hdc, old_color);
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
void Text::Set_color(COLORREF c)
{
	color = c;
}
void Text::Set_ts(DWORD s)
{
	ts = s;
}

void Button::Print()
{
	border.Refresh();
	text.Refresh();
}
