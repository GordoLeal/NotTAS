#include <iostream>
#include <string>
#include <vector>
#include "MainLogic.h"
#include "FuncInterpreter.h"
#include "Access/MemoryAccess.h"

void MainLogic::ExecuteScript(char* fileName)
{
	//this looks ugly, but works... look away.
	if (!_pa.SetGameHandle(AppExeName.c_str(), (char*)AppWindowName.c_str())) {
		std::cout << ">> ERROR: could not set game handle and window name" << std::endl;
		return;
	}

	if (!keepLooping) {
		std::cout << "Loading script: " << fileName << std::endl;
		if (!_sm.LoadScript(fileName))
		{
			std::cout << ">> ERROR: Script File don't exist, please create one or make sure is not a typo." << std::endl;
			return;
		};
		std::cout << "Starting thread." << std::endl;
		loopThread = std::thread(&MainLogic::ExecutionThread, this, fileName);
	}
	else
	{
		//Code Safety during development, in case the script get executed twice.
		std::cout << "!! DEVELOPMENT WARNING: Stopping script from Execute Script Function." << std::endl;
		StopExecution();
	}
}

/// <summary>
/// Main Execution thread for reading the script and doing inputs
/// </summary>
/// <param name="filename"></param>
void MainLogic::ExecutionThread(char* filename) {
	keepLooping = true;
	currentFrame = 0;
	while (keepLooping) {
		printf("current frame: %lu \n", currentFrame);
		ExecuteFrame(currentFrame);
		CheckLoad();
		Sleep(60.0 / 60.0); //TODO: divide by the game framerate.
		currentFrame++;
	}
}

/// <summary>
/// Check the level transition loading status
/// </summary>
void MainLogic::CheckLoad() {

	if (WaitingLoadingToStart) {
		//TODO: Read values from a file or settings file
		std::vector<DWORD> offsets{ 0xA0 };
		intptr_t loadAddress;
		loadAddress = MemoryAccess::GetAddressFromOffsets(_pa.GetGameHwnd(), _pa.GetGameBaseMemoryAddress() + 0x03169448, offsets);
		while (!isInLoad && keepLooping) {
			isInLoad = MemoryAccess::GetByteInAddress(_pa.GetGameHwnd(), loadAddress);
			std::cout << "Waiting for load to start: " << isInLoad << std::endl;
		}
		//Load started, now we wait for it to end;
		WaitingLoadingToStart = false;
	}

	//if we are waiting for load to end, make sure the load at least started.
	if (WaitingLoadingToEnd && isInLoad) {
		//TODO: Read values from a file or settings file
		std::vector<DWORD> offsets{ 0x20,0x1D0 };
		intptr_t loadAddress;
		loadAddress = MemoryAccess::GetAddressFromOffsets(_pa.GetGameHwnd(), _pa.GetGameBaseMemoryAddress() + 0x03319550, offsets);
		while (isInLoad && keepLooping) {
			isInLoad = MemoryAccess::GetByteInAddress(_pa.GetGameHwnd(), loadAddress);
			std::cout << "Waiting for load to end: " << isInLoad << std::endl;
		}
		WaitingLoadingToEnd = false;
	}
}

void MainLogic::ExecuteFrame(unsigned long frame)
{
	ScriptManager::FrameCall currentFrameCalls;
	if (_sm.GetFunctionsFromFrame(frame, &currentFrameCalls)) {
		for (ScriptManager::FrameFunction i : currentFrameCalls.calls) {
			if (_sm.FunctionExist(i.funcNameA))
				_sm.CallFunction(i.funcNameA, i.args);
		}
		_inm.SendSavedInputs();
	}
}

void MainLogic::StopExecution()
{
	keepLooping = false;
	loopThread.detach();
}

void MainLogic::LoadTASSCript()
{
	_sm.LoadScript((char*)ScriptName.c_str());
}

bool MainLogic::IsRunning()
{
	return keepLooping;
}

unsigned long MainLogic::GetCurrentFrame()
{
	return currentFrame;
}

void MainLogic::InitialSetup()
{
	// Load names + functions into the ScriptManager
	_sm.AddScriptFunction("keyboard", FuncInterpreter::AddKeyboardInput);
	_sm.AddScriptFunction("mouse", FuncInterpreter::AddMouseInput);
	_sm.AddScriptFunction("movemouse", FuncInterpreter::AddMouseMoveInput);
	_sm.AddScriptFunction("showgame", FuncInterpreter::AddGameInFocus);
	_sm.AddScriptFunction("stop", FuncInterpreter::StopTAS);
	_sm.AddScriptFunction("setfps", FuncInterpreter::SetGameFPS);
	_sm.AddScriptFunction("waitloadstart", FuncInterpreter::WaitLoadStart);
	_sm.AddScriptFunction("waitloadend", FuncInterpreter::WaitLoadEnd);

	std::cout << ">> Initial Setup: Everything loaded." << std::endl;
}
