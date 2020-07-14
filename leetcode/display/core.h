#pragma once

#define UPDATE(p) OnPaint(hWnd,0,(WPARAM)p,0)

class MyWnd{
public:
	int Register();
	int Create();
public:
	HWND hwnd;
};

class MyApp{
public:
	int Init(HINSTANCE hInst);
	int Run();
	void Show(void* ptr);
public:
	MyWnd wnd;
	HINSTANCE inst;
	HDC hdc;
	HPEN	pen;
	HBRUSH	brush;
	HFONT   font;
	RECT rect;
};

typedef void (__stdcall *pCallBack)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#define CallBack(name) __stdcall name(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
typedef struct{
	int msg;
	pCallBack	pf;
}MessageMap;

extern MyApp app;
extern void CallBack(OnPaint);
extern void CallBack(OnCreate);
extern void CallBack(OnSize);
extern void CallBack(OnLButtonDown);
