#include "WindowsAPI.h"


//Add keyboard inputs to the list.
void WindowsAPI::AddKeyboardInput(WORD key,KeyEvents event)
{
	UINT keyCode = VkKeyScanExA(key,GetKeyboardLayout(1));
	INPUT a = {};
	a.type = INPUT_KEYBOARD;
	a.ki.wVk = keyCode;
	a.ki.dwFlags = event;
	inputVector.push_back(a);

	//UINT keyCode = VkKeyScanExA(key,GetKeyboardLayout(1));
	//INPUT inp[1] = {};
	//inp[0].type = INPUT_KEYBOARD;
	//inp[0].ki.wVk = keyCode;
	//inp[0].ki.dwFlags = event;
	
	//SendInput(1, inp, sizeof(inp));
	
}

//Send all the inputs from the vector list and empty it.
void WindowsAPI::SendSavedInputs()
{
	for (INPUT i : inputVector) {
		std::cout << "a: " << std::endl;
	}
	int err = SendInput(inputVector.size(), inputVector.data(), sizeof(INPUT));
	if (err == 0) {
		std::cout << "err: " << GetLastError() << std::endl;
	}

	inputVector.clear();
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	wchar_t x[255];
	int a = GetWindowTextW(hwnd, x, 255);
	if (a== 0) {
		MessageBoxW(NULL, L"TEU CU", L"CU", MB_OK);
		
	}
	if (wcscmp(x, L"Sponge")) {
		MessageBoxW(NULL, L"ACHO ESSA MERDA", L"CU", MB_OK);
		return false;
	}
	return true;
};

//Sets the game handle for the application that is gonna receive the inputs.
bool WindowsAPI::SetGameHandle(const wchar_t ExeName[], LPCSTR gameWindowName)
{
	int processID = FindProcbyName(ExeName);
	
	if (processID == 0) { // 0 = windows explorer.
		MessageBoxW(NULL, L"Process not found. is the application open?", L"", MB_OK);
		return false;
	}

	WindowsAPI::gameHwnd = OpenProcess(PROCESS_QUERY_INFORMATION | //get process handler
		PROCESS_VM_WRITE | // write into process memory
		PROCESS_VM_READ | // read into process memory
		PROCESS_VM_OPERATION, // change process memory size
		false,
		processID
	);

	EnumWindows(EnumWindowsProc,NULL);

	WindowsAPI::gameWindowHandle = FindWindowA(NULL, gameWindowName);
	if (gameWindowHandle == NULL) {
		MessageBoxW(NULL, L"Window handle not found. is the application open?", L"", MB_OK);
		return false;
	}
	return true;
}

//Find Process ID by Name
int WindowsAPI::FindProcbyName(const wchar_t* name) {
	PROCESSENTRY32 singleProcess; //hold process
	singleProcess.dwSize = sizeof(PROCESSENTRY32);
	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //get all the process currently open in the system
	if (GetLastError() == ERROR_ACCESS_DENIED) {
		MessageBoxW(nullptr, L"ERROR TRYING TO GET SNAPSHOT (ACCESS DENIED)", L"ERROR", MB_OK);
		//std::cout << "ERROR TRYING TO GET SNAPSHOT" << std::endl;
		return 1;
	}

	do {
		if (wcscmp(singleProcess.szExeFile, name) == 0) {
			printf("FOUND Exe: %S \n", singleProcess.szExeFile);
			DWORD processID = singleProcess.th32ProcessID; //get process ID
			CloseHandle(h);
			return processID;
		}

	} while (Process32NextW(h, &singleProcess));

	CloseHandle(h);
	return 0;
}
