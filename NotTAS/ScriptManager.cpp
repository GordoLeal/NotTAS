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
bool ScriptManager::LoadFile(const char* filename, std::vector<ScriptManager::FileLine>& lines) {

	std::fstream fileStream(filename);
	if (!fileStream.is_open()) {
		std::cout << ">> [LoadFile-ERROR]: script file don't exist." << std::endl;
		return false;
	}

	std::string lineText;
	unsigned int rLine = 0;
	std::vector<ScriptManager::FileLine> outFrameCalls;

	while (std::getline(fileStream, lineText))
	{
		rLine++;
		if (lineText.empty())
			continue;

		ScriptManager::FileLine frame;

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-= Frame number =-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		size_t posStartBracks = lineText.find('<');
		size_t posEndBracks = lineText.find('>');

		if (posStartBracks == std::string::npos || posEndBracks == std::string::npos)
		{
			//TODO: better way to show errors
			std::cout << ">> [LoadFile-ERROR]: missing brackets in: " << rLine << std::endl;
			continue;
		}
		std::string subtLine = lineText;
		std::string a = subtLine.substr(posStartBracks + 1, (posEndBracks - posStartBracks) - 1);
		try {
			frame.frame = std::stoull(a);
		}
		catch (std::out_of_range e) { //invalid int value
			std::cout << ">> [LoadFile-ERROR]: invalid frame number at: " << rLine << "|\"" << a << "\"" << std::endl;
			continue;
		}

		lineText.erase(lineText.begin(), lineText.begin() + posEndBracks + 1);

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-= COMMENT =-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		if (lineText.at(0) == '!') {
			frame.call = lineText;
			outFrameCalls.push_back(frame);
			continue;
		}

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-= Function =-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		std::cout << "[LoadFile-log] reading line: " << rLine << std::endl;
		size_t posStartParentheses = lineText.find('(');
		size_t posEndParentheses = lineText.find(')');

		if (posStartParentheses == std::string::npos || posEndParentheses == std::string::npos)
		{
			std::cout << ">> [LoadFile-ERROR]: Missing parentheses in: " << rLine << std::endl;
			continue;
		}

		//check start paretheses
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
		if (posEndParentheses != posStartParentheses + 1) //if the parentheses is next one to another, there is not arguments to pass.
		{
			int j = 0;
			std::string _args;
			for (int i = posStartParentheses + 1; i < lineText.size(); i++)
			{
				char lineC = lineText[i];
				if (lineC != ')')
				{
					if (lineC == ' ')
					{
						continue;
					}
					if (lineC == ',')
					{
						frame.args.push_back(_args);
						_args.clear();
						j++;
						continue;
					}
					_args += lineC;
				}
				else
				{
					frame.args.push_back(_args);
					//ex: 123 ) -> 123 
					lineText.erase(0, i);
					break;
				}
			}

		}

		outFrameCalls.push_back(frame);
	}

	fileStream.close();
	lines = outFrameCalls;
	return true;
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
	std::cout << ">> [CallFunction-ERROR]: trying to call non existent function." << std::endl;
}

bool ForVectorComparisson(ScriptManager::FileLine& frame1, ScriptManager::FileLine& frame2) {
	return (frame1.frame < frame2.frame);
}

bool ScriptManager::SaveScript(const char* fileName)
{
	std::ofstream outfile;
	outfile.open(fileName);
	for (FrameCall i : allFramesCalls) {
		for (FrameFunction z : i.calls) {
			if (z.funcNameA.at(0) == '!') {
				outfile << "<" << i.frameNumber << ">" << z.funcNameA << "\n";
				continue;
			}

			outfile << "<" << i.frameNumber << ">" << z.funcNameA << "(";
			for (int j = 0; j < z.args.size(); j++) {


				if (z.args[j].size() <= 0)
					break;
				outfile << z.args[j];
				if (j + 1 < z.args.size())
					if (z.args[j + 1].length() > 0) {
						outfile << ",";
					}
			}
			outfile << ")\n";
		}
	}
	outfile.close();
	std::cout << "[SaveScript-log] Saved with sucess!" << std::endl;
	return true;
}

//Read the file and get all the frames inside the FrameCalls struct. Create a Vector with a FrameLine for each frame.
bool ScriptManager::LoadScript(char* filename) {

	std::vector<ScriptManager::FileLine> lines;
	if (!LoadFile(filename, lines))
	{
		return false;
	};

	if (lines.size() <= 0) {
		std::cout << ">> [SaveScript-ERROR]: no lines available in LoadScript" << std::endl;
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
		//std::cout << "call is:" << lines[i].call << " and is " << (lines[i].call.at(0) == '!') << std::endl;
		if (!(lines[i].call.at(0) == '!'))
		{
			//std::cout << "call is:" << lines[i].call << " | testing" << std::endl;
			found = false;
			//check if the function name from the line exists inside the registered functions
			for (FuncStruct x : functionsVector) {
				if (lines[i].call.compare(x.Name) == 0) {
					std::cout << lines[i].call << " won comparing agains: " << x.Name << std::endl;
					found = true;
					break;
				}
			}

			// if it don't, just show error and continue;
			if (!found) {
				printf(">> ERROR:[%s] is not a valid function \n", lines[i].call.c_str());
				continue;
			}
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

bool ScriptManager::LoadAndAddScriptToFrame(char* filename, unsigned int at)
{
	std::vector<ScriptManager::FileLine> lines;
	if (!LoadFile(filename, lines))
	{
		return false;
	};

	if (lines.size() <= 0) {
		std::cout << ">> [LoadAndAddScriptToFrame-ERROR]: no lines available" << std::endl;
		return false;
	}

	//Sort just in case.
	sort(lines.begin(), lines.end(), ForVectorComparisson);

	//Reserving memory
	FrameFunction* ff = new FrameFunction();
	ff->args.reserve(MAX_ARGS_SIZE);

	bool found;
	for (int i = 0; i < lines.size(); i++) {
		found = false;

		if (!(lines[i].call.at(0) == '!'))
		{
			found = false;
			//check if the function name from the line exists inside the registered functions
			for (FuncStruct x : functionsVector) {
				if (lines[i].call.compare(x.Name) == 0) {
					//std::cout << lines[i].call << " won comparing agains: " << x.Name << std::endl;
					found = true;
					break;
				}
			}

			// if don't, just show error and continue;
			if (!found) {
				printf(">> [LoadAndAddScriptToFrame-ERROR]:[%s] is not a valid function \n", lines[i].call.c_str());
				continue;
			}
			ff->args = lines[i].args;
		}

		ff->funcNameA = lines[i].call;
		AddFunctionToFrame(at + lines[i].frame, *ff);
		ff->args.clear();
	}
	return true;
}

bool ScriptManager::AddFunctionToFrame(unsigned int frame, FrameFunction function) {
	for (int i = 0; i < allFramesCalls.size(); i++) {
		if (allFramesCalls[i].frameNumber != frame)
			continue;
		allFramesCalls[i].calls.push_back(function);
		return true;
	}
	std::cout << "[log] AddFunctionToFrame: Creating new FrameCalls for: " << function.funcNameA << std::endl;
	//frame don't exist, create a new one.
	FrameCall frameNew;
	frameNew.frameNumber = frame;
	frameNew.calls.push_back(function);
	allFramesCalls.push_back(frameNew);
	return false;
}

bool ScriptManager::RemoveFunctionFromframe(unsigned int frame, FrameFunction function) {
	for (int i = 0; i < allFramesCalls.size(); i++) {
		if (allFramesCalls[i].frameNumber != frame) {
			continue;
		}
		std::vector<FrameFunction> frameCalls = allFramesCalls[i].calls;
		for (int j = 0; j < frameCalls.size(); j++) {
			if (frameCalls[j].funcNameA == function.funcNameA) { //find the function name.
				if (function.funcNameA.at(0) == '!') {
					if (allFramesCalls[i].calls.size() <= 1)
						allFramesCalls.erase(allFramesCalls.begin() + i);
					else
						allFramesCalls[i].calls.erase(allFramesCalls[i].calls.begin() + j);
					return true;
				}

				if (frameCalls[j].args.size() != function.args.size()) //check if the size is the same.[
				{
					break;
				}

				if (function.args.size() > 0) {
					bool isEqual = true;
					for (int z = 0; z < function.args.size(); z++) { //check all the args and if they are the same.
						if (frameCalls[j].args[z] != function.args[z]) {
							isEqual = false;
							break;
						}
					}
					if (!isEqual) // if is not, go to the next function
						break;
				}

				//if we are going to delete the only available function just delete the framecall so we don't get memory leak.
				if (allFramesCalls[i].calls.size() == 1)
					allFramesCalls.erase(allFramesCalls.begin() + i);
				else
					allFramesCalls[i].calls.erase(allFramesCalls[i].calls.begin() + j);

				return true;
			}
		}
	}
	return false;
}

void ScriptManager::GetFramesNumberList(std::vector<unsigned int>* list)
{
	for (FrameCall i : allFramesCalls) {
		list->push_back(i.frameNumber);
	}
}

static bool IsSameFunctionName(ScriptManager::FuncStruct search, std::string toFind) { return toFind.compare(search.Name); }

bool ScriptManager::FunctionExist(std::string name) {
	auto i = std::find_if(functionsVector.begin(), functionsVector.end(), [name](FuncStruct x) { return IsSameFunctionName(x, name); });
	return i != functionsVector.end();
}