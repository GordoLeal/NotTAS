#include <string>
#include <vector>
#include <iostream>
#include <functional>

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
	static ScriptManager& GetInstance() {
		// We only need one call to this class, so making it a singleton would help reduce code.
		static ScriptManager instance;
		return instance;
	}

	struct funcStruct
	{
		const char* Name;
		std::function<void(char**)> func;
	};

	std::vector<FrameCall> LoadScript(const char* fileName);
	bool SaveScript(const char* fileName, std::vector<FrameCall> framecalls);
	void AddScriptFunction(const char* functionName,std::function<void(char**)> func);
	void CallFunction(const char* functionName, char** args);

private:
	std::vector<funcStruct> functionsVector;
};
#endif // SCRIPTMANAGER_H
