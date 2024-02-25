#include <filesystem>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include "ScriptManager.h"

//Note: I could use Ellipsis for the parameters, but for the sake of sanity and consistency, i choose to stick with an static ammount.
#define MAX_ARGS_SIZE 5

/// <summary>
/// LoadScripts from file.
/// The line should be: TIMEFRAME function (args1, args2 ..., args5) \n
/// Max number of args is 5.
/// </summary>
/// <param name="filename"></param>
/// <param name="lines"></param>
/// <returns></returns>
bool ScriptManager::LoadFile(const char* filename, std::vector<ScriptManager::FileLine> &lines) {

	std::fstream fileStream(filename);
	if (!fileStream.is_open()) {
		std::cout << ">> ERROR: script file don't exist." << std::endl;
		return false;
	}
	std::string lineText;
	unsigned int rLine = 0;
	std::vector<ScriptManager::FileLine> outFrameCalls;
	//Probably there is a better way of doing this, but i don't care at the moment. - Gordo

	while (std::getline(fileStream, lineText))
	{
		rLine++;
		if (lineText.empty())
			continue;

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-= COMMENT =-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		if (lineText.at(0) == '!')
			continue;

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-= Frame number =-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		ScriptManager::FileLine frame;

		size_t posStartBracks = lineText.find('<');
		size_t posEndBracks = lineText.find('>');

		if (posStartBracks == std::string::npos || posEndBracks == std::string::npos)
		{
			//TODO: better way to show errors
			std::cout << ">> ERROR: missing brackets in: " << rLine << std::endl;
			continue;
		}
		std::string subtLine = lineText;
		std::string a = subtLine.substr(posStartBracks + 1, (posEndBracks - posStartBracks) - 1);
		try {
			frame.frame = std::stoull(a);
		}
		catch (std::out_of_range e) { //invalid int value
			std::cout << ">> ERROR: invalid frame number at: " << rLine << "|\""<< a << "\""<< std::endl;
			continue;
		}

		lineText.erase(lineText.begin(), lineText.begin() + posEndBracks + 1);

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-= Function =-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		std::cout << "reading line: " << rLine << std::endl;
		int stopedAt = 0;

		size_t posStartParentheses = lineText.find('(');
		size_t posEndParentheses = lineText.find(')');

		if (posStartParentheses == std::string::npos || posEndParentheses == std::string::npos)
		{
			//TODO: better way to show errors
			std::cout << ">> ERROR: missing parentheses in: " << rLine << std::endl;
			continue;
		}

		for (char i : lineText) {
			if (i != '(')
			{
				if (i == ' ')
				{
					continue;
				}
				frame.call += tolower(i);
			}
			else
			{
				break;
			}
		}

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=  ARGS  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		int j = 0;
		std::string _args;
		frame.args.resize(MAX_ARGS_SIZE);
		frame.args[j] = _args;
		for (int i = posStartParentheses + 1; i < lineText.size(); i++) {
			char lineC = lineText[i];
			if (lineC != ')') {
				if (lineC == ' ') {
					continue;
				}
				if (lineC == ',')
				{
					frame.args[j] = _args;
					_args = {};
					j++;
					if (j > MAX_ARGS_SIZE) {
						//TODO: better way to show errors
						std::cout << "wtf are you doing?" << std::endl;
						std::cout << ">> ERROR: way to much arguments" << rLine << std::endl; //better way to handle errors
					}
					continue;
				}
				_args += lineC;
			}
			else
			{
				frame.args[j] = _args;
				//ex: 123 ) -> 123 
				lineText.erase(0, i);
				break;
			}
		}
		outFrameCalls.push_back(frame);
	}

	fileStream.close();
	lines = outFrameCalls;
	return true;
}

bool ScriptManager::SaveScript(const char* fileName, std::vector<ScriptManager::FileLine> framecalls)
{
	//TODO: Save all function calls inside the file
	return false;
}

void ScriptManager::AddScriptFunction(const char* functionName, std::function<void(std::vector<std::string>)> func)
{
	FuncStruct f;
	f.Name = functionName;
	f.frameFunction = func;
	functionsVector.push_back(f);
}

void ScriptManager::CallFunction(std::string funcName, std::vector<std::string> args)
{
	for (FuncStruct i : functionsVector)
	{
		if (i.Name == funcName) {
			i.frameFunction(args);
			return;
		}

	}
	std::cout << ">> ERROR: trying to call non existent function." << std::endl;
}

bool ForVectorComparisson(ScriptManager::FileLine& frame1, ScriptManager::FileLine& frame2) {
	return (frame1.frame < frame2.frame);
}

//Read the file and get all the frames inside the FrameCalls struct. Create a Vector with a FrameLine for each frame.
bool ScriptManager::LoadScript(char* filename) {

	std::vector<ScriptManager::FileLine> lines;
	if (!LoadFile(filename, lines)) 
	{
		return false;
	};

	if (lines.size() <= 0) {
		std::cout << ">> ERROR: no lines available in LoadScript" << std::endl;
		return false;
	}
	//Sort just in case.
	sort(lines.begin(), lines.end(), ForVectorComparisson);
	allFramesCalls.clear();
	//Reserving memory
	FrameCall* currentFrameCalls = new FrameCall();
	FrameFunction* ff = new FrameFunction();
	ff->args.reserve(MAX_ARGS_SIZE);

	bool found = false;
	currentFrameCalls->frameNumber = lines[0].frame;
	for (int i = 0; i < lines.size(); i++) {

		found = false;
		//check if the function name from the line exists inside the registered functions
		for (FuncStruct x : functionsVector) {
			if (lines[i].call.compare(x.Name)) {
				found = true;
				break;
			}
		}

		// if it don't, just show error and continue;
		if (!found) {
			//TODO: Better way to show this error to the user
			printf(">> ERROR:[%s] is not a valid function", lines[i].call.c_str());
			continue;
		}

		ff->funcNameA = lines[i].call;
		ff->args = lines[i].args;
		currentFrameCalls->calls.push_back(*ff);
		ff->args.clear();
		if (i + 1 >= lines.size()) {
			allFramesCalls.push_back(*currentFrameCalls);
			break;
		}
		else if (currentFrameCalls->frameNumber != lines[i + 1].frame)
		{
			allFramesCalls.push_back(*currentFrameCalls);
			currentFrameCalls = new FrameCall();
			currentFrameCalls->frameNumber = lines[i + 1].frame;
		}
	}
	return true;
}

bool ScriptManager::FileExists(char* filename)
{
	return std::filesystem::exists(filename);
}

void ScriptManager::ReplaceFrameCallsFromList(FrameCall FrameCalls)
{
	bool alreadyExists = false;

	//try finding if the framecall already exists for that frame.
	for (FrameCall i : allFramesCalls) {
		if (FrameCalls.frameNumber == i.frameNumber) 
		{
			//if it does, just replace all the calls.
			alreadyExists = true;
			i.calls = FrameCalls.calls;
			break;
		}
	}
	if (!alreadyExists) {
		allFramesCalls.push_back(FrameCalls);
	}

}

bool ScriptManager::GetFunctionsFromFrame(unsigned long frame, FrameCall* framecallStruct) {
	for (int i = 0; i < allFramesCalls.size(); i++) {
		if (allFramesCalls[i].frameNumber != frame) {
			continue;
		}
		*framecallStruct = allFramesCalls[i];
		return true;
	}
	return false;
}

static bool IsSameFunctionName(ScriptManager::FuncStruct search, std::string toFind) { return toFind.compare(search.Name); }

bool ScriptManager::FunctionExist(std::string name) {
	auto i = std::find_if(functionsVector.begin(), functionsVector.end(), [name](FuncStruct x) { return IsSameFunctionName(x, name); });
	return i != functionsVector.end();
}