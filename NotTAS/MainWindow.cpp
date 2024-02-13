#include <Windows.h>
#include <iostream>
#include "MainWindow.h"
#include "MainLogic.h"

#define MainWindow_Button 1

MainWindow::MainWindow() {

	// Get Main Monitor size

	//Create Main Window
	const wchar_t MAINWINDOW_CLASSNAME[] = L"NOTTAS";
	HINSTANCE hInstance = GetModuleHandleA(nullptr);

	WNDCLASS mwc = {};
	mwc.lpszClassName = MAINWINDOW_CLASSNAME;
	mwc.lpfnWndProc = MainWindowProc;
	mwc.hInstance = hInstance;

	RegisterClass(&mwc);

	DWORD style = WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	HWND hwnd = CreateWindowExW(
		0,                              // Optional window styles.
		MAINWINDOW_CLASSNAME,                     // Window class
		L"Not TAS",    // Window text
		style,            // Window style

		// Size and position
		0, 0, 800, 450,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == 0) {
		std::cout << "shit hit the fan" << std::endl;
		//TODO: better way of handling this error.
		return;
	}

	// Create instances of what is inside the main window
	HWND bTest = CreateWindowExW(
		0,
		L"BUTTON",
		L"CU",
		WS_VISIBLE | WS_CHILD,
		10, 10,
		80, 20,
		hwnd,
		(HMENU)MainWindow_Button,
		hInstance,
		NULL
	);

	std::cout << "all fine" << std::endl;
	ShowWindow(hwnd, 1);

}

bool MainWindow::IsApplicationCloseRequest()
{
	MSG msg = {};
	while (PeekMessageA(&msg, nullptr, NULL, NULL, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
		if (msg.message == WM_QUIT)
			return true;
	}
	return false;
}

LRESULT MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MainLogic& ml = MainLogic::GetInstance();
	switch (uMsg)
	{
	case WM_CREATE:
		ml.Setup();
		break;

	case WM_COMMAND:
		if (wParam == MainWindow_Button)
		{
			
			
			ml.ExecuteScript((char*)"teste.txt");


		}

		break;
	case WM_CLOSE:
		//TODO: correctly close everything and clear memory
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
