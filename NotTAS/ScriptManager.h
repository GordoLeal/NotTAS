#pragma once
#include <string>
#include <vector>

#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H


struct FrameCall {
	unsigned long frame = 0;
	std::string call;
	std::vector<std::string> args;
};

class ScriptManager
{

public:
	void LoadScript(const char* fileName);
	std::vector<FrameCall> GetVectorFrameCalls();

};
#endif // SCRIPTMANAGER_H



