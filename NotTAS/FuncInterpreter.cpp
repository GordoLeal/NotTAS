#include "FuncInterpreter.h"
#include "InputManager.h";
using namespace std;

void FuncInterpreter::AddKeyboardInput(char** args)
{
	InputManager& inM = InputManager::GetInstance();
	if (sizeof(args[0]) > 1) {
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

void FuncInterpreter::AddMouseInput(char** args)
{
	InputManager& inM = InputManager::GetInstance();
	InputManager::MouseInputs mIn = InputManager::ConvertToMouseClick(args[0]);
	InputManager::KeyEvents kEvent = InputManager::ConvertToKeyEventHelper(args[1]);
	inM.AddMouseInput(mIn, kEvent);
}

void FuncInterpreter::AddMouseMoveInput(char** args)
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


