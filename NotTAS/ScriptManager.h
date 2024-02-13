#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include <functional>

/// <summary>
/// Responsable for reading the files and holding all the functions from and for the scripts.
/// </summary>
class ScriptManager
{
public:

	struct FileLine {
		unsigned long frame = 0;
		std::string call;
		std::vector<std::string> args;
	};

	static ScriptManager& GetInstance() {
		// We only need one call to this class, so making it a singleton would help reduce code.
		static ScriptManager instance;
		return instance;
	}
	//=-= Registering the function =-=
	struct FuncStruct
	{
		const char* Name;
		std::function<void( std::vector<std::string>)> frameFunction;
	};

	// =-= Internal function calling =-=
	struct FrameFunction {
		std::string funcNameA;
		std::vector<std::string> args;
	};

	struct FrameCall
	{
		unsigned long frameNumber;
		std::vector<FrameFunction> calls;
	};

	bool SaveScript(const char* fileName, std::vector<FileLine> fileLine);
	/// <summary>
	/// add a function to the list of functions that can be loaded by a script
	/// </summary>
	void AddScriptFunction(const char* funcName,std::function<void(std::vector<std::string>)> func);
	/// <summary>
	/// execute registered function by its name
	/// </summary>
	void CallFunction(std::string funcName, std::vector<std::string> args);
	///Read the file and set all the frames inside the FrameCalls struct.
	void LoadScript(char* filename);
	/// <summary>
	/// return all function calls from a frame.
	/// </summary>
	bool GetFunctionsFromFrame(unsigned long frame, FrameCall* framestruct);
	bool FunctionExist(std::string name);

private:
	std::vector<FileLine> LoadFile(const char* fileName);
	ScriptManager() {};
	std::vector<FuncStruct> functionsVector;
	std::vector<FrameCall> allFramesCalls;
};
#endif // SCRIPTMANAGER_H
