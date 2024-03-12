#ifndef SETTINGSFILEMANAGER_H
#define SETTINGSFILEMANAGER_H
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

class SettingsFileManager
{
public:
	struct SettingsInfo
	{
		//std::string PresentationText;
		std::string WindowName;
		std::wstring ExeName;
		uintptr_t LoadingAddress;
		std::vector<DWORD> LoadingOffsets;
		uintptr_t FPSAddress;
		std::vector<DWORD> FPSOffsets;
	};
	static void LoadSettingsFile(const char* filepath, SettingsInfo & info);
private:
};
#endif
