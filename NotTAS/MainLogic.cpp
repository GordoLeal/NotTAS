#include <string>
#include <vector>
#include "MainLogic.h"

void MainLogic::ExecuteScript(char* fileName)
{
	if (!keepLooping) {
		loopThread = std::thread(&MainLogic::ExecutionThread, this, fileName);
	}
	else
	{
		StopExecution();
	}
}

//Main Execution thread for reading the script and doing inputs
void MainLogic::ExecutionThread(char* filename) {
	keepLooping = true;
	_sm.LoadScript(filename);
	currentFrame = 0;
	while (keepLooping) {
		printf("current frame: %lu \n", currentFrame);
		ExecuteFrame(currentFrame);
		//TODO: divide by the game framerate.
		Sleep(60.0 / 60.0);
		currentFrame++;
	}

}

void MainLogic::ExecuteFrame(unsigned long frame)
{
	ScriptManager::FrameCall currentFrameCalls;
	if (_sm.GetFunctionsFromFrame(frame, &currentFrameCalls)) {
		for (ScriptManager::FrameFunction i : currentFrameCalls.calls) {
			std::cout << i.args.size() << " <<<args" << std::endl;
			//Convert vector string to char* array;
			if (_sm.FunctionExist(i.funcNameA))
				_sm.CallFunction(i.funcNameA, i.args);
		}
		_inm.SendSavedInputs();
	}
}

void MainLogic::StopExecution()
{
	printf("stopping thread");
	keepLooping = false;
	loopThread.detach();
}

void MainLogic::Setup()
{
	// Load names + functions into the ScriptManager
	_sm.AddScriptFunction("keyboard", FuncInterpreter::AddKeyboardInput);
	_sm.AddScriptFunction("mouse", FuncInterpreter::AddMouseInput);
	_sm.AddScriptFunction("movemouse", FuncInterpreter::AddMouseMoveInput);
	_sm.AddScriptFunction("showgame", FuncInterpreter::AddGameInFocus);
	_sm.AddScriptFunction("stop", FuncInterpreter::StopTAS);

	//TEMP
	_sm.LoadScript((char*)"teste.txt");

	_inm.SetGameHandle(L"Pineapple-Win64-Shipping.exe", (char*)"Sponge");
}
