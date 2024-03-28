#include <iostream>
#include <thread>
#include <filesystem>
#include "../Access/ProcessAccess.h"
#include "Window_Settings.h"
#include "../MainLogic.h"

using namespace std;
using namespace std::filesystem;
/// <summary>
/// System::String -> std::string
/// 
/// Copy Paste from MSND. not trying to re-invent the wheel.
/// https://learn.microsoft.com/en-us/cpp/dotnet/how-to-convert-system-string-to-standard-string
/// </summary>
/// <param name="s">in</param>
/// <param name="os">out</param>
static void MarshalString(System::String^ s, std::string& os) {
	using namespace System::Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}
/// <summary>
/// System::String -> std::wstring
/// 
/// Copy Paste from MSND. not trying to re-invent the wheel.
/// https://learn.microsoft.com/en-us/cpp/dotnet/how-to-convert-system-string-to-standard-string
/// </summary>
/// <param name="s">in</param>
/// <param name="os">out</param>
static void MarshalString(System::String^ s, std::wstring& os) {
	using namespace System::Runtime::InteropServices;
	const wchar_t* chars =
		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}

void NotTAS::Window_Settings::LoadSettingFiles()
{

	path profilesPath = "Settings/Profiles";
	create_directories("Settings/Profiles");

	for (const auto& entry : directory_iterator(profilesPath)) {
		std::cout << entry.path().filename() << std::endl;
		if (entry.path().filename().string().find(".profile") != std::string::npos)
		{
			//gives a bit more of work and code just to look a bit better. /shrugs
			string filen = (string)entry.path().filename().string();
			filen.erase(filen.begin() + filen.find(".profile"), filen.end());

			listBox_SettingFiles->Items->Add(gcnew String(filen.data()));
		}
	}
	string quickshotcut;
	if (SettingsFileManager::QuickLoadText("QuickPlayShorcut.txt", quickshotcut))
	{
		try {
			int t = stoi(quickshotcut, nullptr, 16);
			if (t >= 1 && t <= 254)
			{
				label_ValidCheckShortcut->Text = "Valid code";
				textBox_VirtualKeyShortcut->Text = gcnew String(quickshotcut.c_str());
			}
			else
			{
				label_ValidCheckShortcut->Text = "Invalid code!";
			}
		}
		catch (invalid_argument) {
			label_ValidCheckShortcut->Text = "Not a code!";
		}
	}
	else
	{
		textBox_VirtualKeyShortcut->Text = gcnew String("0x21");
	}
}

System::Void NotTAS::Window_Settings::checkBox_StartOnDetect_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void NotTAS::Window_Settings::button_SaveExit_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::wstring appExeName;
	MarshalString(textBox_AppExe->Text, appExeName);
	std::string appWindowName;
	MarshalString(textBox_AppWindowName->Text, appWindowName);

	_ml.AppExeName = appExeName;
	_ml.AppWindowName = appWindowName;
	this->Close();
	return System::Void();
}

System::Void NotTAS::Window_Settings::textBox_ScriptPath_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void NotTAS::Window_Settings::listBox_SettingFiles_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	// .profiles list
	if (listBox_SettingFiles->SelectedIndex <= -1) {
		//invalid selection
		return System::Void();
	}

	string profilesPath = "Settings/Profiles";
	SettingsFileManager::SettingsInfo info;
	std::string selectedProfile;
	MarshalString(listBox_SettingFiles->SelectedItem->ToString(), selectedProfile);
	//gives a bit more of work and code just to look a bit better. /shrugs
	cout << "[Settingsfile_SelectedIndexChanged-Log] path: " << (profilesPath + "/" + selectedProfile + ".profile") << endl;
	SettingsFileManager::LoadSettingsFile((const char*)(profilesPath + "/" + selectedProfile + ".profile").c_str(), info);
	wcout << "[Settingsfile_SelectedIndexChanged-Log] info.exeame:" << info.ExeName << "\n";
	textBox_AppExe->Text = gcnew String(info.ExeName.data());
	textBox_AppWindowName->Text = gcnew String(info.WindowName.data());
	_ml.AppExeName = info.ExeName;
	_ml.AppWindowName = info.WindowName;
	_ml.fpsAddress = info.FPSAddress;
	_ml.fpsOffsets = info.FPSOffsets;
	_ml.loadingAddress = info.LoadingAddress;
	_ml.loadingOffsets = info.LoadingOffsets;
	wcout << "[Settingsfile_SelectedIndexChanged-Log] appexename:" << _ml.AppExeName << "\n";
	cout << "[Settingsfile_SelectedIndexChanged-Log] appwindowname:" << _ml.AppWindowName << endl;
	return System::Void();
}

System::Void NotTAS::Window_Settings::linkLabel_VirtualKeyCode_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
{
	System::Diagnostics::Process::Start("https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes");
}

System::Void NotTAS::Window_Settings::textBox_VirtualKeyShortcut_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	string a;
	MarshalString(textBox_VirtualKeyShortcut->Text, a);
	try {
		int t = stoi(a, nullptr, 16);
		if (t > 0 && t < 255)
		{
			label_ValidCheckShortcut->Text = "Valid code";
			SettingsFileManager::QuickSaveText("QuickPlayShorcut.txt", a);
		}
		else
		{
			label_ValidCheckShortcut->Text = "Invalid code!";
		}
	}
	catch (invalid_argument) {
		label_ValidCheckShortcut->Text = "Not a code!";
	}

}
