#ifndef FUNCINTERPRETER_H
#define FUNCINTERPRETER_H
#include <iostream>
#include <string>
#include <vector>
#include "MainLogic.h"
#include "Access/MemoryAccess.h"
#include "Access/ProcessAccess.h"

/// <summary>
/// Interpretation layer between what is written on the script file and the source code.
/// </summary>
class FuncInterpreter
{
	//everything here is being setup at first load on MainLogic.cpp InitialSetup function
public:
	static void AddKeyboardInput(std::vector<std::string> args);
	static void AddMouseInput(std::vector<std::string> args);
	static void AddMouseMoveInput(std::vector<std::string> args);
	static void AddGameInFocus(std::vector<std::string> args);
	static void StopTAS(std::vector<std::string> args);
	static void SetGameFPS(std::vector<std::string> args);
	static void WaitLoadStart(std::vector<std::string> args);
	static void WaitLoadEnd(std::vector<std::string> args);
	static void MoveCursor(std::vector<std::string> args);
	static void waitfor(std::vector<std::string> args);
private:
	MainLogic& _ml = MainLogic::GetInstance();
	~FuncInterpreter() = default;

};
#endif // !FUNCINTERPRETER_H



