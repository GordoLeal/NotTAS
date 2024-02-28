#include "Window_ControlPainel.h"
using namespace NotTAS;

// For some reason  i don't know. even if is referencing the same static pointer, multiple calls to 
// a instance can consume some few bytes of memory every call, to fix this call the instance once at the start of the .cpp and let the compiler deal with it.
// seems to have solved the problem.
ScriptManager& _sm = ScriptManager::GetInstance();
MainLogic& _ml = MainLogic::GetInstance();

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
	//ScriptManager& sm = ScriptManager::GetInstance();
	if (_sm.AddFunctionToFrame((unsigned int)numUD_EditingFrame->Value, fFunction)) {
		std::cout << "[1] AddFunction: + " << fFunction.funcNameA << " to frame: " << (unsigned int)numUD_EditingFrame->Value << std::endl;
	}
	UpdateCurrentEditingFrameTextbox();
}

void Window_ControlPainel::UpdateCurrentEditingFrameTextbox() {
	listBox_EditingFrame->Items->Clear();
	//ScriptManager& sm = ScriptManager::GetInstance();
	ScriptManager::FrameCall frCalls;
	_sm.GetFunctionsFromFrame((unsigned int)numUD_EditingFrame->Value, &frCalls);
	for (ScriptManager::FrameFunction i : frCalls.calls) {
		std::string buf = (char*)"";
		if (i.funcNameA.at(0) == '!') {
			buf += i.funcNameA;
			listBox_EditingFrame->Items->Add(gcnew String(buf.data()));
			continue;
		}
		buf += i.funcNameA + "(";
		std::cout << "[log] UpdateCurrentEditingFrame:(" << i.funcNameA << ") have: (" << i.args.size() << ") args." << std::endl;
		for (int j = 0; j < i.args.size(); j++) {
			if (i.args[j].size() <= 0) {
				std::cout << "[!] UpdateCurrentEditingFrame:" << i.funcNameA << " don't have value in arg:" << j << std::endl;
				continue;
			}
			buf += i.args[j];
			std::cout << "[log] UpdateCurrentEditingFrame:(" << i.funcNameA << ") adding arg: (" << i.args[j] << ") at:" << j << std::endl;
			if (j + 1 < i.args.size())
				if (i.args[j + 1].length() > 0) {
					buf += ",";
				}
		}
		buf += ")";
		listBox_EditingFrame->Items->Add(gcnew String(buf.data()));
	}

	//Frames List

	listBox_FramesNumber->Items->Clear();
	std::vector<unsigned int> i;
	_sm.GetFramesNumberList(&i);
	if (i.size() > 0) {
		sort(i.begin(), i.end());
		for (unsigned int a : i) {
			listBox_FramesNumber->Items->Add(a);
		}
	}

}

System::Void NotTAS::Window_ControlPainel::Button_StartSystem_Click(System::Object^ sender, System::EventArgs^ e)
{
	//// Play button
	//if (_ml.ScriptName.empty() || _ml.ScriptName == "") {
	//	std::cout << ">> [StartSystem-log] ERROR: scriptname is empty, please load a file." << std::endl;
	//	return;
	//}

	if (!_ml.IsRunning()) {
		std::cout << "[StartSystem-log] Starting..." << std::endl;
		std::cout << _ml.ScriptName << std::endl;
		_ml.startingFrame = (int)numeric_StartFromFrame->Value;
		_ml.ExecuteScript();
		bWorker->RunWorkerAsync();
	}
	else
	{
		std::cout << "[StartSystem-log] Stopping..." << std::endl;
		_ml.StopExecution();
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
		bWorker->ReportProgress(1);
		if (!_ml.IsRunning()) {
			bWorker->CancelAsync();
		}
		System::Threading::Thread::Sleep(100);
	}
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::bWorker_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e)
{
	Button_StartSystem->Text = _ml.IsRunning() ? gcnew String("Stop") : gcnew String("Play");
	return System::Void();
}

System::Void NotTAS::Window_ControlPainel::bWorker_WorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
{
	//Background worker completed
	Button_StartSystem->Text = gcnew String("Play");
	return System::Void();
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
		<< "! Added:"
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
		std::cout << "[log] End Delete"<< std::endl;
		UpdateCurrentEditingFrameTextbox();
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

	//show only the necessary.
	//i could use a switch here but c++ System::String switch is a pain, fuck it, just use a bunch of if... - Gordos
	if (comboBox_SelectFunction->Text == gcnew String("keyboard")) { groupBox_AddKeyboard->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("mouse")) { groupBox_AddMouse->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("movemouse")) { groupBox_AddMoveMouse->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("showgame")) { groupBox_ShowGame->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("setfps")) { groupBox_SetFPS->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("stop")) { groupBox_Stop->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("waitloadstart")) { groupBox_WaitLoadStart->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("waitloadend")) { groupBox_WaitLoadEnd->Visible = true; }
	if (comboBox_SelectFunction->Text == gcnew String("comment")) { groupBox_Comment->Visible = true; }

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
		<< "! Added:"
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
	fFunction.funcNameA = "mouse";
	fFunction.args.resize(2);
	fFunction.args[0] = std::to_string((int)numericUD_MMove_X->Value);
	fFunction.args[1] = std::to_string((int)numericUD_MMove_Y->Value);
	//Just for console feedback
	std::cout
		<< "! Added:"
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
		<< "! Added:"
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
		<< "! Added:"
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
		<< "! Added:"
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
		<< "! Added:"
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
		<< "! Added:"
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
	filename += ".txt";
	//TODO: ui
	if (_sm.SaveScript(filename.data())) {
		MessageBoxA(NULL, "File Saved", "Not TAS", MB_OK);
	}
	UpdateCurrentEditingFrameTextbox();
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
	UpdateCurrentEditingFrameTextbox();
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
	if (listBox_FramesNumber->SelectedValue != NULL) {
		std::string a;
		MarshalString(listBox_FramesNumber->Text, a);
		numUD_EditingFrame->Value = std::stoi(a);
		UpdateCurrentEditingFrameTextbox();
	}

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
	UpdateCurrentEditingFrameTextbox();
}