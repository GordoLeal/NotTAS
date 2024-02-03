#include <iostream>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

#ifndef WINAPI_H
#define WINAPI_H


class WindowsAPI
{
public:
	enum KeyEvents
	{
		keydown = 0x0000,
		keyup = KEYEVENTF_KEYUP
	};

	void AddKeyboardInput(WORD key, KeyEvents event);
	void SendSavedInputs();
	bool SetGameHandle(const wchar_t gameName[], LPCSTR gameWindowName);
	static int FindProcbyName(const wchar_t* name);
private:
	HANDLE gameHwnd;
	HWND gameWindowHandle;
	std::vector<INPUT> inputVector;
};
#endif 

