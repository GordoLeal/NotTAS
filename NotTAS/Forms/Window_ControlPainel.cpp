#include <thread>
#include <iostream>
#include "../SettingsFileManager.h"
#include "Window_ControlPainel.h"
using namespace NotTAS;


//
//ScriptManager& _sm = ScriptManager::GetInstance();
//MainLogic& _ml = MainLogic::GetInstance();

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

void Window_ControlPainel::AddFunction(ScriptManager::FrameFunction fFunction) {
	if (_sm.AddFunctionToFrame((unsigned int)numUD_EditingFrame->Value, fFunction)) {
		std::cout << "[AddFunction-log] Added: " << fFunction.funcNameA << " to frame: " << (unsigned int)numUD_EditingFrame->Value << std::endl;
	}
	UpdateCurrentEditingTextBoxes();
}

void Window_ControlPainel::UpdateCurrentEditingTextBoxes()
{
	// This blocks any Update loops from happening;

	listBox_EditingFrame->Items->Clear();
	ScriptManager::FrameCall frCalls;
	_sm.GetFunctionsFromFrame((unsigned int)numUD_EditingFrame->Value, &frCalls);
	if (frCalls.calls.size() > 0)
		for (ScriptManager::FrameFunction i : frCalls.calls) {
			std::string buf = "";
			if (i.funcNameA.at(0) == '!') {
				buf += i.funcNameA;
				listBox_EditingFrame->Items->Add(gcnew String(buf.data()));
				continue;
			}
			buf += i.funcNameA + "(";
			std::cout << "[UpdateEditingFrame-log] (" << i.funcNameA << ") have: (" << i.args.size() << ") args." << std::endl;
			for (int j = 0; j < i.args.size(); j++) {
				if (i.args[j].size() <= 0) {
					std::cout << "[UpdateEditingFrame-log]" << i.funcNameA << " don't have value in arg:" << j << std::endl;
					continue;
				}
				buf += i.args[j];
				std::cout << "[UpdateEditingFrame-log] (" << i.funcNameA << ") adding arg: (" << i.args[j] << ") at:" << j << std::endl;
				if (j + 1 < i.args.size())
					if (i.args[j + 1].length() > 0) {
						buf += ",";
					}
			}
			buf += ")";
			listBox_EditingFrame->Items->Add(gcnew String(buf.data()));
		}

	if (UIIsUpdating)
		return;
	UIIsUpdating = true;
	int oldSel = listBox_FramesNumber->SelectedIndex;

	listBox_FramesNumber->Items->Clear();
	std::vector<unsigned int> i;
	_sm.GetFramesNumberList(&i);
	if (i.size() > 0) {
		sort(i.begin(), i.end());
		for (unsigned int a : i) {
			listBox_FramesNumber->Items->Add(a);
		}
	}
	else
	{
		i.clear();
	}

	//if we select nothing to start, then do nothing.
	if (oldSel > -1) {
		// If the last selection is the last, keep the selection with the last object.
		if (listBox_FramesNumber->Items->Count == oldSel)
			listBox_FramesNumber->SelectedIndex = listBox_FramesNumber->Items->Count - 1;
		else
			listBox_FramesNumber->SelectedIndex = oldSel;
	}


	UIIsUpdating = false;
}

void NotTAS::Window_ControlPainel::DoStartExecution()
{
	std::cout << "[StartSystem-log] Starting..." << std::endl;
	std::cout << _ml.ScriptName << std::endl;
	_ml.SetToolFPS((unsigned int)numUD_ToolFPS->Value);
	_ml.startingFrame = (int)numeric_StartFromFrame->Value;
	_ml.ExecuteScript(checkBox_StartOnGameDetect->Checked);
	if (checkBox_StartOnGameDetect->Checked) {
		checkBox_StartOnGameDetect->Enabled = false;
	}
}

void NotTAS::Window_ControlPainel::DoStopExecution() {
	std::cout << "[StartSystem-log] Stopping..." << std::endl;
	checkBox_StartOnGameDetect->Enabled = true;
	_ml.StopExecution();
}

System::Void NotTAS::Window_ControlPainel::Button_StartSystem_Click(System::Object^ sender, System::EventArgs^ e)
{
	// Play button
	Button_StartSystem->Enabled = false;

	if (!_ml.IsRunning() && !_ml.IsWaitingProcess()) {

		DoStartExecution();
	}
	else
	{
		DoStopExecution();
	}
	Button_StartSystem->Enabled = true;
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::Button_OpenSettings_Click(System::Object^ sender, System::EventArgs^ e)
{
	Window_Settings^ settings = gcnew Window_Settings;
	settings->ShowDialog();
	std::string quickplayshortcut;
	if (SettingsFileManager::QuickLoadText("QuickPlayShorcut.txt", quickplayshortcut))
	{
		std::cout << "[Initial Main Window Load] Loading Quick Play Shortcut" << std::endl;
		try {
			int t = std::stoi(quickplayshortcut, nullptr, 16);
			if (t >= 1 && t <= 254)
			{
				//valid
				shortcutkey = t;
			}
		}
		catch (std::invalid_argument) {
			std::cout << ">> [Initial Main Window Load] INVALID SHORTCUT, SET TO DEFAULT [PAGEUP] BUTTON" << std::endl;
		}
	}
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::numeric_StartFromFrame_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	// Start From Frame value
	_ml.startingFrame = (unsigned int)numeric_StartFromFrame->Value;
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::bWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
{
	while (true) {
		if (bWorker->CancellationPending) {
			e->Cancel = true;
			break;
		}
		//if form is not yet created, just skip until the form have a handle.
		if (!IsHandleCreated)
			continue;
		this->BeginInvoke(gcnew  Action(this, &NotTAS::Window_ControlPainel::CheckPlayStopKeyPress));
		if (_ml.IsRunning() || _ml.IsWaitingProcess()) {
			this->BeginInvoke(gcnew  Action<String^>(this, &NotTAS::Window_ControlPainel::UpdateButtonText), "Stop");
		}
		else
		{
			this->BeginInvoke(gcnew  Action<String^>(this, &NotTAS::Window_ControlPainel::UpdateButtonText), "Play");
		}

		System::Threading::Thread::Sleep(100);
	}
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::bWorker_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
{
	if (e->Error != nullptr)
	{
		//if a error happened inside the background worker thread, forms will stop the backgroud thread and store the error inside the RunWorkerCompleteEVentArgs
		std::cout << ">> [bWorker_DoWork-ERROR] BACKGROUND WORKER CRASH!" << std::endl;
		std::string error;
		MarshalString(e->Error->Message, error);
		std::cout << error << std::endl;
	}
	return System::Void();
}

void NotTAS::Window_ControlPainel::UpdateButtonText(String^ text)
{
	if (Button_StartSystem->IsHandleCreated)
		Button_StartSystem->Text = text;
}

void NotTAS::Window_ControlPainel::CheckPlayStopKeyPress()
{
	//Is key down?
	if (GetAsyncKeyState(shortcutkey) & 0x8000 && !IsPressingSwitchPlayButton)
	{
		IsPressingSwitchPlayButton = true;
		if (!_ml.IsRunning() && !_ml.IsWaitingProcess())
		{
			DoStartExecution();
		}
		else
		{
			DoStopExecution();
		}
	}
	else if(GetAsyncKeyState(shortcutkey) & 0x8000 && IsPressingSwitchPlayButton) //Is user holding the button?
	{
		// Do nothing
	}
	else // key is not being pressed, just release
	{
		IsPressingSwitchPlayButton = false;
	}
}

System::Void NotTAS::Window_ControlPainel::button_AddKeyboardKey_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (textBox_KB_Key->Text == "" || comboBox_KB_InputType->Text == "") {
		MessageBoxA(nullptr, "Missing a few settings", "Error", MB_OK);
		return System::Void();
	}
	// add keyboard input button
	ScriptManager::FrameFunction fFunction;
	fFunction.funcNameA = "keyboard";
	fFunction.args.resize(2);
	MarshalString(textBox_KB_Key->Text, fFunction.args[0]);
	MarshalString(comboBox_KB_InputType->Text, fFunction.args[1]);
	//Just for console feedback
	std::cout
		<< "[AddKeyboardKey-log] Added:"
		<< fFunction.funcNameA
		<< " to frame: "
		<< (unsigned int)numUD_EditingFrame->Value
		<< " with args: "
		<< fFunction.args[0]
		<< " | "
		<< fFunction.args[1]
		<< std::endl;
	AddFunction(fFunction);
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::button_AddKeyboardSpecialKey_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (comboBox_KB_SpecialKey->Text == "" || comboBox_KB_InputType->Text == "") {
		MessageBoxA(nullptr, "Missing a few settings", "Error", MB_OK);
		return System::Void();
	}
	// add keyboard input button
	ScriptManager::FrameFunction fFunction;
	fFunction.funcNameA = "keyboard";
	fFunction.args.resize(2);
	MarshalString(comboBox_KB_SpecialKey->Text, fFunction.args[0]);
	MarshalString(comboBox_KB_InputType->Text, fFunction.args[1]);
	//Just for console feedback
	std::cout
		<< "[AddSpecialKeyboardKey-log] Added:"
		<< fFunction.funcNameA
		<< " to frame: "
		<< (unsigned int)numUD_EditingFrame->Value
		<< " with args: "
		<< fFunction.args[0]
		<< " | "
		<< fFunction.args[1]
		<< std::endl;
	AddFunction(fFunction);
	return System::Void();
}

/// <summary>
/// Takes a string with func name and args inside parenthesis and turns it into a ScriptManager::sfunction struct.
/// 
/// probably will be moved to the scriptmanager.h
/// </summary>
/// <param name="in"></param>
/// <returns></returns>
static ScriptManager::FrameFunction TransformStringIntoFunction(std::string in) {
	ScriptManager::FrameFunction f;
	if (in.at(0) == '!') { //if is a comment just add it to funcname
		f.funcNameA = in;
		return f;
	}
	size_t pS = in.find('(');
	size_t pE = in.find(')');
	if (pE != pS + 1) // if is a parenthesis right after the other there's no args in the list.
	{
		int j = 0;
		std::string _args;
		for (int i = pS + 1; i < in.size(); i++) {
			char c = in[i];
			if (c != ')') {
				if (c == ' ') {
					continue;
				}
				if (c == ',')
				{
					f.args.push_back(_args);
					_args.clear();
					j++;
					continue;
				}
				_args += c;
			}
			else
			{
				f.args.push_back(_args);
				break;
			}
		}
	}
	in.erase(in.begin() + pS, in.end());
	f.funcNameA = in;
	return f;
}

System::Void NotTAS::Window_ControlPainel::button_DeleteInput_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (listBox_EditingFrame->SelectedIndex > -1) {
		int i = (int)(listBox_EditingFrame->SelectedIndex);
		unsigned int frame = (unsigned int)numUD_EditingFrame->Value; // <- tongue possible crash, need more investigation.
		std::string selecteditemstr;
		MarshalString(listBox_EditingFrame->SelectedItem->ToString(), selecteditemstr);
		ScriptManager::FrameCall fCall;
		_sm.GetFunctionsFromFrame(frame, &fCall);
		ScriptManager::FrameFunction selectedFunction = TransformStringIntoFunction(selecteditemstr);
		std::cout << "[DeleteButton-log] trying to delete at: " << frame << "function translated:" << selectedFunction.funcNameA << std::endl;

		for (ScriptManager::FrameFunction i : fCall.calls)
		{
			std::cout << "[DeleteButton-log]" << selectedFunction.funcNameA << "?" << i.funcNameA << std::endl;
			std::cout << "[DeleteButton-log]" << selectedFunction.args.size() << "!" << i.args.size() << std::endl;
			if (selectedFunction.funcNameA == i.funcNameA && selectedFunction.args.size() == i.args.size())
			{
				std::cout << "[DeleteButton-log] found function" << std::endl;
				if (selectedFunction.args.size() > 0)
				{
					bool allMatch = true;
					for (int a = 0; a < i.args.size(); a++)
					{
						if (selectedFunction.args[a] != i.args[a])
						{
							allMatch = false;
							break;
						}
					}
					//if any argument don't match, then, this is not the function we want to delete. keep looking.
					if (!allMatch)
						continue;
				}

				if (_sm.RemoveFunctionFromframe(frame, i))
				{
					std::cout << "[DeleteButton-log] function deleted with sucess: " << frame << std::endl;
				}
				else
				{
					std::cout << ">> [DeleteButton-log] ERROR: could not delete input at: " << frame << std::endl;
				}
				break;

			}
		}
		UpdateCurrentEditingTextBoxes();
	}
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::comboBox_SelectFunction_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	//hide everything.
	groupBox_AddKeyboard->Visible = false;
	groupBox_AddMouse->Visible = false;
	groupBox_AddMoveMouse->Visible = false;
	groupBox_ShowGame->Visible = false;
	groupBox_SetFPS->Visible = false;
	groupBox_Stop->Visible = false;
	groupBox_WaitLoadStart->Visible = false;
	groupBox_WaitLoadEnd->Visible = false;
	groupBox_Comment->Visible = false;
	groupBox_AddScript->Visible = false;
	groupBox_AddWait->Visible = false;
	groupBox_AddMoveCursor->Visible = false;

	//show only the necessary.
	//i could use a switch here but c++ System::String switch is a pain, fuck it, just use a bunch of ifs. - Gordos
	if (comboBox_SelectFunction->Text == gcnew String("keyboard")) { groupBox_AddKeyboard->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("mouse")) { groupBox_AddMouse->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("movemouse")) { groupBox_AddMoveMouse->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("showgame")) { groupBox_ShowGame->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("setfps")) { groupBox_SetFPS->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("stop")) { groupBox_Stop->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("waitloadstart")) { groupBox_WaitLoadStart->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("waitloadend")) { groupBox_WaitLoadEnd->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("comment")) { groupBox_Comment->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("add script")) { groupBox_AddScript->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("wait")) { groupBox_AddWait->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("move cursor")) { groupBox_AddMoveCursor->Visible = true; }

	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::button_MClick_AddInput_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (comboBox_MClick_ButtonPress->Text == "" || comboBox_MClick_InputType->Text == "") {
		MessageBoxA(nullptr, "Missing a few settings", "Error", MB_OK);
		return System::Void();
	}
	// add Mouse input button
	ScriptManager::FrameFunction fFunction;
	fFunction.funcNameA = "mouse";
	fFunction.args.resize(2);
	MarshalString(comboBox_MClick_ButtonPress->Text, fFunction.args[0]);
	MarshalString(comboBox_MClick_InputType->Text, fFunction.args[1]);
	//Just for console feedback
	std::cout
		<< "[AddMouseClick-log] Added:"
		<< fFunction.funcNameA
		<< " to frame: "
		<< (unsigned int)numUD_EditingFrame->Value
		<< " with args: "
		<< fFunction.args[0]
		<< " | "
		<< fFunction.args[1]
		<< std::endl;
	AddFunction(fFunction);
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::button_AddMoveMouse_Click(System::Object^ sender, System::EventArgs^ e)
{
	//Add Move mouse

	ScriptManager::FrameFunction fFunction;
	fFunction.funcNameA = "movemouse";
	fFunction.args.resize(2);
	fFunction.args[0] = std::to_string((int)numericUD_MMove_X->Value);
	fFunction.args[1] = std::to_string((int)numericUD_MMove_Y->Value);
	//Just for console feedback
	std::cout
		<< "[AddMoveMouse-log] Added:"
		<< fFunction.funcNameA
		<< " to frame: "
		<< (unsigned int)numUD_EditingFrame->Value
		<< " with args: "
		<< fFunction.args[0]
		<< " | "
		<< fFunction.args[1]
		<< std::endl;
	AddFunction(fFunction);
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::button_AddShowGame_Click(System::Object^ sender, System::EventArgs^ e)
{
	//Add Show Game

	ScriptManager::FrameFunction fFunction;
	fFunction.funcNameA = "showgame";
	//Just for console feedback
	std::cout
		<< "[AddShowGame-log] Added:"
		<< fFunction.funcNameA
		<< " to frame: "
		<< (unsigned int)numUD_EditingFrame->Value
		<< std::endl;
	AddFunction(fFunction);
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::button_AddStop_Click(System::Object^ sender, System::EventArgs^ e)
{
	//Add Stop Tool function

	ScriptManager::FrameFunction fFunction;
	fFunction.funcNameA = "stop";
	//Just for console feedback
	std::cout
		<< "[AddStop-log] Added:"
		<< fFunction.funcNameA
		<< " to frame: "
		<< (unsigned int)numUD_EditingFrame->Value
		<< std::endl;
	AddFunction(fFunction);
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::button_AddWaitLoadStart_Click(System::Object^ sender, System::EventArgs^ e)
{
	//Add wait load start function

	ScriptManager::FrameFunction fFunction;
	fFunction.funcNameA = "waitloadstart";
	//Just for console feedback
	std::cout
		<< "[AddWaitLoad-Start-log] Added:"
		<< fFunction.funcNameA
		<< " to frame: "
		<< (unsigned int)numUD_EditingFrame->Value
		<< std::endl;
	AddFunction(fFunction);
	return System::Void();

}

System::Void NotTAS::Window_ControlPainel::button_AddWaitLoadEnd_Click(System::Object^ sender, System::EventArgs^ e)
{
	//Add wait load end function

	ScriptManager::FrameFunction fFunction;
	fFunction.funcNameA = "waitloadend";
	//Just for console feedback
	std::cout
		<< "[AddWaitLoad-End-log] Added:"
		<< fFunction.funcNameA
		<< " to frame: "
		<< (unsigned int)numUD_EditingFrame->Value
		<< std::endl;
	AddFunction(fFunction);
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::button_AddSetFPS_Click(System::Object^ sender, System::EventArgs^ e)
{
	// add Mouse input button
	ScriptManager::FrameFunction fFunction;
	fFunction.funcNameA = "setfps";
	fFunction.args.resize(1);
	MarshalString(numUD_SetFPS->Text, fFunction.args[0]);
	//Just for console feedback
	std::cout
		<< "[AddSetFPS-log] Added:"
		<< fFunction.funcNameA
		<< " to frame: "
		<< (unsigned int)numUD_EditingFrame->Value
		<< " with args: "
		<< fFunction.args[0]
		<< std::endl;
	AddFunction(fFunction);
	return System::Void();
}


System::Void NotTAS::Window_ControlPainel::button_File_Save_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string filename;
	MarshalString(textBox_File_Name->Text, filename);
	SettingsFileManager::QuickSaveText("LastSavedFile.txt", filename);
	filename += ".txt";
	if (_sm.SaveScript(filename.data())) {
		MessageBoxA(NULL, "File Saved", "Not TAS", MB_OK);
	}
	UpdateCurrentEditingTextBoxes();
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::button_File_Load_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (textBox_File_Name->Text == "") {
		MessageBoxA(nullptr, "Missing Name", "Error", MB_OK);
		return System::Void();
	}

	std::string scriptfilename;
	MarshalString(textBox_File_Name->Text, scriptfilename);
	_ml.ScriptName = scriptfilename + ".txt";
	_ml.LoadTASSCript();
	listBox_FramesNumber->SelectedIndex = -1;
	UpdateCurrentEditingTextBoxes();
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::button_AddComment_Click(System::Object^ sender, System::EventArgs^ e)
{
	// add Mouse input button
	ScriptManager::FrameFunction fFunction;
	MarshalString(textBox_Comment->Text, fFunction.funcNameA);
	fFunction.funcNameA = "! " + fFunction.funcNameA;
	//Just for console feedback
	std::cout
		<< "! Added:"
		<< fFunction.funcNameA
		<< " to frame: "
		<< (unsigned int)numUD_EditingFrame->Value
		<< std::endl;
	AddFunction(fFunction);
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::listBox_FramesNumber_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (listBox_FramesNumber->SelectedIndex > -1 && !UIIsUpdating) {
		std::string a;
		MarshalString(listBox_FramesNumber->Text, a);
		numUD_EditingFrame->Value = std::stoi(a);
		UpdateCurrentEditingTextBoxes();
	}

	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::comboBox_KB_SpecialKey_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::button_AddScript_Click(System::Object^ sender, System::EventArgs^ e)
{
	// Merge script from another file into the current frames.

	button_AddScript->Enabled = false;
	if (System::String::IsNullOrWhiteSpace(textBox_AddScript->Text)) {
		MessageBoxA(NULL, "please fill the textbar with something valid", "ERROR", MB_OK);
		button_AddScript->Enabled = true;
		return System::Void();
	}
	String^ finText = textBox_AddScript->Text + ".txt";
	std::string fileLoc;
	MarshalString(finText, fileLoc);
	_sm.LoadAndAddScriptToFrame((char*)fileLoc.c_str(), (unsigned int)numUD_EditingFrame->Value);
	button_AddScript->Enabled = true;
	UpdateCurrentEditingTextBoxes();
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::button_AddWait_Click(System::Object^ sender, System::EventArgs^ e)
{
	ScriptManager::FrameFunction fFunction;
	fFunction.funcNameA = "wait";
	fFunction.args.resize(1);
	MarshalString(numUD_AddWait->Value.ToString(), fFunction.args[0]);
	//Just for console feedback
	std::cout
		<< "[AddWait-log] Added:"
		<< fFunction.funcNameA
		<< " to frame: "
		<< (unsigned int)numUD_EditingFrame->Value
		<< std::endl;
	AddFunction(fFunction);
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::button_AddMoveCursor_Click(System::Object^ sender, System::EventArgs^ e)
{
	ScriptManager::FrameFunction fFunction;
	fFunction.funcNameA = "movecursor";
	fFunction.args.resize(2);
	MarshalString(numUD_MoveCursor_X->Value.ToString(), fFunction.args[0]);
	MarshalString(numUD_MoveCursor_Y->Value.ToString(), fFunction.args[1]);
	std::cout
		<< "[AddMoveCursor-log] Added:"
		<< fFunction.funcNameA
		<< " to frame: "
		<< (unsigned int)numUD_EditingFrame->Value
		<< std::endl;
	AddFunction(fFunction);
	return System::Void();
}


System::Void NotTAS::Window_ControlPainel::textBox_KB_Key_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	cli::array<wchar_t>^ b = textBox_KB_Key->Text->ToCharArray();
	if (b->LongLength <= 0)
		return System::Void();
	System::String^ a = b[0].ToString();
	textBox_KB_Key->Text = a;
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::numUD_EditingFrame_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	UpdateCurrentEditingTextBoxes();
}