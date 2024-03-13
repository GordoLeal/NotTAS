#include <Windows.h>
#include <iostream>
#include "MainWindow.h"
#include "MainLogic.h"

//  =-=-=-=-=-=-=-=-=-=-=-=-=-=-
//  =-=-=-=-=- DELETE =-=-=-=-=-
//  -=-=-=-=-=-=-=-=-=-=-=-=-=-=

//main window
constexpr int MW_Widght = 350;
constexpr int MW_Height = 200;
// cu button
constexpr int MW_Button = 1;
//playbutton
constexpr int PlayButton_ID = 2;

MainWindow::MainWindow() {
	//Create Main Window
	const wchar_t MAINWINDOW_CLASSNAME[] = L"NOT TAS";
	HINSTANCE hInstance = GetModuleHandleA(nullptr); //get instance of module

	WNDCLASS mwc = {};
	mwc.lpszClassName = MAINWINDOW_CLASSNAME;
	mwc.lpfnWndProc = MainWindowProc; //func that will receive all the messages
	mwc.hInstance = hInstance;

	RegisterClass(&mwc);

	DWORD style = WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	HWND hwnd = CreateWindowExW(
		0,                              // Optional window styles.
		MAINWINDOW_CLASSNAME,                     // Window class
		L"Not TAS",    // Window text
		style,            // Window style
		0, 0, MW_Widght, MW_Height, // Size and position
		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == 0) {
		std::cout << "shit hit the fan" << std::endl;
		return;
	}

	// == Create instances of what is inside the main window ==
	
	//Test button;
	HWND button_Play = CreateWindowExW(
		0,
		L"BUTTON",
		L"Play",
		WS_VISIBLE | WS_CHILD,
		10, 10, //position
		50, 25, //size
		hwnd,   // stick the to the hwnd
		(HMENU)PlayButton_ID,
		hInstance,
		NULL
	);

	//Test button;
	HWND button_Settings = CreateWindowExW(
		0,
		L"BUTTON",
		L"Play",
		WS_VISIBLE | WS_CHILD,
		10, 10, //position
		50, 25, //size
		hwnd,   // stick the to the hwnd
		(HMENU)PlayButton_ID,
		hInstance,
		NULL
	);

	//Test button;
	HWND button_Editor = CreateWindowExW(
		0,
		L"BUTTON",
		L"Play",
		WS_VISIBLE | WS_CHILD,
		10, 10, //position
		50, 25, //size
		hwnd,   // stick the to the hwnd
		(HMENU)PlayButton_ID,
		hInstance,
		NULL
	);

	//Test button;
	HWND bTest = CreateWindowExW(
		0,
		L"STATIC",
		L"CU",
		WS_VISIBLE | WS_CHILD,
		60, 10, //position
		25, 10, //size
		hwnd,   // stick the to the hwnd
		(HMENU)MW_Button,
		hInstance,
		NULL
	);

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
		//ml.InitialSetup();
		break;

	case WM_COMMAND:
		if (wParam == MW_Button)
		{
			//ml.ExecuteScript((char*)"teste.txt");
		}

		break;
	case WM_CLOSE:
		//TODO: correctly close everything and clear memory
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
