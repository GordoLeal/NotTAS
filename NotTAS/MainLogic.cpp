#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include "MainLogic.h"
#include "FuncInterpreter.h"
#include "Access/MemoryAccess.h"

void MainLogic::ExecuteScript(bool StartOnOpen)
{
	//wait for the program to start or start immediatly if possible
	if (StartOnOpen)
	{
		foas = false;
		keepChecking = true;
		std::thread([this]
			{
				std::cout << "[ExecuteScript-log]: Starting async loop 1..." << std::endl;
				bool keel = false;
				//keep trying to set the game handle and window, if it can set both it means the game is open.
				while (!keel) {
					std::cout << "[ExecuteScript-log]: Checking for the game." << std::endl;
					keel = _pa.SetGameHandle(AppExeName.c_str(), (char*)AppWindowName.c_str(), true);
					//keep checking == false, User asked to stop looking for the program.
					if (!keepChecking)
					{
						std::cout << "[ExecuteScript-log]: Stopping async loop 1..." << std::endl;
						return;
					}
					Sleep(5);
				};
				std::cout << "[ExecuteScript-log]: Process found" << std::endl;
				foas = true;
			}).detach();

			std::thread([this]
				{
					std::cout << "[ExecuteScript-log]: Startingn async loop 2..." << foas << std::endl;
					//wait for the game handle and window to be set
					while (!foas)
					{
						//keep checking == false, User asked to stop looking for the program.
						if (!keepChecking)
						{
							std::cout << "[ExecuteScript-log]: Stopping async loop 2..." << std::endl;
							return;
						}
						Sleep(5);
					}
					std::cout << "[ExecuteScript-log] Starting thread." << std::endl;
					loopThread = std::thread(&MainLogic::ExecutionThread, this);
				}).detach();

	}
	else
	{
		if (!_pa.SetGameHandle(AppExeName.c_str(), (char*)AppWindowName.c_str(), false))
		{
			std::cout << ">> [ExecuteScript-ERROR]: could not set game handle and window name" << std::endl;
			return;
		}

		//KeepLooping == true, it means the tool is already doing something, stop it.
		if (!keepLooping)
		{
			std::cout << "[ExecuteScript-log] Starting thread." << std::endl;
			loopThread = std::thread(&MainLogic::ExecutionThread, this);
		}
		else
		{
			//Code Safety during development, in case the script get executed twice.
			std::cout << "!! [ExecuteScript-WARNING] DEVELOPMENT WARNING: Stopping script from Execute Script Function." << std::endl;
			StopExecution();
		}
		//std::cout << "[ExecuteScript-log] Starting thread." << std::endl;
		//loopThread = std::thread(&MainLogic::ExecutionThread, this);

	}
}

void MySleep(double Milliseconds) {
	using namespace std::chrono;
	auto start = system_clock::now();
	bool test = false;
	do {
		auto end = system_clock::now();
		duration<double> passing = end - start;
		if (passing.count() >= Milliseconds)
			test = true;
	} while (!test);
}

/// <summary>
/// Main Execution thread for reading the script and doing inputs
/// </summary>
/// <param name="filename"></param>
void MainLogic::ExecutionThread() {
	keepLooping = true;
	currentFrame = 0;
	using namespace std::chrono;
	auto start = system_clock::now();

	while (keepLooping)
	{

		printf("[ExecutionThread-log] current frame: %lu \n", currentFrame);
		ExecuteFrame(currentFrame);
		CheckLoad();
		if (currentFrame == 59) {
			auto end = system_clock::now();

			duration<double> elapsed_seconds = end - start;
			std::cout << "[60 frame]" << elapsed_seconds.count() << std::endl;
		}
		if (currentFrame == 119) {
			auto end = system_clock::now();

			duration<double> elapsed_seconds = end - start;
			std::cout << "[120 frame]" << elapsed_seconds.count() << std::endl;
		}

		double teste = 1.0000f / toolFPS;
		std::cout << "[valor]" << teste << std::endl;
		MySleep(teste);
		//Sleep(teste);
		currentFrame++;
	}
}

/// <summary>
/// Check the level transition loading status
/// </summary>
void MainLogic::CheckLoad() {
	intptr_t afinalAddress = _pa.GetGameBaseMemoryAddress() + loadingAddress;
	if (WaitingLoadingToStart) {
		//std::vector<DWORD> offsets{ 0xA0 };
		intptr_t loadAddress;

		//loadAddress = MemoryAccess::GetAddressFromOffsets(_pa.GetGameHwnd(), _pa.GetGameBaseMemoryAddress() + 0x03169448, offsets);
		loadAddress = MemoryAccess::GetAddressFromOffsets(_pa.GetGameHwnd(), afinalAddress, loadingOffsets);

		do
		{
			isInLoad = MemoryAccess::GetByteInAddress(_pa.GetGameHwnd(), loadAddress);
			std::cout << "[waitload-start-log] Waiting for load to start: " << isInLoad << std::endl;
			//this delay is necessary otherwise IsInLoad is gonna byte flip at random. no idea what causes it
			Sleep(1);
		} while (!isInLoad && keepLooping);
		//Load started, now we wait for it to end;
		WaitingLoadingToStart = false;
	}

	//if we are waiting for load to end, make sure the load at least started.
	if (WaitingLoadingToEnd && isInLoad)
	{
		//std::vector<DWORD> offsets{ 0x20,0x1D0 };
		intptr_t loadAddress;

		//loadAddress = MemoryAccess::GetAddressFromOffsets(_pa.GetGameHwnd(), _pa.GetGameBaseMemoryAddress() + 0x03319550, offsets);
		loadAddress = MemoryAccess::GetAddressFromOffsets(_pa.GetGameHwnd(), afinalAddress, loadingOffsets);

		do
		{
			isInLoad = MemoryAccess::GetByteInAddress(_pa.GetGameHwnd(), loadAddress);
			std::cout << "[waitload-end-Log] Waiting for load to end: " << isInLoad << std::endl;
			//this delay is necessary otherwise IsInLoad is gonna byte flip at random. no idea what causes it
			Sleep(1);
		} while (isInLoad && keepLooping);
		WaitingLoadingToEnd = false;
	}
}

void MainLogic::ExecuteFrame(unsigned long frame)
{
	ScriptManager::FrameCall currentFrameCalls;
	if (_sm.GetFunctionsFromFrame(frame, &currentFrameCalls)) {
		for (ScriptManager::FrameFunction i : currentFrameCalls.calls) {
			if (i.funcNameA.at(0) == '!')
				continue;
			if (_sm.FunctionExist(i.funcNameA))
				_sm.CallFunction(i.funcNameA, i.args);
		}
		_inm.SendSavedInputs();
	}
}

void MainLogic::StopExecution()
{
	keepLooping = false;
	keepChecking = false;

	if (loopThread.joinable())
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

bool MainLogic::IsWaitingProcess()
{
	return keepChecking;
}

unsigned long MainLogic::GetCurrentFrame()
{
	return currentFrame;
}

void MainLogic::SetToolFPS(unsigned int fps)
{
	toolFPS = fps;
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
	_sm.AddScriptFunction("movecursor", FuncInterpreter::MoveCursor); //TODO: add movecursor to the UI
	_sm.AddScriptFunction("wait", FuncInterpreter::waitfor); //TODO: add movecursor to the UI

	std::cout << "[InitialSetup-log] Initial Setup: Everything loaded." << std::endl;
}
