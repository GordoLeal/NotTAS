#include <iostream>
#include "InputManager.h"
#include "MainLogic.h"
#include "FuncInterpreter.h"
#include "MemoryAccess.h"
#include "ProcessAccess.h"

using namespace std;

/// <summary>
/// script call: keyboard(key, keyevent)
/// </summary>
/// <param name="args"></param>
void FuncInterpreter::AddKeyboardInput(std::vector<std::string> args)
{
	InputManager& inM = InputManager::GetInstance();
	if (args[0].size() > 1) {
		//Is probably a special key
		InputManager::SpecialKeyboardInputs sKeyIn = InputManager::ConvertToSpecialKeyboardKeyHelper(args[0]);
		InputManager::KeyEvents kEvent = InputManager::ConvertToKeyEventHelper(args[1]);
		inM.AddSpecialKeyboardInput(sKeyIn, kEvent);
	}
	else
	{
		//its probably only a single key

		InputManager::KeyEvents kEvent = InputManager::ConvertToKeyEventHelper(args[1]);
		inM.AddKeyboardInput(args[0][0], kEvent);
	}

}

/// <summary>
/// script call: mouse(key,keyevent)
/// </summary>
/// <param name="args"></param>
void FuncInterpreter::AddMouseInput(std::vector<std::string> args)
{
	InputManager& inM = InputManager::GetInstance();
	InputManager::MouseInputs mIn = InputManager::ConvertToMouseClick(args[0]);
	InputManager::KeyEvents kEvent = InputManager::ConvertToKeyEventHelper(args[1]);
	inM.AddMouseInput(mIn, kEvent);
}
/// <summary>
/// script call: movemouse(x,y)
/// </summary>
/// <param name="args"></param>
void FuncInterpreter::AddMouseMoveInput(std::vector<std::string> args)
{
	int x;
	int y;
	try {
		x = stoi(args[0]);
		y = stoi(args[1]);
	}
	catch (out_of_range const& ex) {
		//TODO: Better way to show errors
		cout << ">> ERROR: value for move mouse is way too big" << endl;
		return;
	}
	catch (invalid_argument const& ex) {
		//TODO: Better way to show errors
		cout << ">> ERROR: value for move mouse is not a number" << endl;
		return;
	}

	//Post Message on move mouse does nothing, unless i am missing something, but for now gonna only use move mouse.
	InputManager::AddMouseMoveInput(x, y, InputManager::KeyEvents::SI_MoveMouse);
}

void FuncInterpreter::AddGameInFocus(std::vector<std::string> args)
{
	ProcessAccess& inm = ProcessAccess::GetInstance();
	inm.FocusOnGameWindow();
}

void FuncInterpreter::SetGameFPS(std::vector<std::string> args)
{
	printf("getting fpsStartAddress from offsets \n");
	ProcessAccess& pa = ProcessAccess::GetInstance();
	//TODO: Read this value from another place, a file or settings
	intptr_t fpsStartAddress = 0x03414EA0;
	intptr_t gameModuleAddress = pa.GetGameBaseMemoryAddress();
	//TODO: Read this value from another place, a file or settings
	std::vector<DWORD> offsets{0x10,0x378};
	intptr_t fpsAddress = MemoryAccess::GetAddressFromOffsets(pa.GetGameHwnd(), gameModuleAddress + fpsStartAddress, offsets);
	MemoryAccess::WriteFloatToAdress(pa.GetGameHwnd(), fpsAddress, stof(args[0]));

}

void FuncInterpreter::StopTAS(std::vector<std::string> args) {
	MainLogic& ml = MainLogic::GetInstance();
	ml.StopExecution();
}


