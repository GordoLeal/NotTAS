#pragma once

namespace NotTAS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Window_Editor
	/// </summary>
	public ref class Window_Editor : public System::Windows::Forms::Form
	{
	public:
		Window_Editor(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Window_Editor()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::ComboBox^ CB_InsertInput;


	private: System::Windows::Forms::GroupBox^ GroupBox_Keyboard;

	private: System::Windows::Forms::CheckBox^ checkbox_keyboardspecial;
	private: System::Windows::Forms::ComboBox^ comboBox_PressTypeKeyboard;

	private: System::Windows::Forms::ComboBox^ comboBox_KeyboardSpecialKey;
	private: System::Windows::Forms::Button^ button_AddInputKeyboard;
	private: System::Windows::Forms::TextBox^ textbox_keybordKey;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::GroupBox^ insertInput;
			System::Windows::Forms::Label^ keyboardkeylabel;
			System::Windows::Forms::Label^ presstypelabel;
			this->GroupBox_Keyboard = (gcnew System::Windows::Forms::GroupBox());
			this->button_AddInputKeyboard = (gcnew System::Windows::Forms::Button());
			this->textbox_keybordKey = (gcnew System::Windows::Forms::TextBox());
			this->comboBox_PressTypeKeyboard = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_KeyboardSpecialKey = (gcnew System::Windows::Forms::ComboBox());
			this->checkbox_keyboardspecial = (gcnew System::Windows::Forms::CheckBox());
			this->CB_InsertInput = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			insertInput = (gcnew System::Windows::Forms::GroupBox());
			keyboardkeylabel = (gcnew System::Windows::Forms::Label());
			presstypelabel = (gcnew System::Windows::Forms::Label());
			insertInput->SuspendLayout();
			this->GroupBox_Keyboard->SuspendLayout();
			this->SuspendLayout();
			// 
			// insertInput
			// 
			insertInput->Controls->Add(this->GroupBox_Keyboard);
			insertInput->Controls->Add(this->CB_InsertInput);
			insertInput->Location = System::Drawing::Point(12, 12);
			insertInput->Name = L"insertInput";
			insertInput->Size = System::Drawing::Size(357, 280);
			insertInput->TabIndex = 2;
			insertInput->TabStop = false;
			insertInput->Text = L"Insert Input";
			// 
			// GroupBox_Keyboard
			// 
			this->GroupBox_Keyboard->Controls->Add(keyboardkeylabel);
			this->GroupBox_Keyboard->Controls->Add(this->button_AddInputKeyboard);
			this->GroupBox_Keyboard->Controls->Add(this->textbox_keybordKey);
			this->GroupBox_Keyboard->Controls->Add(presstypelabel);
			this->GroupBox_Keyboard->Controls->Add(this->comboBox_PressTypeKeyboard);
			this->GroupBox_Keyboard->Controls->Add(this->comboBox_KeyboardSpecialKey);
			this->GroupBox_Keyboard->Controls->Add(this->checkbox_keyboardspecial);
			this->GroupBox_Keyboard->Location = System::Drawing::Point(20, 71);
			this->GroupBox_Keyboard->Name = L"GroupBox_Keyboard";
			this->GroupBox_Keyboard->Size = System::Drawing::Size(310, 189);
			this->GroupBox_Keyboard->TabIndex = 1;
			this->GroupBox_Keyboard->TabStop = false;
			this->GroupBox_Keyboard->Text = L"Keyboard";
			// 
			// keyboardkeylabel
			// 
			keyboardkeylabel->AutoSize = true;
			keyboardkeylabel->Location = System::Drawing::Point(118, 23);
			keyboardkeylabel->Name = L"keyboardkeylabel";
			keyboardkeylabel->Size = System::Drawing::Size(27, 13);
			keyboardkeylabel->TabIndex = 6;
			keyboardkeylabel->Text = L"key:";
			// 
			// button_AddInputKeyboard
			// 
			this->button_AddInputKeyboard->Location = System::Drawing::Point(85, 136);
			this->button_AddInputKeyboard->Name = L"button_AddInputKeyboard";
			this->button_AddInputKeyboard->Size = System::Drawing::Size(116, 23);
			this->button_AddInputKeyboard->TabIndex = 5;
			this->button_AddInputKeyboard->Text = L"Add keyboard input";
			this->button_AddInputKeyboard->UseVisualStyleBackColor = true;
			this->button_AddInputKeyboard->Click += gcnew System::EventHandler(this, &Window_Editor::button_AddInputKeyboard_Click);
			// 
			// textbox_keybordKey
			// 
			this->textbox_keybordKey->Location = System::Drawing::Point(151, 20);
			this->textbox_keybordKey->Name = L"textbox_keybordKey";
			this->textbox_keybordKey->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textbox_keybordKey->Size = System::Drawing::Size(121, 20);
			this->textbox_keybordKey->TabIndex = 4;
			this->textbox_keybordKey->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// presstypelabel
			// 
			presstypelabel->AutoSize = true;
			presstypelabel->Location = System::Drawing::Point(82, 76);
			presstypelabel->Name = L"presstypelabel";
			presstypelabel->Size = System::Drawing::Size(63, 13);
			presstypelabel->TabIndex = 3;
			presstypelabel->Text = L"Press Type:";
			// 
			// comboBox_PressTypeKeyboard
			// 
			this->comboBox_PressTypeKeyboard->FormattingEnabled = true;
			this->comboBox_PressTypeKeyboard->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"pm_keydown", L"pm_keyup", L"si_keydown",
					L"si_keyup"
			});
			this->comboBox_PressTypeKeyboard->Location = System::Drawing::Point(151, 73);
			this->comboBox_PressTypeKeyboard->Name = L"comboBox_PressTypeKeyboard";
			this->comboBox_PressTypeKeyboard->Size = System::Drawing::Size(121, 21);
			this->comboBox_PressTypeKeyboard->TabIndex = 2;
			// 
			// comboBox_KeyboardSpecialKey
			// 
			this->comboBox_KeyboardSpecialKey->Enabled = false;
			this->comboBox_KeyboardSpecialKey->FormattingEnabled = true;
			this->comboBox_KeyboardSpecialKey->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"space", L"esc", L"backspace",
					L"enter", L"leftctrl", L"leftshift", L"rightctrl", L"rightshift"
			});
			this->comboBox_KeyboardSpecialKey->Location = System::Drawing::Point(151, 46);
			this->comboBox_KeyboardSpecialKey->Name = L"comboBox_KeyboardSpecialKey";
			this->comboBox_KeyboardSpecialKey->Size = System::Drawing::Size(121, 21);
			this->comboBox_KeyboardSpecialKey->TabIndex = 1;
			this->comboBox_KeyboardSpecialKey->Text = L"press type";
			this->comboBox_KeyboardSpecialKey->SelectedIndexChanged += gcnew System::EventHandler(this, &Window_Editor::comboBox_KeyboardSpecialKey_SelectedIndexChanged);
			// 
			// checkbox_keyboardspecial
			// 
			this->checkbox_keyboardspecial->AutoSize = true;
			this->checkbox_keyboardspecial->Location = System::Drawing::Point(41, 48);
			this->checkbox_keyboardspecial->Name = L"checkbox_keyboardspecial";
			this->checkbox_keyboardspecial->Size = System::Drawing::Size(104, 17);
			this->checkbox_keyboardspecial->TabIndex = 0;
			this->checkbox_keyboardspecial->Text = L"Use Special Key";
			this->checkbox_keyboardspecial->UseVisualStyleBackColor = true;
			this->checkbox_keyboardspecial->CheckedChanged += gcnew System::EventHandler(this, &Window_Editor::checkbox_keyboardspecial_CheckedChanged);
			// 
			// CB_InsertInput
			// 
			this->CB_InsertInput->FormattingEnabled = true;
			this->CB_InsertInput->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"keyboard", L"mouse", L"movemouse", L"stop",
					L"setfps", L"showgame", L"waitloadstart", L"waitloadend"
			});
			this->CB_InsertInput->Location = System::Drawing::Point(20, 30);
			this->CB_InsertInput->Name = L"CB_InsertInput";
			this->CB_InsertInput->Size = System::Drawing::Size(121, 21);
			this->CB_InsertInput->TabIndex = 0;
			this->CB_InsertInput->Text = L"type";
			this->CB_InsertInput->SelectedIndexChanged += gcnew System::EventHandler(this, &Window_Editor::CB_InsertInput_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(485, 289);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(18) {
				L"teste 1", L"teste 2", L"teste 3", L"teste 46",
					L"teste 45", L"teste 45", L"teste 439", L"teste 434", L"teste 48", L"teste 46t", L"teste 47", L"teste 456", L"teste 4t 4", L"teste 43",
					L"teste 42", L"teste 4teste 4", L"teste 4teste 4", L"teste 44"
			});
			this->listBox1->Location = System::Drawing::Point(375, 47);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(297, 225);
			this->listBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(466, 28);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(36, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"frame:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label2->Location = System::Drawing::Point(508, 29);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(15, 15);
			this->label2->TabIndex = 4;
			this->label2->Text = L"0";
			// 
			// Window_Editor
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(698, 330);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(insertInput);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->button1);
			this->Name = L"Window_Editor";
			this->Text = L"Window_Editor";
			insertInput->ResumeLayout(false);
			this->GroupBox_Keyboard->ResumeLayout(false);
			this->GroupBox_Keyboard->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void comboBox_KeyboardSpecialKey_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void CB_InsertInput_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
private: System::Void checkbox_keyboardspecial_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_AddInputKeyboard_Click(System::Object^ sender, System::EventArgs^ e);
};
}
