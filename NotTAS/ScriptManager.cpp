#include <fstream>
#include <iostream>
#include <functional>
#include <optional>
//#include <string>
//#include <vector>
#include "ScriptManager.h"

using namespace std;

// LoadScripts from file.
// The line should be: TIMEFRAME function (args1, args2 ..., args5) \n
// Max number of args is 5.
vector<FrameCall> ScriptManager::LoadScript(const char* filename) {

	fstream fileStream(filename);
	string lineText;
	unsigned int rLine = 0;
	vector<FrameCall> outFrameCalls;

	//Probably  there is a better way of doing this, but i don't care at the moment. - Gordo

	while (getline(fileStream, lineText))
	{
		rLine++;
		FrameCall frame;
		// =-=-=-=-=-=-=-=--=-=--= Frame number =--=-=-=--=-=-=--=-=--=
		size_t posStartBracks = lineText.find('<');
		size_t posEndBracks = lineText.find('>');

		if (posStartBracks == string::npos || posEndBracks == string::npos)
		{
			//TODO: better way to show errors
			cout << ">> ERROR missing brackets in: " << rLine << endl;
			continue;
		}
		string subtLine = lineText;
		string a = subtLine.substr(posStartBracks + 1, (posEndBracks - posStartBracks) - 1);
		try {
			//frame.frame = stoul(subtLine.substr(posStartBracks + 1, (posEndBracks - posStartBracks) - 1));
			frame.frame = stoull(a);
		}
		catch (out_of_range e) { //invalid int value
			//TODO: better way to show errors
			cout << ">> ERROR invalid frame number at: " << rLine << endl;
			cout << a << endl;
		}

		lineText.erase(lineText.begin(), lineText.begin() + posEndBracks + 1);

		// =-=-=-=-=-=-=--=-=-=--=- Function =-=--==--=-=-=--=-=-=-=--=-=--==--=
		cout << "reading line: " << rLine << endl;
		int stopedAt = 0;

		size_t posStartParentheses = lineText.find('(');
		size_t posEndParentheses = lineText.find(')');

		if (posStartParentheses == string::npos || posEndParentheses == string::npos)
		{
			//TODO: better way to show errors
			cout << ">> ERROR missing parentheses in: " << rLine << endl;
			continue;
		}

		for (char i : lineText) {
			if (i != '(')
			{
				if (i == ' ')
				{
					continue;
				}

				frame.call += i;
			}
			else
			{
				break;
			}
		}

		// =-=-=-=-=--=-=-=-=  ARGS  =-=-=-=--=-=-=--=
		unsigned int j = 0;
		string _args[5];

		for (int i = posStartParentheses + 1; i < lineText.size(); i++) {
			if (lineText[i] != ')') {
				if (lineText[i] == ' ') {
					continue;
				}
				if (lineText[i] == ',')
				{
					j++;
					if (j > 5) {
						//TODO: better way to show errors
						cout << "wtf are you doing?" << endl;
						cout << ">> ERROR way to much arguments" << rLine << endl; //better way to handle errors
					}
					continue;
				}
				_args[j] += lineText[i];
			}
			else
			{
				//ex: 123 ) -> 123 
				lineText.erase(0, i);
				break;
			}
		}

		frame.args.insert(frame.args.end(), &_args[0], &_args[5]);
	}
	fileStream.close();
	return outFrameCalls;
}

bool ScriptManager::SaveScript(const char* fileName, std::vector<FrameCall> framecalls)
{
	return false;
}

void ScriptManager::AddScriptFunction(const char* functionName, std::function<void(char**)> func)
{
	funcStruct f;
	f.Name = functionName;
	f.func = func;
	functionsVector.push_back(f);
}

void ScriptManager::CallFunction(const char* functionName, char** args)
{
	for (funcStruct i : functionsVector) 
	{
		if (i.Name == functionName) {
			i.func(args);
			return;
		}

	}
	//TODO: better way to show errors
	cout << ">> ERROR: trying to call function that don't exist" << endl;
}
