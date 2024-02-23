#include "Window_Editor.h"
#include <iostream>

using namespace System;
System::Void NotTAS::Window_Editor::CB_InsertInput_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	String^ selected = (String^)CB_InsertInput->SelectedItem;
	GroupBox_Keyboard->Visible = false;
	String^ compar = gcnew String("keyboard");
	if (selected == compar) {
		GroupBox_Keyboard->Visible = true;
	}
	return System::Void();
}

System::Void NotTAS::Window_Editor::checkbox_keyboardspecial_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	bool check = checkbox_keyboardspecial->Checked;
	comboBox_KeyboardSpecialKey->Enabled = check;
	textbox_keybordKey->Enabled = !check;
	//comboBox_KeyboardSpecialKey->CanSelect = CheckBox_keyboard
	return System::Void();
}

System::Void NotTAS::Window_Editor::button_AddInputKeyboard_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}
