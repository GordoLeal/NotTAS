#include <iostream>
#include "InputManager.h"
#include "FuncInterpreter.h"

using namespace std;

/// <summary>
/// script call: keyboard(key, keyevent)
/// </summary>
/// <param name="args"></param>
void FuncInterpreter::AddKeyboardInput(std::vector<std::string> args)
{
	std::cout << "[FuncInterpreter-log] Keyboard Input" << std::endl;
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
	std::cout << "[FuncInterpreter-log] Mouse Input" << std::endl;
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
	std::cout << "[FuncInterpreter-log] Move Mouse input" << std::endl;
	int x;
	int y;
	try {
		x = stoi(args[0]);
		y = stoi(args[1]);
	}
	catch (out_of_range const& ex) {
		cout << ">> [AddMouseMoveInput-ERROR]: value for move mouse is way too big" << endl;
		return;
	}
	catch (invalid_argument const& ex) {
		cout << ">> [AddMouseMoveInput-ERROR]: value for move mouse is not a number" << endl;
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

void FuncInterpreter::WaitLoadStart(std::vector<std::string> args)
{
	std::cout << "[FuncInterpreter-log] Wait Load Start" << std::endl;
	MainLogic::GetInstance().WaitingLoadingToStart = true;
}

void FuncInterpreter::WaitLoadEnd(std::vector<std::string> args)
{
	std::cout << "[FuncInterpreter-log] Wait load end" << std::endl;
	MainLogic::GetInstance().WaitingLoadingToEnd = true;
}

void FuncInterpreter::MoveCursor(std::vector<std::string> args)
{
	POINT currentPos;
	GetCursorPos(&currentPos); // Get current mouse position

	int x, y;
	try {
		x = stoi(args[0]);
		y = stoi(args[1]);
	}
	catch (out_of_range const& ex) {
		cout << ">> [MoveCursor-ERROR]: value for x or y is way too big." << endl;
		return;
	}
	catch (invalid_argument const& ex) {
		cout << ">> [MoveCursor-ERROR]: value for x or y is not a number." << endl;
		return;
	}

	// Calculate new position
	int newX = currentPos.x + x;
	int newY = currentPos.y + y;
	std::cout << "[FuncInterpreter-log] Setting Cursor Position at X:"<< newX << " Y:" << newY<< std::endl;
	// Set the new position
	SetCursorPos(newX, newY);
}

void FuncInterpreter::waitfor(std::vector<std::string> args)
{
	int x;
	try {
		x = stoul(args[0]);
	}
	catch (out_of_range const& ex) {
		cout << ">> [waitfor-ERROR]: value for x is way too big." << endl;
		return;
	}
	catch (invalid_argument const& ex) {
		cout << ">> [waitfor-ERROR]: value for x is not a number." << endl;
		return;
	}
	std::cout << "[FuncInterpreter-log] Waiting for " << x << "Milliseconds" << std::endl;
	Sleep(x);
}

void FuncInterpreter::SetGameFPS(std::vector<std::string> args)
{
	std::cout << "[FuncInterpreter-log] Set Game FPS" << std::endl;
	ProcessAccess& _pa = ProcessAccess::GetInstance();
	MainLogic& _ml = MainLogic::GetInstance();
	intptr_t gameModuleAddress = _pa.GetGameBaseMemoryAddress();
	intptr_t fpsAddress = MemoryAccess::GetAddressFromOffsets(_pa.GetGameHwnd(), gameModuleAddress + _ml.fpsAddress, _ml.fpsOffsets);
	MemoryAccess::WriteFloatToAdress(_pa.GetGameHwnd(), fpsAddress, stof(args[0]));

}

void FuncInterpreter::StopTAS(std::vector<std::string> args) {
	std::cout << "[FuncInterpreter-log] Stop TAS" << std::endl;
	MainLogic& ml = MainLogic::GetInstance();
	ml.StopExecution();
}