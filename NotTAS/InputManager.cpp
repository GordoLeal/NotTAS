#include <future>
#include <iostream>
#include "InputManager.h"

using namespace std;

// -=-=--=--=-=-=-=-=-=-=-=-=-=-=-== ADDING INPUTS TO THE LIST =-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=--=-=--=-=--=

// >>> KEYBOARD

//Add keyboard inputs to the list.
void InputManager::AddKeyboardInput(char key, KeyEvents inEvent)
{
	SHORT vkKeyScanResult = VkKeyScanExA(key, GetKeyboardLayout(0));

	BYTE KeyCode = static_cast<BYTE>(vkKeyScanResult & 0xFF);
	//BYTE shiftState = static_cast<BYTE>((vkKeyScanResult >> 8) & 0xFF);
	InputStruct outStruct;
	outStruct.hardware = Keyboard;
	outStruct.keyevent = inEvent;

	switch (inEvent)
	{
	case PM_KeyDown:
	case PM_KeyUp:
		outStruct.key = KeyCode;
		break;
	case SI_KeyUp:
	case SI_KeyDown:
		INPUT outInputArr = {};
		outInputArr.type = INPUT_KEYBOARD;
		outInputArr.ki.wVk = KeyCode;
		outInputArr.ki.dwFlags = inEvent;
		outInputArr.ki.dwExtraInfo = GetMessageExtraInfo(); //No idea what this does, but MSDN said it is required.
		outStruct.siInput = outInputArr;
		break;
	}
	InputManager& inM = InputManager::GetInstance();
	inM.inputsVector.push_back(outStruct);
}

void InputManager::AddSpecialKeyboardInput(SpecialKeyboardInputs key, KeyEvents inEvent)
{
	InputStruct outStruct;
	outStruct.hardware = Keyboard;
	outStruct.keyevent = inEvent;

	switch (inEvent)
	{
	case PM_KeyDown:
	case PM_KeyUp:
		outStruct.key = key;
		break;
	case SI_KeyUp:
	case SI_KeyDown:
		INPUT outInputArr = {};
		outInputArr.type = INPUT_KEYBOARD;
		outInputArr.ki.wVk = key;
		outInputArr.ki.dwFlags = inEvent;
		outInputArr.ki.dwExtraInfo = GetMessageExtraInfo(); //No idea what this does, but MSDN said it is required.
		outStruct.siInput = outInputArr;
		break;
	}
	InputManager& inM = InputManager::GetInstance();
	inM.inputsVector.push_back(outStruct);
}

// >>> MOUSE

//Add keyboard inputs to the list.
void InputManager::AddMouseInput(MouseInputs key, KeyEvents inEvent)
{
	InputStruct outStruct;
	outStruct.hardware = Mouse;
	outStruct.keyevent = inEvent;
	switch (inEvent)
	{
	case PM_KeyDown:
	case PM_KeyUp:
		outStruct.key = key;
		break;
	case SI_KeyUp:
	case SI_KeyDown:
		INPUT outInputArr = {};
		outInputArr.type = INPUT_MOUSE;
		switch (key)
		{
		case InputManager::RightClick:
			if (inEvent == SI_KeyDown) {

				outInputArr.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
			}
			else
			{
				outInputArr.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
			}
			break;
		case InputManager::LeftRight:
			if (inEvent == SI_KeyDown) {

				outInputArr.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			}
			else
			{
				outInputArr.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			}
			break;
		case InputManager::MiddleClick:
			if (inEvent == SI_KeyDown) {

				outInputArr.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
			}
			else
			{
				outInputArr.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
			}
			break;
		}
		outInputArr.mi.dwExtraInfo = GetMessageExtraInfo(); // No idea what this does, but MSDN said it is required.
		outStruct.siInput = outInputArr;
		break;
	}
	InputManager& inM = InputManager::GetInstance();
	inM.inputsVector.push_back(outStruct);
}

void InputManager::AddMouseMoveInput(int x, int y, InputManager::KeyEvents inEvent) {
	InputStruct outStruct;
	outStruct.hardware = Mouse;
	outStruct.keyevent = inEvent;
	switch (inEvent)
	{
	case PM_MoveMouse:
		outStruct.dirX = x;
		outStruct.dirY = y;
		break;
	case SI_MoveMouse:
		outStruct.siInput.type = INPUT_MOUSE;
		outStruct.siInput.mi.dx = (LONG)x;
		outStruct.siInput.mi.dy = (LONG)y;
		outStruct.siInput.mi.mouseData = 0;
		outStruct.siInput.mi.dwFlags = MOUSEEVENTF_MOVE;
		outStruct.siInput.mi.time = 0; //if is 0 the user system does the job of giving the correct time.
		outStruct.siInput.mi.dwExtraInfo = GetMessageExtraInfo(); //No idea what this does, but MSDN said it is required.
		break;
	}
	InputManager& inM = InputManager::GetInstance();
	inM.inputsVector.push_back(outStruct);
}

// -=-=--=-=-=--=-=-=-=--=-=-=-=-=-=-=-=-= SENDING INPUTS =-=-=--==-=-=-=--=-=-=-=-=-=-=-=--=-=-=-=--=-

/// <summary>
/// 
/// </summary>
/// <param name="handle"></param>
/// <param name="type"></param>
/// <param name="key"></param>
/// <returns></returns>
BOOL SendInputMessageToApp(HWND handle, UINT type, BYTE key) {
	//std::cout << "dentro do thread" << handle << " | type: " << type << "| key: " << key << std::endl;
	bool teste = PostMessageW(handle, type, key, 0);
	if (!teste) {
		DWORD errorMessageID = GetLastError();
		std::cout << ">> ERROR HAPPENED WHILE TRYING TO SEND INPUT. error ID: " << errorMessageID << std::endl;
	}
	return true;
}

BOOL SendMouseMoveMessageToApp(HWND handle, UINT type, int x, int y) {
	//std::cout << "dentro do thread" << handle << " | type: " << type << "| key: " << key << std::endl;
	bool teste = PostMessageW(handle, type, 0, MAKELPARAM(x, y));
	if (!teste) {
		DWORD errorMessageID = GetLastError();
		std::cout << ">> ERROR HAPPENED WHILE TRYING TO SEND MOVE MOUSE INPUT. error ID: " << errorMessageID << std::endl;
		return false;
	}
	return true;
}


//Send all the inputs from the vector list and empty it.
void InputManager::SendSavedInputs()
{
	InputManager& inM = InputManager::GetInstance();
	//this way of sending inputs one by one via sendinput is not ideal for the way sendinput works.
	vector<INPUT> arrOutInput;
	for (InputStruct i : inM.inputsVector)
	{
		//why not switch? because of the variables of the async call. this would generate a compiler error.
		if (i.keyevent == PM_KeyUp || i.keyevent == PM_KeyDown)
		{
			std::future<BOOL> a = std::async(SendInputMessageToApp, inM.gameWindowHwnd, i.keyevent, i.key);
			a.get();
		}
		else if (i.keyevent == SI_KeyUp || i.keyevent == SI_KeyDown) //is not Post Message, is Send Input
		{
			arrOutInput.push_back(i.siInput);
		}
		else if (i.keyevent == PM_MoveMouse) // if the user wants to try it they can, but majority of application will do nothing with this message.
		{
			std::future<BOOL> a = std::async(SendMouseMoveMessageToApp, inM.gameWindowHwnd, i.keyevent, i.dirX, i.dirY);
			a.get();
		}
		else if (i.keyevent == SI_MoveMouse)
		{
			arrOutInput.push_back(i.siInput);
		}
		else
		{
			cout << ">> ERROR: INPUT EVENT NOT VALID! " << i.keyevent << endl;
		}
	}
	if (arrOutInput.size() > 0) {

		cout << "SENDING.. " << arrOutInput.size() << endl;
		int erroRet = SendInput(sizeof(arrOutInput), arrOutInput.data(), sizeof(INPUT));
		if (erroRet == 0) {
			cout << ">> ERROR SENDING Move Mouse INPUT via SI: " << GetLastError() << endl;
		}
	}
	arrOutInput.clear();
	inM.inputsVector.clear();
}

// =-=-=-=-=-=-=-=-=-=-=--=-=--=-=-=--=-=-=-= GAME HANDLES =-=-=-=-=--=-=-=--=-=-=-=-=--=-=--=-=--=-=--=-=--=-=-

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
bool InputManager::SetGameHandle(const wchar_t ExeName[], char gameWindowName[])
{
	int processID = FindProcbyName(ExeName);
	InputManager& inM = InputManager::GetInstance();

	if (processID == 0) { // 0 = windows explorer.
		MessageBoxW(NULL, L"Process not found. is the application open?", L"", MB_OK);
		return false;
	}

	inM.gameHwnd = OpenProcess(
		PROCESS_QUERY_INFORMATION | //get process handler
		PROCESS_VM_READ, // read into process memory
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

	inM.gameWindowHwnd = sba.windowHandle;
	if (inM.gameWindowHwnd == NULL) {
		MessageBoxW(NULL, L"Window handle not found. is the application open?", L"", MB_OK);
		return false;
	}
	return true;
}

void InputManager::FocusOnGameWindow()
{
	InputManager& inM = InputManager::GetInstance();
	if (inM.gameWindowHwnd == NULL) {
		//TODO: better way to show this message to the user
		cout << ">> ERROR: trying to call gameWindowHwnd without setting it first. please call SetGameHandle First." << endl;
		return;
	}
	SetForegroundWindow(inM.gameWindowHwnd);
}

static string ToLower(char* in)
{
	string outResult;
	for (int i = 0; i < strlen(in); i++)
		outResult += tolower(in[i]);
	return outResult;
}

InputManager::KeyEvents InputManager::ConvertToKeyEventHelper(char* in)
{
	string keyEventString = ToLower(in);
	InputManager::KeyEvents kEvent;

	//Yanderer simulator dev, but it works and switch in c++ is just stupid to work with strings, so a bunch of if-else it is.
	if (keyEventString == "pm_keydown") { kEvent = InputManager::KeyEvents::PM_KeyDown; }
	else if (keyEventString == "pm_keyup") { kEvent = InputManager::KeyEvents::PM_KeyUp; }
	else if (keyEventString == "si_keydown") { kEvent = InputManager::KeyEvents::SI_KeyDown; }
	else if (keyEventString == "si_keyup") { kEvent = InputManager::KeyEvents::SI_KeyUp; }
	else if (keyEventString == "pm_movemouse") { kEvent = InputManager::KeyEvents::PM_MoveMouse; }
	else if (keyEventString == "si_movemouse") { kEvent = InputManager::KeyEvents::SI_MoveMouse; }
	else {
		cout << ">> ERROR: invalid string while trying to convert parameter as KeyEvent in ConvertToKeyEventHelper" << endl;
		//TODO: Better way to show errors to the user
		return;
	}

	return kEvent;
}

InputManager::SpecialKeyboardInputs InputManager::ConvertToSpecialKeyboardKeyHelper(char* in)
{
	string keyEventString = ToLower(in);
	InputManager::SpecialKeyboardInputs kEvent;

	if (keyEventString == "backspace") { kEvent = InputManager::SpecialKeyboardInputs::Backspace; }
	else if (keyEventString == "leftctrl") { kEvent = InputManager::SpecialKeyboardInputs::LeftCtrl; }
	else if (keyEventString == "leftshift") { kEvent = InputManager::SpecialKeyboardInputs::LeftShift; }
	else if (keyEventString == "rightctrl") { kEvent = InputManager::SpecialKeyboardInputs::RightCtrl; }
	else if (keyEventString == "rightshift") { kEvent = InputManager::SpecialKeyboardInputs::RightShift; }
	else if (keyEventString == "space") { kEvent = InputManager::SpecialKeyboardInputs::Space; }
	else {
		cout << ">> ERROR: invalid string while trying to convert parameter as SpecialKey in ConvertToSpecialKeyboardKeyHelper" << endl;
		//TODO: Better way to show errors to the user
		return;
	}

	return;
}

InputManager::MouseInputs InputManager::ConvertToMouseClick(char* in)
{
	string kEventString = ToLower(in);
	if (kEventString == "right") { kEventString = InputManager::MouseInputs::RightClick; }
	else if (kEventString == "left") { kEventString = InputManager::MouseInputs::LeftRight; }
	else if (kEventString == "middle") { kEventString = InputManager::MouseInputs::MiddleClick; }
	else
	{
		cout << ">> ERROR: invalid string while trying to convert parameter as SpecialKey in ConvertToSpecialKeyboardKeyHelper" << endl;
		//TODO: Better way to show errors to the user
	}

	return;
}



//Find Process ID by Name
int InputManager::FindProcbyName(const wchar_t* name) {
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
