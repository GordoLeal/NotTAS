#include <iostream>
#include <string>
#include "InputManager.h"

#ifndef FUNCINTERPRETER_H
#define FUNCINTERPRETER_H

class FuncInterpreter
{
public:
	static void AddKeyboardInput(char** args);
	static void AddMouseInput(char** args);
	static void AddMouseMoveInput(char** args);
private:
	~FuncInterpreter() = default;

};
#endif // !FUNCINTERPRETER_H



