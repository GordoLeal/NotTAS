#include <iostream>
#include <Windows.h>
#include "FuncInterpreter.h"
#include "ScriptManager.h"
#include "MainWindow.h"

using namespace std;

int main() {
	
	ScriptManager& sMan = ScriptManager::GetInstance();
	// Load names + functions into the ScriptManager
	sMan.AddScriptFunction("keyboard", FuncInterpreter::AddKeyboardInput);
	sMan.AddScriptFunction("mouse",FuncInterpreter::AddMouseInput);
	sMan.AddScriptFunction("movemouse",FuncInterpreter::AddMouseMoveInput);

	bool KeepLooping = true;
	MainWindow* mWindow = new MainWindow(); //Maybe we can make MainWindow a singleton since we only need one.
	
	while (KeepLooping) {
		if (mWindow->IsApplicationCloseRequest()) {
			KeepLooping = false;
		}
	}

	delete mWindow;

	return 0;
}
