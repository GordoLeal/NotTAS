#include "Window_ControlPainel.h"
#include "Window_Editor.h"
using namespace NotTAS;

System::Void NotTAS::Window_ControlPainel::Button_OpenEditor_Click(System::Object^ sender, System::EventArgs^ e)
{
	Window_Editor^ editor = gcnew Window_Editor();
	editor->Show();
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::Button_StartSystem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MainLogic& ml = MainLogic::GetInstance();
	if (ml.ScriptName.empty() || ml.ScriptName == "") {
		std::cout << ">> ERROR: scriptname is empty, please write the name of a file in settings." << std::endl;
		return;
	}

	if (!ml.IsRunning()) {
		std::cout << "Starting..." << std::endl;
		std::cout << ml.ScriptName << std::endl;
		ml.startingFrame = (int)numeric_StartFromFrame->Value;
		ml.ExecuteScript((char*)ml.ScriptName.c_str());
		bWorker->RunWorkerAsync();
	}
	else
	{
		std::cout << "Stopping..." << std::endl;
		ml.StopExecution();
	}

	return System::Void();
}



System::Void NotTAS::Window_ControlPainel::Button_OpenSettings_Click(System::Object^ sender, System::EventArgs^ e)
{
	Window_Settings^ settings = gcnew Window_Settings;
	settings->ShowDialog();
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::numeric_StartFromFrame_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{

	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::bWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
{
	MainLogic& ml = MainLogic::GetInstance();
	while (true) {
		if (bWorker->CancellationPending) {
			e->Cancel = true;
			break;
		}
		bWorker->ReportProgress(1);
		if (!ml.IsRunning()) {
			bWorker->CancelAsync();
		}
		System::Threading::Thread::Sleep(100);
	}
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::bWorker_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e)
{
	std::cout << "testando3" << std::endl;
	MainLogic& ml = MainLogic::GetInstance();
	Button_StartSystem->Text = ml.IsRunning() ? gcnew String("Stop") : gcnew String("Play");
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::bWorker_WorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
{
	Button_StartSystem->Text = gcnew String("Play");
	return System::Void();
}


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
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
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
