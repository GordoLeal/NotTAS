#include <iostream>
#include <thread>
#include "../Access/ProcessAccess.h"
#include "Window_Settings.h"
#include "../MainLogic.h"


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


	MainLogic& ml = MainLogic::GetInstance();
	ml.AppExeName = appExeName;
	ml.AppWindowName = appWindowName;
	this->Close();
	return System::Void();
}

System::Void NotTAS::Window_Settings::textBox_ScriptPath_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}



