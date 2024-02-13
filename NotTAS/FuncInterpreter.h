#ifndef FUNCINTERPRETER_H
#define FUNCINTERPRETER_H
#include <iostream>
#include <string>
#include <vector>

class FuncInterpreter
{
public:

	static void AddKeyboardInput(std::vector<std::string> args);
	static void AddMouseInput(std::vector<std::string> args);
	static void AddMouseMoveInput(std::vector<std::string> args);
	static void AddGameInFocus(std::vector<std::string> args);
	static void StopTAS(std::vector<std::string> args);
private:
	~FuncInterpreter() = default;

};
#endif // !FUNCINTERPRETER_H



