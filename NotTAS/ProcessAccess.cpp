#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "ProcessAccess.h"


struct SendToWind
{
	HWND windowHandle;
	char* name;
};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	SendToWind& sa = *reinterpret_cast<SendToWind*>(lParam);
	char a[255] = {};
	GetWindowTextA(hwnd, a, 255);
	if (strstr(a, sa.name))
	{
		sa.windowHandle = hwnd;
		return false;
	}
	return true;
};

//Sets the game handle and window handle for the application that is gonna receive the inputs.
bool ProcessAccess::SetGameHandle(const wchar_t ExeName[], char gameWindowName[])
{
	int processID = FindProcbyName(ExeName);
	ProcessAccess& pa = ProcessAccess::GetInstance();

	if (processID == 0) { // 0 = windows explorer.
		MessageBoxW(NULL, L"Process not found. is the application open?", L"", MB_OK);
		return false;
	}

	pa.gameHwnd = OpenProcess(
		PROCESS_QUERY_INFORMATION | 
		PROCESS_VM_READ | // read into process memory
		PROCESS_VM_OPERATION |
		PROCESS_VM_WRITE, // Write into process memory
		false,
		processID
	);

	//i don't like this hack way of getting the handle of the game window, but it works...
	SendToWind sba;
	sba.name = gameWindowName;

	if (!EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&sba)))
	{
		//TODO: do something if can't find window
	};

	pa.gameWindowHwnd = sba.windowHandle;
	if (pa.gameWindowHwnd == NULL) {
		MessageBoxW(NULL, L"Window handle not found. is the application open?", L"", MB_OK);
		return false;
	}

	pa.gameMainMemoryAddress = ProcessAccess::GetBaseAddress(processID, ExeName);
	if (pa.gameMainMemoryAddress == 0x0) {
		MessageBoxW(NULL, L"Game Base Module not found. is the application open?", L"", MB_OK);
		return false;
	}
	return true;
}

void ProcessAccess::FocusOnGameWindow()
{
	ProcessAccess& pa = ProcessAccess::GetInstance();
	if (pa.gameWindowHwnd == NULL) {
		//TODO: better way to show this message to the user
		std::cout << ">> ERROR: trying to call gameWindowHwnd without setting it first. please call SetGameHandle First." << std::endl;
		return;
	}
	SetForegroundWindow(pa.gameWindowHwnd);
}

//Find Process ID by Name
int ProcessAccess::FindProcbyName(const wchar_t* name) {
	PROCESSENTRY32 singleProcess; //hold process
	singleProcess.dwSize = sizeof(PROCESSENTRY32);
	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //get all the process currently open in the system
	if (GetLastError() == ERROR_ACCESS_DENIED) {
		MessageBoxW(nullptr, L"ERROR TRYING TO GET SNAPSHOT (ACCESS DENIED)", L"ERROR", MB_OK);
		return 0;
	}

	do {
		if (wcscmp(singleProcess.szExeFile, name) == 0) {
			printf("FOUND Exe: %S \n", singleProcess.szExeFile);
			DWORD processID = singleProcess.th32ProcessID;
			CloseHandle(h);
			return processID;
		}

	} while (Process32NextW(h, &singleProcess));

	CloseHandle(h);
	return 0;
}

intptr_t ProcessAccess::GetBaseAddress(DWORD id, const wchar_t* name) {
	MODULEENTRY32W singlemodule;
	singlemodule.dwSize = sizeof(MODULEENTRY32W);
	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, id);
	if (GetLastError() == ERROR_ACCESS_DENIED) {
		MessageBoxW(nullptr, L"ERROR TRYING TO GET BASE MODULE (ACCESS DENIED)", L"ERROR", MB_OK);
		return 0x0;
	}
	intptr_t baseAddress = 0x0;
	do {
		if (wcscmp(singlemodule.szModule, name) == 0) {
			printf("FOUND module: %S \n", singlemodule.szModule);
			baseAddress = (intptr_t)singlemodule.modBaseAddr;
		}

	} while (Module32NextW(h, &singlemodule));

	CloseHandle(h);
	return baseAddress;
}

HANDLE ProcessAccess::GetGameHwnd()
{
	return gameHwnd;
}

HWND ProcessAccess::GetGameWindowHandle()
{
	return gameWindowHwnd;
}

intptr_t ProcessAccess::GetGameBaseMemoryAddress()
{
	return gameMainMemoryAddress;
}

ProcessAccess::~ProcessAccess()
{
	CloseHandle(gameHwnd);
	//CloseHandle(gameWindowHwnd);
}
