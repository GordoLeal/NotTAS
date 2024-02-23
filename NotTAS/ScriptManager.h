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

	// =-= Registering the function =-=
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
	/// <summary>
	/// Save allFunctionsCall inside the file
	/// </summary>
	/// <param name="fileName"></param>
	/// <param name="fileLine"></param>
	/// <returns></returns>
	bool SaveScript(const char* fileName, std::vector<FileLine> fileLine);
	
	/// <summary>
	/// add a function to the list of functions that can be loaded by a script
	/// </summary>
	void AddScriptFunction(const char* funcName,std::function<void(std::vector<std::string>)> func);
	
	/// <summary>
	/// execute registered function by its name
	/// </summary>
	void CallFunction(std::string funcName, std::vector<std::string> args);
	
	/// <summary>
	/// Read the file and set all the frames inside the FrameCalls struct.
	/// </summary>
	/// <param name="filename"></param>
	void LoadScript(char* filename);

	// =-=-=-=-=- Get and Set Frame CAlls =-==--=--=-=-
	/// <summary>
	/// return all function calls from a frame.
	/// </summary>
	bool GetFunctionsFromFrame(unsigned long frame, FrameCall* framestruct);
	/// <summary>
	/// Replaces (or add if is non existent) all the calls from a framecall to a frame.
	/// </summary>
	void ReplaceFrameCallsFromList(FrameCall FrameCalls);
	//-0-0-0-0-0-0-0-0-0-0-0-0-0-

	/// <summary>
	/// Check if file exists
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	static bool FileExists(char* filename);
	bool FunctionExist(std::string name);

private:
	std::vector<FileLine> LoadFile(const char* fileName);
	ScriptManager() {};
	std::vector<FuncStruct> functionsVector;
	std::vector<FrameCall> allFramesCalls;
};
#endif // SCRIPTMANAGER_H
