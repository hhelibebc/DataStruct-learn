#include "..\common\stdafx.h"
#include "core.h"
#include "gui.h"

MyApp app;
static char *Class = "DIY window";
static char *Title = "Ä§¸ÄµÄwin32³ÌÐò";
static MSG msg;
static MessageMap cb_tab[]={
	WM_PAINT,		OnPaint,
	WM_CREATE,		OnCreate,
	WM_SIZE,		OnSize,
	WM_LBUTTONDOWN,	OnLButtonDown,
};
#define CNT	(sizeof(cb_tab)/sizeof(cb_tab[0]))

void CallBack(OnPaint){
	PAINTSTRUCT ps;
	if (message == 0) {
		InvalidateRect(hWnd, &app.rect, 0);
		app.hdc = BeginPaint(hWnd,&ps);
		GUIBase* p = (GUIBase*)wParam;
		if (p != NULL && p->GUID == 0x12345678)
			p->Print();
		EndPaint(hWnd,&ps);
	}
	else if (message == 1) {
		InvalidateRect(hWnd, &app.rect, 1);
	}
}
void CallBack(OnCreate) {
	GetClientRect(hWnd, &app.rect);
	LOGFONT lfont;
	CLEAROBJ(&lfont);
	lfont.lfCharSet = GB2312_CHARSET;
	lfont.lfHeight = 25;
	app.font = CreateFontIndirect(&lfont);
	init();
}
void CallBack(OnSize) {
	GetClientRect(hWnd, &app.rect);
}
void CallBack(OnLButtonDown){
	test();
}
LRESULT CallBack(WndProc){
	char i;
	for(i=0;i<CNT;i++){
		if(message == cb_tab[i].msg){
			cb_tab[i].pf(hWnd,message,wParam,lParam);
			return 0;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
int MyWnd::Register(){
	WNDCLASSEX wcex;

	memset(&wcex,0,sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= app.inst;
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszClassName	= Class;

	return RegisterClassEx(&wcex);
}
int MyWnd::Create(){
	hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, Class, Title,WS_OVERLAPPEDWINDOW,
		400, 100, 1024, 768, NULL, NULL, app.inst, NULL);
	if(NULL == hwnd)
		return 0;
	::ShowWindow(hwnd,SW_SHOW);
	::UpdateWindow(hwnd);
	return 1;
}
int MyApp::Init(HINSTANCE hinst){
	inst = hinst;
	wnd.Register();
	return wnd.Create();
}
int MyApp::Run(){
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 1;
}
void MyApp::Show(void* ptr)
{
	OnPaint(wnd.hwnd, 0, (WPARAM)ptr, 0);
}
