#include "InputManager.h"
#include "Access/ProcessAccess.h"

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
	ProcessAccess& pa = ProcessAccess::GetInstance();
	
	//this way of sending inputs one by one via sendinput is not ideal for the way sendinput works.
	vector<INPUT> arrOutInput;
	for (InputStruct i : inM.inputsVector)
	{
		//why not switch? because of the variables of the async call. this would generate a compiler error.
		if (i.keyevent == PM_KeyUp || i.keyevent == PM_KeyDown)
		{
			std::future<BOOL> a = std::async(SendInputMessageToApp, pa.GetGameWindowHandle(), i.keyevent, i.key);
			a.get();
		}
		else if (i.keyevent == SI_KeyUp || i.keyevent == SI_KeyDown) //is not Post Message, is Send Input
		{
			arrOutInput.push_back(i.siInput);
		}
		else if (i.keyevent == PM_MoveMouse) // if the user wants to try it they can, but majority of application will do nothing with this message.
		{
			std::future<BOOL> a = std::async(SendMouseMoveMessageToApp, pa.GetGameWindowHandle(), i.keyevent, i.dirX, i.dirY);
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

		int erroRet = SendInput(sizeof(arrOutInput), arrOutInput.data(), sizeof(INPUT));
		if (erroRet == 0) {
			cout << ">> ERROR SENDING Move Mouse INPUT via SI: " << GetLastError() << endl;
		}
	}
	arrOutInput.clear();
	inM.inputsVector.clear();
}

// =-=-=-=-=-=-=-=--=-=-=--=-=--== HELPERS =-=-=-=-=-=-=-=-=-=-=--=

static string ToLower(std::string in)
{
	string outResult;
	for (int i = 0; i < in.size(); i++)
		outResult += tolower(in[i]);
	return outResult;
}

InputManager::KeyEvents InputManager::ConvertToKeyEventHelper(std::string in)
{
	string keyEventString = ToLower(in);
	InputManager::KeyEvents kEvent;
	if (keyEventString == "pm_keydown") { kEvent = InputManager::KeyEvents::PM_KeyDown; }
	else if (keyEventString == "pm_keyup") { kEvent = InputManager::KeyEvents::PM_KeyUp; }
	else if (keyEventString == "si_keydown") { kEvent = InputManager::KeyEvents::SI_KeyDown; }
	else if (keyEventString == "si_keyup") { kEvent = InputManager::KeyEvents::SI_KeyUp; }
	else if (keyEventString == "pm_movemouse") { kEvent = InputManager::KeyEvents::PM_MoveMouse; }
	else if (keyEventString == "si_movemouse") { kEvent = InputManager::KeyEvents::SI_MoveMouse; }
	else {
		printf(">> ERROR: invalid string while trying to convert parameter as KeyEvent in ConvertToKeyEventHelper: %s", in);
		//TODO: Better way to show errors to the user
		return InputManager::KeyEvents::err;
	}

	return kEvent;
}

InputManager::SpecialKeyboardInputs InputManager::ConvertToSpecialKeyboardKeyHelper(std::string in)
{
	string keyEventString = ToLower(in);
	InputManager::SpecialKeyboardInputs kEvent;

	if (keyEventString == "backspace") { kEvent = InputManager::SpecialKeyboardInputs::Backspace; }
	else if (keyEventString == "leftctrl") { kEvent = InputManager::SpecialKeyboardInputs::LeftCtrl; }
	else if (keyEventString == "leftshift") { kEvent = InputManager::SpecialKeyboardInputs::LeftShift; }
	else if (keyEventString == "rightctrl") { kEvent = InputManager::SpecialKeyboardInputs::RightCtrl; }
	else if (keyEventString == "rightshift") { kEvent = InputManager::SpecialKeyboardInputs::RightShift; }
	else if (keyEventString == "space") { kEvent = InputManager::SpecialKeyboardInputs::Space; }
	else if (keyEventString == "esc") { kEvent = InputManager::SpecialKeyboardInputs::Esc; }
	else if (keyEventString == "enter") { kEvent = InputManager::SpecialKeyboardInputs::Enter; }
	else {
		printf(">> ERROR: invalid string while trying to convert parameter as SpecialKey in ConvertToSpecialKeyboardKeyHelper %s", in);
		//TODO: Better way to show errors to the user
		return InputManager::SpecialKeyboardInputs::errSK;
	}

	return kEvent;
}

InputManager::MouseInputs InputManager::ConvertToMouseClick(std::string in)
{
	string kEventString = ToLower(in);
	InputManager::MouseInputs outMI;
	if (kEventString == "right") { outMI= InputManager::MouseInputs::RightClick; }
	else if (kEventString == "left") { outMI = InputManager::MouseInputs::LeftRight; }
	else if (kEventString == "middle") { outMI = InputManager::MouseInputs::MiddleClick; }
	else
	{
		printf(">> ERROR: invalid string while trying to convert parameter as SpecialKey in ConvertToMouseClick %s", in);
		//TODO: Better way to show errors to the user
		outMI = InputManager::MouseInputs::errM;
	}

	return outMI;
}
