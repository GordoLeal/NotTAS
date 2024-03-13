#include <iostream>
#include <fstream>
#include "SettingsFileManager.h"
#include "MainLogic.h"

using namespace std;
//MainLogic& _ml = MainLogic::GetInstance();

void SettingsFileManager::LoadSettingsFile(const char* filepath, SettingsInfo& info)
{
	fstream filestream(filepath);
	if (!filestream.is_open()) {
		std::cout << ">> [LoadSettigsFile-ERROR]: script file don't exist. :" << filepath << std::endl;
		return;
	}
	unsigned int lineCount = 0;
	string linetext;
	while (getline(filestream, linetext)) {
		lineCount++;
		
		if (linetext.empty())
			continue;

		size_t equalPos = linetext.find('=');
		if (equalPos == string::npos) {
			std::cout << ">> [LoadSettigsFile-ERROR]: missing = in line: " << lineCount << " | line: " << linetext << std::endl;
			return;
		}

		string arg = linetext;
		string result = linetext;
		// arg=0x000
		arg.erase(arg.begin() + equalPos, arg.end()); // arg
		result.erase(result.begin(), result.begin() + equalPos+1);// 0x000
		cout << "[LoadSettingsFile-log] arg:" << arg << "| result:" << result << endl;

		//if (arg == "presentationtext") { info.PresentationText = result; }
		
		if (arg == "windowname") { info.WindowName = result; }
		
		else if (arg == "exename") 
		{
			std::wstring a(result.begin(), result.end());
			info.ExeName = a;
		}
		
		// =-=-=-= LOADING ADDRESS =-=-=-=

		else if (arg == "loadingaddress") { 
			info.LoadingAddress = strtoul(result.c_str(), nullptr, 0);

		}
		
		else if(arg == "loadingoffsets")
		{
			vector<DWORD> strOffsets;
			string buff;
			for (int i = 0; i < result.size(); i++) {
				if (result.at(i) == ' ')
					continue;
				if (result.at(i) == ',') {
					unsigned long conv = strtoul(buff.c_str(),nullptr,0);
					cout << "[LoadSettingsFile-Log] Loading buffer: " << buff <<"|conversion to: "<< conv << endl;
					info.LoadingOffsets.push_back(conv);
					buff.clear();
					continue;
				}
				buff += result.at(i);

				if (i + 1 >= result.size()) {
					unsigned long conv = strtoul(buff.c_str(), nullptr, 0);
					cout << "[LoadSettingsFile-Log] Loading buffer: " << buff << "|conversion to: " << conv << endl;
					info.LoadingOffsets.push_back(conv);
					buff.clear();
				}
			}
		}
		
		// =-=-=-= FPS ADDRESS =-=-=-=

		else if(arg == "fpsaddress")
		{
			info.FPSAddress = strtoul(result.c_str(), nullptr, 0);
		}
		
		else if(arg == "fpsoffsets")
		{
			vector<DWORD> strOffsets;
			string buff;
			for (int i = 0; i < result.size(); i++) {
				if (result.at(i) == ' ')
					continue;
				if (result.at(i) == ',') {
					unsigned long conv = strtoul(buff.c_str(), nullptr, 0);
					cout << "[LoadSettingsFile-Log] FPS buffer: " << buff << "|conversion to: " << conv << endl;
					info.FPSOffsets.push_back(conv);
					buff.clear();
					continue;
				}

				buff += result.at(i);

				if (i + 1 >= result.size()) {
					unsigned long conv = strtoul(buff.c_str(), nullptr, 0);
					cout << "[LoadSettingsFile-Log] FPS buffer: " << buff << "|conversion to: " << conv << endl;
					info.FPSOffsets.push_back(conv);
					buff.clear();
				}
			}
		}
		
	}
	filestream.close();
}

void SettingsFileManager::QuickSaveText(const char* filepath, std::string text)
{
	std::string s = "Settings/";
	s.append(filepath);
	std::ofstream outfile(s);
	outfile << text;
	outfile.close();

}

bool SettingsFileManager::QuickLoadText(const char* filepath, std::string& text)
{
	std::string s = "Settings/";
	s.append(filepath);
	std::fstream fileStream(s);
	if (!fileStream.is_open()) {
		std::cout << ">> [QuickLoadText-ERROR]: file don't exist." << std::endl;
		return false;
	}

	std::string lineText;
	while (std::getline(fileStream, lineText)) {
		text.append(lineText);
	}
	fileStream.close();
	return true;
}
