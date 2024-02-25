#include <iostream>
#include <Windows.h>
#ifndef PROCESSACCESS_H
#define PROCESSACCESS_H
class ProcessAccess
{
public:
	static ProcessAccess& GetInstance() {
		static ProcessAccess instance;
		return instance;
	}
	static int FindProcbyName(const wchar_t* name);
	static intptr_t GetBaseAddress(DWORD id, const wchar_t* name);
	static bool SetGameHandle(const wchar_t* gameName, char* gameWindowName);
	void FocusOnGameWindow();
	HANDLE GetGameHwnd();
	HWND GetGameWindowHandle();
	intptr_t GetGameBaseMemoryAddress();

private:
	ProcessAccess() {}
	~ProcessAccess();
	HANDLE gameHwnd = nullptr;
	HWND gameWindowHwnd = nullptr;
	intptr_t gameMainMemoryAddress = NULL;
};

#endif // !PROCESSACCESS_H

