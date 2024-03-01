#pragma once
#include <Windows.h>
#include <iostream>
#include "Window_Settings.h"
#include "..\MainLogic.h"
namespace NotTAS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Window_ControlPainel
	/// </summary>
	public ref class Window_ControlPainel : public System::Windows::Forms::Form
	{
	public:
		Window_ControlPainel(void)
		{
			InitializeComponent();
			Window_Settings^ settings = gcnew Window_Settings;
			settings->ShowDialog();
			UpdateCurrentEditingFrameTextbox();
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Window_ControlPainel()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ groupBox_AddMouse;
	protected:
	private: System::Windows::Forms::ComboBox^ comboBox_MClick_InputType;
	private: System::Windows::Forms::Button^ button_MClick_AddInput;
	private: System::Windows::Forms::ComboBox^ comboBox_MClick_ButtonPress;
	private: System::Windows::Forms::GroupBox^ groupBox_AddMoveMouse;
	private: System::Windows::Forms::NumericUpDown^ numericUD_MMove_Y;
	private: System::Windows::Forms::NumericUpDown^ numericUD_MMove_X;
	private: System::Windows::Forms::Button^ button_AddMoveMouse;
	private: System::Windows::Forms::GroupBox^ groupBox_ShowGame;
	private: System::Windows::Forms::Button^ button_AddShowGame;
	private: System::Windows::Forms::GroupBox^ groupBox_Stop;
	private: System::Windows::Forms::Button^ button_AddStop;
	private: System::Windows::Forms::GroupBox^ groupBox_WaitLoadStart;
	private: System::Windows::Forms::Button^ button_AddWaitLoadStart;
	private: System::Windows::Forms::GroupBox^ groupBox_WaitLoadEnd;
	private: System::Windows::Forms::Button^ button_AddWaitLoadEnd;
	private: System::Windows::Forms::GroupBox^ groupBox_SetFPS;
	private: System::Windows::Forms::NumericUpDown^ numUD_SetFPS;
	private: System::Windows::Forms::Button^ button_AddSetFPS;
	private: System::Windows::Forms::TextBox^ textBox_File_Name;
	private: System::Windows::Forms::Button^ button_File_Load;
	private: System::Windows::Forms::Button^ button_File_Save;
	private: System::Windows::Forms::GroupBox^ groupBox_Comment;
	private: System::Windows::Forms::Button^ button_AddComment;
	private: System::Windows::Forms::TextBox^ textBox_Comment;
	private: System::Windows::Forms::ListBox^ listBox_FramesNumber;
	private:
		bool IsRunning = false;
		void UpdateCurrentEditingFrameTextbox();
		void AddFunction(ScriptManager::FrameFunction);
	private: System::Windows::Forms::Button^ Button_OpenSettings;
	public: System::Windows::Forms::Button^ Button_StartSystem;
	private: System::Windows::Forms::CheckBox^ checkBox_StartOnGameDetect;
	private: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::Windows::Forms::NumericUpDown^ numeric_StartFromFrame;
	private: System::ComponentModel::BackgroundWorker^ bWorker;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button_DeleteInput;
	private: System::Windows::Forms::ComboBox^ comboBox_SelectFunction;
	private: System::Windows::Forms::NumericUpDown^ numUD_EditingFrame;
	private: System::Windows::Forms::GroupBox^ groupBox_AddKeyboard;
	private: System::Windows::Forms::ComboBox^ comboBox_KB_InputType;
	private: System::Windows::Forms::Button^ button_AddKeyboardSpecialKey;
	private: System::Windows::Forms::Button^ button_AddKeyboardKey;
	private: System::Windows::Forms::TextBox^ textBox_KB_Key;
	private: System::Windows::Forms::ComboBox^ comboBox_KB_SpecialKey;
	private: System::Windows::Forms::ListBox^ listBox_EditingFrame;
	private: System::ComponentModel::IContainer^ components;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::Label^ Label_StartFromFrame;
			System::Windows::Forms::GroupBox^ groupBox_AddInput;
			System::Windows::Forms::Label^ label7;
			System::Windows::Forms::Label^ label6;
			System::Windows::Forms::Label^ label5;
			System::Windows::Forms::Label^ label4;
			System::Windows::Forms::Label^ label3;
			System::Windows::Forms::Label^ label_MClick_Button;
			System::Windows::Forms::Label^ label_MClick_InputType;
			System::Windows::Forms::Label^ label2;
			System::Windows::Forms::GroupBox^ groupBox_SaveLoadFile;
			System::Windows::Forms::Label^ label_txt;
			System::Windows::Forms::Label^ label8;
			System::Windows::Forms::GroupBox^ groupBox_InputsList;
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Window_ControlPainel::typeid));
			this->groupBox_AddMoveMouse = (gcnew System::Windows::Forms::GroupBox());
			this->button_AddMoveMouse = (gcnew System::Windows::Forms::Button());
			this->numericUD_MMove_Y = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUD_MMove_X = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox_AddKeyboard = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox_KB_InputType = (gcnew System::Windows::Forms::ComboBox());
			this->button_AddKeyboardSpecialKey = (gcnew System::Windows::Forms::Button());
			this->button_AddKeyboardKey = (gcnew System::Windows::Forms::Button());
			this->textBox_KB_Key = (gcnew System::Windows::Forms::TextBox());
			this->comboBox_KB_SpecialKey = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox_Comment = (gcnew System::Windows::Forms::GroupBox());
			this->button_AddComment = (gcnew System::Windows::Forms::Button());
			this->textBox_Comment = (gcnew System::Windows::Forms::TextBox());
			this->groupBox_SetFPS = (gcnew System::Windows::Forms::GroupBox());
			this->numUD_SetFPS = (gcnew System::Windows::Forms::NumericUpDown());
			this->button_AddSetFPS = (gcnew System::Windows::Forms::Button());
			this->groupBox_WaitLoadEnd = (gcnew System::Windows::Forms::GroupBox());
			this->button_AddWaitLoadEnd = (gcnew System::Windows::Forms::Button());
			this->groupBox_WaitLoadStart = (gcnew System::Windows::Forms::GroupBox());
			this->button_AddWaitLoadStart = (gcnew System::Windows::Forms::Button());
			this->groupBox_Stop = (gcnew System::Windows::Forms::GroupBox());
			this->button_AddStop = (gcnew System::Windows::Forms::Button());
			this->groupBox_ShowGame = (gcnew System::Windows::Forms::GroupBox());
			this->button_AddShowGame = (gcnew System::Windows::Forms::Button());
			this->groupBox_AddMouse = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox_MClick_InputType = (gcnew System::Windows::Forms::ComboBox());
			this->button_MClick_AddInput = (gcnew System::Windows::Forms::Button());
			this->comboBox_MClick_ButtonPress = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_SelectFunction = (gcnew System::Windows::Forms::ComboBox());
			this->button_File_Load = (gcnew System::Windows::Forms::Button());
			this->button_File_Save = (gcnew System::Windows::Forms::Button());
			this->textBox_File_Name = (gcnew System::Windows::Forms::TextBox());
			this->listBox_FramesNumber = (gcnew System::Windows::Forms::ListBox());
			this->button_DeleteInput = (gcnew System::Windows::Forms::Button());
			this->listBox_EditingFrame = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->numUD_EditingFrame = (gcnew System::Windows::Forms::NumericUpDown());
			this->Button_OpenSettings = (gcnew System::Windows::Forms::Button());
			this->Button_StartSystem = (gcnew System::Windows::Forms::Button());
			this->checkBox_StartOnGameDetect = (gcnew System::Windows::Forms::CheckBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->numeric_StartFromFrame = (gcnew System::Windows::Forms::NumericUpDown());
			this->bWorker = (gcnew System::ComponentModel::BackgroundWorker());
			Label_StartFromFrame = (gcnew System::Windows::Forms::Label());
			groupBox_AddInput = (gcnew System::Windows::Forms::GroupBox());
			label7 = (gcnew System::Windows::Forms::Label());
			label6 = (gcnew System::Windows::Forms::Label());
			label5 = (gcnew System::Windows::Forms::Label());
			label4 = (gcnew System::Windows::Forms::Label());
			label3 = (gcnew System::Windows::Forms::Label());
			label_MClick_Button = (gcnew System::Windows::Forms::Label());
			label_MClick_InputType = (gcnew System::Windows::Forms::Label());
			label2 = (gcnew System::Windows::Forms::Label());
			groupBox_SaveLoadFile = (gcnew System::Windows::Forms::GroupBox());
			label_txt = (gcnew System::Windows::Forms::Label());
			label8 = (gcnew System::Windows::Forms::Label());
			groupBox_InputsList = (gcnew System::Windows::Forms::GroupBox());
			groupBox_AddInput->SuspendLayout();
			this->groupBox_AddMoveMouse->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUD_MMove_Y))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUD_MMove_X))->BeginInit();
			this->groupBox_AddKeyboard->SuspendLayout();
			this->groupBox_Comment->SuspendLayout();
			this->groupBox_SetFPS->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_SetFPS))->BeginInit();
			this->groupBox_WaitLoadEnd->SuspendLayout();
			this->groupBox_WaitLoadStart->SuspendLayout();
			this->groupBox_Stop->SuspendLayout();
			this->groupBox_ShowGame->SuspendLayout();
			this->groupBox_AddMouse->SuspendLayout();
			groupBox_SaveLoadFile->SuspendLayout();
			groupBox_InputsList->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_EditingFrame))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numeric_StartFromFrame))->BeginInit();
			this->SuspendLayout();
			// 
			// Label_StartFromFrame
			// 
			Label_StartFromFrame->AutoSize = true;
			Label_StartFromFrame->Location = System::Drawing::Point(501, 358);
			Label_StartFromFrame->Name = L"Label_StartFromFrame";
			Label_StartFromFrame->Size = System::Drawing::Size(90, 13);
			Label_StartFromFrame->TabIndex = 9;
			Label_StartFromFrame->Text = L"Start From Frame:";
			// 
			// groupBox_AddInput
			// 
			groupBox_AddInput->Controls->Add(this->groupBox_AddMoveMouse);
			groupBox_AddInput->Controls->Add(this->groupBox_AddKeyboard);
			groupBox_AddInput->Controls->Add(this->groupBox_Comment);
			groupBox_AddInput->Controls->Add(this->groupBox_SetFPS);
			groupBox_AddInput->Controls->Add(this->groupBox_WaitLoadEnd);
			groupBox_AddInput->Controls->Add(this->groupBox_WaitLoadStart);
			groupBox_AddInput->Controls->Add(this->groupBox_Stop);
			groupBox_AddInput->Controls->Add(this->groupBox_ShowGame);
			groupBox_AddInput->Controls->Add(this->groupBox_AddMouse);
			groupBox_AddInput->Controls->Add(label2);
			groupBox_AddInput->Controls->Add(this->comboBox_SelectFunction);
			groupBox_AddInput->Location = System::Drawing::Point(12, 12);
			groupBox_AddInput->Name = L"groupBox_AddInput";
			groupBox_AddInput->Size = System::Drawing::Size(299, 277);
			groupBox_AddInput->TabIndex = 12;
			groupBox_AddInput->TabStop = false;
			groupBox_AddInput->Text = L"Add Input";
			// 
			// groupBox_AddMoveMouse
			// 
			this->groupBox_AddMoveMouse->Controls->Add(this->button_AddMoveMouse);
			this->groupBox_AddMoveMouse->Controls->Add(label7);
			this->groupBox_AddMoveMouse->Controls->Add(label6);
			this->groupBox_AddMoveMouse->Controls->Add(this->numericUD_MMove_Y);
			this->groupBox_AddMoveMouse->Controls->Add(this->numericUD_MMove_X);
			this->groupBox_AddMoveMouse->Location = System::Drawing::Point(25, 62);
			this->groupBox_AddMoveMouse->Name = L"groupBox_AddMoveMouse";
			this->groupBox_AddMoveMouse->Size = System::Drawing::Size(247, 196);
			this->groupBox_AddMoveMouse->TabIndex = 4;
			this->groupBox_AddMoveMouse->TabStop = false;
			this->groupBox_AddMoveMouse->Text = L"Move Mouse";
			this->groupBox_AddMoveMouse->Visible = false;
			// 
			// button_AddMoveMouse
			// 
			this->button_AddMoveMouse->Location = System::Drawing::Point(71, 123);
			this->button_AddMoveMouse->Name = L"button_AddMoveMouse";
			this->button_AddMoveMouse->Size = System::Drawing::Size(120, 23);
			this->button_AddMoveMouse->TabIndex = 4;
			this->button_AddMoveMouse->Text = L"Add Move Mouse";
			this->button_AddMoveMouse->UseVisualStyleBackColor = true;
			this->button_AddMoveMouse->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_AddMoveMouse_Click);
			// 
			// label7
			// 
			label7->AutoSize = true;
			label7->Location = System::Drawing::Point(12, 68);
			label7->Name = L"label7";
			label7->Size = System::Drawing::Size(64, 13);
			label7->TabIndex = 3;
			label7->Text = L"Y ( Vertical )";
			// 
			// label6
			// 
			label6->AutoSize = true;
			label6->Location = System::Drawing::Point(7, 42);
			label6->Name = L"label6";
			label6->Size = System::Drawing::Size(76, 13);
			label6->TabIndex = 2;
			label6->Text = L"X ( Horizontal )";
			// 
			// numericUD_MMove_Y
			// 
			this->numericUD_MMove_Y->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->numericUD_MMove_Y->Location = System::Drawing::Point(84, 67);
			this->numericUD_MMove_Y->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32500, 0, 0, 0 });
			this->numericUD_MMove_Y->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32500, 0, 0, System::Int32::MinValue });
			this->numericUD_MMove_Y->Name = L"numericUD_MMove_Y";
			this->numericUD_MMove_Y->Size = System::Drawing::Size(120, 20);
			this->numericUD_MMove_Y->TabIndex = 1;
			// 
			// numericUD_MMove_X
			// 
			this->numericUD_MMove_X->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->numericUD_MMove_X->Location = System::Drawing::Point(84, 39);
			this->numericUD_MMove_X->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32500, 0, 0, 0 });
			this->numericUD_MMove_X->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 32500, 0, 0, System::Int32::MinValue });
			this->numericUD_MMove_X->Name = L"numericUD_MMove_X";
			this->numericUD_MMove_X->Size = System::Drawing::Size(120, 20);
			this->numericUD_MMove_X->TabIndex = 0;
			// 
			// groupBox_AddKeyboard
			// 
			this->groupBox_AddKeyboard->Controls->Add(this->comboBox_KB_InputType);
			this->groupBox_AddKeyboard->Controls->Add(label5);
			this->groupBox_AddKeyboard->Controls->Add(this->button_AddKeyboardSpecialKey);
			this->groupBox_AddKeyboard->Controls->Add(this->button_AddKeyboardKey);
			this->groupBox_AddKeyboard->Controls->Add(this->textBox_KB_Key);
			this->groupBox_AddKeyboard->Controls->Add(label4);
			this->groupBox_AddKeyboard->Controls->Add(label3);
			this->groupBox_AddKeyboard->Controls->Add(this->comboBox_KB_SpecialKey);
			this->groupBox_AddKeyboard->Location = System::Drawing::Point(25, 62);
			this->groupBox_AddKeyboard->Name = L"groupBox_AddKeyboard";
			this->groupBox_AddKeyboard->Size = System::Drawing::Size(253, 202);
			this->groupBox_AddKeyboard->TabIndex = 2;
			this->groupBox_AddKeyboard->TabStop = false;
			this->groupBox_AddKeyboard->Text = L"Keyboard";
			this->groupBox_AddKeyboard->Visible = false;
			// 
			// comboBox_KB_InputType
			// 
			this->comboBox_KB_InputType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_KB_InputType->FormattingEnabled = true;
			this->comboBox_KB_InputType->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"pm_keydown", L"pm_keyup", L"si_keydown",
					L"si_keyup"
			});
			this->comboBox_KB_InputType->Location = System::Drawing::Point(84, 86);
			this->comboBox_KB_InputType->Name = L"comboBox_KB_InputType";
			this->comboBox_KB_InputType->Size = System::Drawing::Size(121, 21);
			this->comboBox_KB_InputType->TabIndex = 7;
			// 
			// label5
			// 
			label5->AutoSize = true;
			label5->Location = System::Drawing::Point(17, 89);
			label5->Name = L"label5";
			label5->Size = System::Drawing::Size(61, 13);
			label5->TabIndex = 6;
			label5->Text = L"Input Type:";
			// 
			// button_AddKeyboardSpecialKey
			// 
			this->button_AddKeyboardSpecialKey->Location = System::Drawing::Point(104, 144);
			this->button_AddKeyboardSpecialKey->Name = L"button_AddKeyboardSpecialKey";
			this->button_AddKeyboardSpecialKey->Size = System::Drawing::Size(101, 23);
			this->button_AddKeyboardSpecialKey->TabIndex = 5;
			this->button_AddKeyboardSpecialKey->Text = L"Add Special Key";
			this->button_AddKeyboardSpecialKey->UseVisualStyleBackColor = true;
			this->button_AddKeyboardSpecialKey->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_AddKeyboardSpecialKey_Click);
			// 
			// button_AddKeyboardKey
			// 
			this->button_AddKeyboardKey->Location = System::Drawing::Point(20, 144);
			this->button_AddKeyboardKey->Name = L"button_AddKeyboardKey";
			this->button_AddKeyboardKey->Size = System::Drawing::Size(75, 23);
			this->button_AddKeyboardKey->TabIndex = 4;
			this->button_AddKeyboardKey->Text = L"Add Key";
			this->button_AddKeyboardKey->UseVisualStyleBackColor = true;
			this->button_AddKeyboardKey->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_AddKeyboardKey_Click);
			// 
			// textBox_KB_Key
			// 
			this->textBox_KB_Key->Location = System::Drawing::Point(84, 61);
			this->textBox_KB_Key->Name = L"textBox_KB_Key";
			this->textBox_KB_Key->Size = System::Drawing::Size(56, 20);
			this->textBox_KB_Key->TabIndex = 3;
			this->textBox_KB_Key->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox_KB_Key->TextChanged += gcnew System::EventHandler(this, &Window_ControlPainel::textBox_KB_Key_TextChanged);
			// 
			// label4
			// 
			label4->AutoSize = true;
			label4->Location = System::Drawing::Point(50, 64);
			label4->Name = L"label4";
			label4->Size = System::Drawing::Size(28, 13);
			label4->TabIndex = 2;
			label4->Text = L"Key:";
			// 
			// label3
			// 
			label3->AutoSize = true;
			label3->Location = System::Drawing::Point(12, 37);
			label3->Name = L"label3";
			label3->Size = System::Drawing::Size(66, 13);
			label3->TabIndex = 1;
			label3->Text = L"Special Key:";
			// 
			// comboBox_KB_SpecialKey
			// 
			this->comboBox_KB_SpecialKey->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_KB_SpecialKey->FormattingEnabled = true;
			this->comboBox_KB_SpecialKey->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"backspace", L"leftctrl", L"leftshift",
					L"rightctrl", L"rightshift", L"space", L"esc", L"enter"
			});
			this->comboBox_KB_SpecialKey->Location = System::Drawing::Point(84, 34);
			this->comboBox_KB_SpecialKey->Name = L"comboBox_KB_SpecialKey";
			this->comboBox_KB_SpecialKey->Size = System::Drawing::Size(121, 21);
			this->comboBox_KB_SpecialKey->TabIndex = 0;
			this->comboBox_KB_SpecialKey->SelectedIndexChanged += gcnew System::EventHandler(this, &Window_ControlPainel::comboBox_KB_SpecialKey_SelectedIndexChanged);
			// 
			// groupBox_Comment
			// 
			this->groupBox_Comment->Controls->Add(this->button_AddComment);
			this->groupBox_Comment->Controls->Add(this->textBox_Comment);
			this->groupBox_Comment->Location = System::Drawing::Point(18, 56);
			this->groupBox_Comment->Name = L"groupBox_Comment";
			this->groupBox_Comment->Size = System::Drawing::Size(260, 208);
			this->groupBox_Comment->TabIndex = 10;
			this->groupBox_Comment->TabStop = false;
			this->groupBox_Comment->Text = L"Comment";
			this->groupBox_Comment->Visible = false;
			// 
			// button_AddComment
			// 
			this->button_AddComment->Location = System::Drawing::Point(69, 104);
			this->button_AddComment->Name = L"button_AddComment";
			this->button_AddComment->Size = System::Drawing::Size(111, 23);
			this->button_AddComment->TabIndex = 1;
			this->button_AddComment->Text = L"Add Comment";
			this->button_AddComment->UseVisualStyleBackColor = true;
			this->button_AddComment->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_AddComment_Click);
			// 
			// textBox_Comment
			// 
			this->textBox_Comment->Location = System::Drawing::Point(17, 57);
			this->textBox_Comment->Name = L"textBox_Comment";
			this->textBox_Comment->Size = System::Drawing::Size(231, 20);
			this->textBox_Comment->TabIndex = 0;
			// 
			// groupBox_SetFPS
			// 
			this->groupBox_SetFPS->Controls->Add(this->numUD_SetFPS);
			this->groupBox_SetFPS->Controls->Add(this->button_AddSetFPS);
			this->groupBox_SetFPS->Location = System::Drawing::Point(25, 56);
			this->groupBox_SetFPS->Name = L"groupBox_SetFPS";
			this->groupBox_SetFPS->Size = System::Drawing::Size(253, 202);
			this->groupBox_SetFPS->TabIndex = 9;
			this->groupBox_SetFPS->TabStop = false;
			this->groupBox_SetFPS->Text = L"SetFPS";
			this->groupBox_SetFPS->Visible = false;
			// 
			// numUD_SetFPS
			// 
			this->numUD_SetFPS->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->numUD_SetFPS->Location = System::Drawing::Point(62, 45);
			this->numUD_SetFPS->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->numUD_SetFPS->Name = L"numUD_SetFPS";
			this->numUD_SetFPS->Size = System::Drawing::Size(120, 20);
			this->numUD_SetFPS->TabIndex = 1;
			this->numUD_SetFPS->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			// 
			// button_AddSetFPS
			// 
			this->button_AddSetFPS->Location = System::Drawing::Point(62, 90);
			this->button_AddSetFPS->Name = L"button_AddSetFPS";
			this->button_AddSetFPS->Size = System::Drawing::Size(119, 23);
			this->button_AddSetFPS->TabIndex = 0;
			this->button_AddSetFPS->Text = L"Add SetFPS";
			this->button_AddSetFPS->UseVisualStyleBackColor = true;
			this->button_AddSetFPS->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_AddSetFPS_Click);
			// 
			// groupBox_WaitLoadEnd
			// 
			this->groupBox_WaitLoadEnd->Controls->Add(this->button_AddWaitLoadEnd);
			this->groupBox_WaitLoadEnd->Location = System::Drawing::Point(25, 56);
			this->groupBox_WaitLoadEnd->Name = L"groupBox_WaitLoadEnd";
			this->groupBox_WaitLoadEnd->Size = System::Drawing::Size(253, 202);
			this->groupBox_WaitLoadEnd->TabIndex = 8;
			this->groupBox_WaitLoadEnd->TabStop = false;
			this->groupBox_WaitLoadEnd->Text = L"WaitLoadEnd";
			this->groupBox_WaitLoadEnd->Visible = false;
			// 
			// button_AddWaitLoadEnd
			// 
			this->button_AddWaitLoadEnd->Location = System::Drawing::Point(62, 90);
			this->button_AddWaitLoadEnd->Name = L"button_AddWaitLoadEnd";
			this->button_AddWaitLoadEnd->Size = System::Drawing::Size(119, 23);
			this->button_AddWaitLoadEnd->TabIndex = 0;
			this->button_AddWaitLoadEnd->Text = L"Add Wait Load End";
			this->button_AddWaitLoadEnd->UseVisualStyleBackColor = true;
			this->button_AddWaitLoadEnd->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_AddWaitLoadEnd_Click);
			// 
			// groupBox_WaitLoadStart
			// 
			this->groupBox_WaitLoadStart->Controls->Add(this->button_AddWaitLoadStart);
			this->groupBox_WaitLoadStart->Location = System::Drawing::Point(25, 62);
			this->groupBox_WaitLoadStart->Name = L"groupBox_WaitLoadStart";
			this->groupBox_WaitLoadStart->Size = System::Drawing::Size(253, 202);
			this->groupBox_WaitLoadStart->TabIndex = 7;
			this->groupBox_WaitLoadStart->TabStop = false;
			this->groupBox_WaitLoadStart->Text = L"WaitLoadStart";
			this->groupBox_WaitLoadStart->Visible = false;
			// 
			// button_AddWaitLoadStart
			// 
			this->button_AddWaitLoadStart->Location = System::Drawing::Point(62, 90);
			this->button_AddWaitLoadStart->Name = L"button_AddWaitLoadStart";
			this->button_AddWaitLoadStart->Size = System::Drawing::Size(119, 23);
			this->button_AddWaitLoadStart->TabIndex = 0;
			this->button_AddWaitLoadStart->Text = L"Add Wait Load Start";
			this->button_AddWaitLoadStart->UseVisualStyleBackColor = true;
			this->button_AddWaitLoadStart->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_AddWaitLoadStart_Click);
			// 
			// groupBox_Stop
			// 
			this->groupBox_Stop->Controls->Add(this->button_AddStop);
			this->groupBox_Stop->Location = System::Drawing::Point(25, 62);
			this->groupBox_Stop->Name = L"groupBox_Stop";
			this->groupBox_Stop->Size = System::Drawing::Size(253, 202);
			this->groupBox_Stop->TabIndex = 6;
			this->groupBox_Stop->TabStop = false;
			this->groupBox_Stop->Text = L"Stop";
			this->groupBox_Stop->Visible = false;
			// 
			// button_AddStop
			// 
			this->button_AddStop->Location = System::Drawing::Point(80, 94);
			this->button_AddStop->Name = L"button_AddStop";
			this->button_AddStop->Size = System::Drawing::Size(101, 23);
			this->button_AddStop->TabIndex = 0;
			this->button_AddStop->Text = L"Add Stop";
			this->button_AddStop->UseVisualStyleBackColor = true;
			this->button_AddStop->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_AddStop_Click);
			// 
			// groupBox_ShowGame
			// 
			this->groupBox_ShowGame->Controls->Add(this->button_AddShowGame);
			this->groupBox_ShowGame->Location = System::Drawing::Point(25, 62);
			this->groupBox_ShowGame->Name = L"groupBox_ShowGame";
			this->groupBox_ShowGame->Size = System::Drawing::Size(253, 202);
			this->groupBox_ShowGame->TabIndex = 5;
			this->groupBox_ShowGame->TabStop = false;
			this->groupBox_ShowGame->Text = L"Show Game";
			this->groupBox_ShowGame->Visible = false;
			// 
			// button_AddShowGame
			// 
			this->button_AddShowGame->Location = System::Drawing::Point(62, 94);
			this->button_AddShowGame->Name = L"button_AddShowGame";
			this->button_AddShowGame->Size = System::Drawing::Size(119, 23);
			this->button_AddShowGame->TabIndex = 0;
			this->button_AddShowGame->Text = L"Add Show Game";
			this->button_AddShowGame->UseVisualStyleBackColor = true;
			this->button_AddShowGame->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_AddShowGame_Click);
			// 
			// groupBox_AddMouse
			// 
			this->groupBox_AddMouse->Controls->Add(label_MClick_Button);
			this->groupBox_AddMouse->Controls->Add(label_MClick_InputType);
			this->groupBox_AddMouse->Controls->Add(this->comboBox_MClick_InputType);
			this->groupBox_AddMouse->Controls->Add(this->button_MClick_AddInput);
			this->groupBox_AddMouse->Controls->Add(this->comboBox_MClick_ButtonPress);
			this->groupBox_AddMouse->Location = System::Drawing::Point(25, 62);
			this->groupBox_AddMouse->Name = L"groupBox_AddMouse";
			this->groupBox_AddMouse->Size = System::Drawing::Size(216, 168);
			this->groupBox_AddMouse->TabIndex = 3;
			this->groupBox_AddMouse->TabStop = false;
			this->groupBox_AddMouse->Text = L"Mouse";
			this->groupBox_AddMouse->Visible = false;
			// 
			// label_MClick_Button
			// 
			label_MClick_Button->AutoSize = true;
			label_MClick_Button->Location = System::Drawing::Point(27, 47);
			label_MClick_Button->Name = L"label_MClick_Button";
			label_MClick_Button->Size = System::Drawing::Size(41, 13);
			label_MClick_Button->TabIndex = 10;
			label_MClick_Button->Text = L"Button:";
			// 
			// label_MClick_InputType
			// 
			label_MClick_InputType->AutoSize = true;
			label_MClick_InputType->Location = System::Drawing::Point(7, 74);
			label_MClick_InputType->Name = L"label_MClick_InputType";
			label_MClick_InputType->Size = System::Drawing::Size(61, 13);
			label_MClick_InputType->TabIndex = 9;
			label_MClick_InputType->Text = L"Input Type:";
			// 
			// comboBox_MClick_InputType
			// 
			this->comboBox_MClick_InputType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_MClick_InputType->FormattingEnabled = true;
			this->comboBox_MClick_InputType->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"pm_keydown", L"pm_keyup", L"si_keydown",
					L"si_keyup"
			});
			this->comboBox_MClick_InputType->Location = System::Drawing::Point(71, 71);
			this->comboBox_MClick_InputType->Name = L"comboBox_MClick_InputType";
			this->comboBox_MClick_InputType->Size = System::Drawing::Size(121, 21);
			this->comboBox_MClick_InputType->TabIndex = 8;
			// 
			// button_MClick_AddInput
			// 
			this->button_MClick_AddInput->Location = System::Drawing::Point(71, 123);
			this->button_MClick_AddInput->Name = L"button_MClick_AddInput";
			this->button_MClick_AddInput->Size = System::Drawing::Size(75, 23);
			this->button_MClick_AddInput->TabIndex = 1;
			this->button_MClick_AddInput->Text = L"Add Input";
			this->button_MClick_AddInput->UseVisualStyleBackColor = true;
			this->button_MClick_AddInput->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_MClick_AddInput_Click);
			// 
			// comboBox_MClick_ButtonPress
			// 
			this->comboBox_MClick_ButtonPress->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_MClick_ButtonPress->FormattingEnabled = true;
			this->comboBox_MClick_ButtonPress->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"left", L"right", L"middle" });
			this->comboBox_MClick_ButtonPress->Location = System::Drawing::Point(71, 44);
			this->comboBox_MClick_ButtonPress->Name = L"comboBox_MClick_ButtonPress";
			this->comboBox_MClick_ButtonPress->Size = System::Drawing::Size(121, 21);
			this->comboBox_MClick_ButtonPress->TabIndex = 0;
			// 
			// label2
			// 
			label2->AutoSize = true;
			label2->Location = System::Drawing::Point(7, 23);
			label2->Name = L"label2";
			label2->Size = System::Drawing::Size(51, 13);
			label2->TabIndex = 1;
			label2->Text = L"Function:";
			// 
			// comboBox_SelectFunction
			// 
			this->comboBox_SelectFunction->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_SelectFunction->FormattingEnabled = true;
			this->comboBox_SelectFunction->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				L"keyboard", L"mouse", L"movemouse",
					L"showgame", L"setfps", L"stop", L"waitloadstart", L"waitloadend", L"comment"
			});
			this->comboBox_SelectFunction->Location = System::Drawing::Point(64, 20);
			this->comboBox_SelectFunction->Name = L"comboBox_SelectFunction";
			this->comboBox_SelectFunction->Size = System::Drawing::Size(121, 21);
			this->comboBox_SelectFunction->TabIndex = 0;
			this->comboBox_SelectFunction->SelectedIndexChanged += gcnew System::EventHandler(this, &Window_ControlPainel::comboBox_SelectFunction_SelectedIndexChanged);
			// 
			// groupBox_SaveLoadFile
			// 
			groupBox_SaveLoadFile->Controls->Add(label_txt);
			groupBox_SaveLoadFile->Controls->Add(label8);
			groupBox_SaveLoadFile->Controls->Add(this->button_File_Load);
			groupBox_SaveLoadFile->Controls->Add(this->button_File_Save);
			groupBox_SaveLoadFile->Controls->Add(this->textBox_File_Name);
			groupBox_SaveLoadFile->Location = System::Drawing::Point(11, 295);
			groupBox_SaveLoadFile->Name = L"groupBox_SaveLoadFile";
			groupBox_SaveLoadFile->Size = System::Drawing::Size(300, 81);
			groupBox_SaveLoadFile->TabIndex = 19;
			groupBox_SaveLoadFile->TabStop = false;
			groupBox_SaveLoadFile->Text = L"Save / Load";
			// 
			// label_txt
			// 
			label_txt->AutoSize = true;
			label_txt->Location = System::Drawing::Point(223, 22);
			label_txt->Name = L"label_txt";
			label_txt->Size = System::Drawing::Size(21, 13);
			label_txt->TabIndex = 20;
			label_txt->Text = L".txt";
			// 
			// label8
			// 
			label8->AutoSize = true;
			label8->Location = System::Drawing::Point(26, 22);
			label8->Name = L"label8";
			label8->Size = System::Drawing::Size(68, 13);
			label8->TabIndex = 21;
			label8->Text = L"Script Name:";
			label8->UseMnemonic = false;
			// 
			// button_File_Load
			// 
			this->button_File_Load->Location = System::Drawing::Point(100, 50);
			this->button_File_Load->Name = L"button_File_Load";
			this->button_File_Load->Size = System::Drawing::Size(75, 23);
			this->button_File_Load->TabIndex = 20;
			this->button_File_Load->Text = L"Load";
			this->button_File_Load->UseVisualStyleBackColor = true;
			this->button_File_Load->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_File_Load_Click);
			// 
			// button_File_Save
			// 
			this->button_File_Save->Location = System::Drawing::Point(19, 50);
			this->button_File_Save->Name = L"button_File_Save";
			this->button_File_Save->Size = System::Drawing::Size(75, 23);
			this->button_File_Save->TabIndex = 19;
			this->button_File_Save->Text = L"Save";
			this->button_File_Save->UseVisualStyleBackColor = true;
			this->button_File_Save->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_File_Save_Click);
			// 
			// textBox_File_Name
			// 
			this->textBox_File_Name->Location = System::Drawing::Point(97, 19);
			this->textBox_File_Name->MaxLength = 50;
			this->textBox_File_Name->Name = L"textBox_File_Name";
			this->textBox_File_Name->Size = System::Drawing::Size(120, 20);
			this->textBox_File_Name->TabIndex = 18;
			this->textBox_File_Name->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// groupBox_InputsList
			// 
			groupBox_InputsList->Controls->Add(this->listBox_FramesNumber);
			groupBox_InputsList->Controls->Add(this->button_DeleteInput);
			groupBox_InputsList->Controls->Add(this->listBox_EditingFrame);
			groupBox_InputsList->Controls->Add(this->label1);
			groupBox_InputsList->Controls->Add(this->numUD_EditingFrame);
			groupBox_InputsList->Location = System::Drawing::Point(318, 12);
			groupBox_InputsList->Name = L"groupBox_InputsList";
			groupBox_InputsList->Size = System::Drawing::Size(475, 277);
			groupBox_InputsList->TabIndex = 17;
			groupBox_InputsList->TabStop = false;
			groupBox_InputsList->Text = L"Inputs List";
			// 
			// listBox_FramesNumber
			// 
			this->listBox_FramesNumber->FormattingEnabled = true;
			this->listBox_FramesNumber->Location = System::Drawing::Point(369, 33);
			this->listBox_FramesNumber->Name = L"listBox_FramesNumber";
			this->listBox_FramesNumber->Size = System::Drawing::Size(76, 186);
			this->listBox_FramesNumber->TabIndex = 18;
			this->listBox_FramesNumber->SelectedIndexChanged += gcnew System::EventHandler(this, &Window_ControlPainel::listBox_FramesNumber_SelectedIndexChanged);
			// 
			// button_DeleteInput
			// 
			this->button_DeleteInput->Location = System::Drawing::Point(93, 235);
			this->button_DeleteInput->Name = L"button_DeleteInput";
			this->button_DeleteInput->Size = System::Drawing::Size(75, 23);
			this->button_DeleteInput->TabIndex = 15;
			this->button_DeleteInput->Text = L"Delete Input";
			this->button_DeleteInput->UseVisualStyleBackColor = true;
			this->button_DeleteInput->Click += gcnew System::EventHandler(this, &Window_ControlPainel::button_DeleteInput_Click);
			// 
			// listBox_EditingFrame
			// 
			this->listBox_EditingFrame->FormattingEnabled = true;
			this->listBox_EditingFrame->Location = System::Drawing::Point(18, 33);
			this->listBox_EditingFrame->Name = L"listBox_EditingFrame";
			this->listBox_EditingFrame->Size = System::Drawing::Size(345, 186);
			this->listBox_EditingFrame->TabIndex = 17;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(174, 240);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(39, 13);
			this->label1->TabIndex = 14;
			this->label1->Text = L"Frame:";
			// 
			// numUD_EditingFrame
			// 
			this->numUD_EditingFrame->Location = System::Drawing::Point(219, 238);
			this->numUD_EditingFrame->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { -1, 0, 0, 0 });
			this->numUD_EditingFrame->Name = L"numUD_EditingFrame";
			this->numUD_EditingFrame->Size = System::Drawing::Size(120, 20);
			this->numUD_EditingFrame->TabIndex = 16;
			this->numUD_EditingFrame->ValueChanged += gcnew System::EventHandler(this, &Window_ControlPainel::numUD_EditingFrame_ValueChanged);
			// 
			// Button_OpenSettings
			// 
			this->Button_OpenSettings->Location = System::Drawing::Point(411, 353);
			this->Button_OpenSettings->Name = L"Button_OpenSettings";
			this->Button_OpenSettings->Size = System::Drawing::Size(83, 23);
			this->Button_OpenSettings->TabIndex = 0;
			this->Button_OpenSettings->Text = L"Settings";
			this->Button_OpenSettings->UseVisualStyleBackColor = true;
			this->Button_OpenSettings->Click += gcnew System::EventHandler(this, &Window_ControlPainel::Button_OpenSettings_Click);
			// 
			// Button_StartSystem
			// 
			this->Button_StartSystem->Location = System::Drawing::Point(694, 353);
			this->Button_StartSystem->Name = L"Button_StartSystem";
			this->Button_StartSystem->Size = System::Drawing::Size(83, 23);
			this->Button_StartSystem->TabIndex = 2;
			this->Button_StartSystem->Text = L"Play";
			this->Button_StartSystem->UseVisualStyleBackColor = true;
			this->Button_StartSystem->Click += gcnew System::EventHandler(this, &Window_ControlPainel::Button_StartSystem_Click);
			// 
			// checkBox_StartOnGameDetect
			// 
			this->checkBox_StartOnGameDetect->AutoSize = true;
			this->checkBox_StartOnGameDetect->Enabled = false;
			this->checkBox_StartOnGameDetect->Location = System::Drawing::Point(656, 333);
			this->checkBox_StartOnGameDetect->Name = L"checkBox_StartOnGameDetect";
			this->checkBox_StartOnGameDetect->Size = System::Drawing::Size(131, 17);
			this->checkBox_StartOnGameDetect->TabIndex = 10;
			this->checkBox_StartOnGameDetect->Text = L"Start On Game Detect";
			this->toolTip1->SetToolTip(this->checkBox_StartOnGameDetect, L"After pressing \"Play\" the tool will wait for the game window to be open to start "
				L"sending inputs.");
			this->checkBox_StartOnGameDetect->UseVisualStyleBackColor = true;
			// 
			// numeric_StartFromFrame
			// 
			this->numeric_StartFromFrame->Location = System::Drawing::Point(596, 356);
			this->numeric_StartFromFrame->Name = L"numeric_StartFromFrame";
			this->numeric_StartFromFrame->Size = System::Drawing::Size(92, 20);
			this->numeric_StartFromFrame->TabIndex = 11;
			this->numeric_StartFromFrame->ValueChanged += gcnew System::EventHandler(this, &Window_ControlPainel::numeric_StartFromFrame_ValueChanged);
			// 
			// bWorker
			// 
			this->bWorker->WorkerReportsProgress = true;
			this->bWorker->WorkerSupportsCancellation = true;
			this->bWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Window_ControlPainel::bWorker_DoWork);
			this->bWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Window_ControlPainel::bWorker_ProgressChanged);
			this->bWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Window_ControlPainel::bWorker_WorkerCompleted);
			// 
			// Window_ControlPainel
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(805, 386);
			this->Controls->Add(groupBox_SaveLoadFile);
			this->Controls->Add(groupBox_InputsList);
			this->Controls->Add(groupBox_AddInput);
			this->Controls->Add(this->numeric_StartFromFrame);
			this->Controls->Add(this->checkBox_StartOnGameDetect);
			this->Controls->Add(Label_StartFromFrame);
			this->Controls->Add(this->Button_StartSystem);
			this->Controls->Add(this->Button_OpenSettings);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->Name = L"Window_ControlPainel";
			this->Text = L"Not TAS";
			groupBox_AddInput->ResumeLayout(false);
			groupBox_AddInput->PerformLayout();
			this->groupBox_AddMoveMouse->ResumeLayout(false);
			this->groupBox_AddMoveMouse->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUD_MMove_Y))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUD_MMove_X))->EndInit();
			this->groupBox_AddKeyboard->ResumeLayout(false);
			this->groupBox_AddKeyboard->PerformLayout();
			this->groupBox_Comment->ResumeLayout(false);
			this->groupBox_Comment->PerformLayout();
			this->groupBox_SetFPS->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_SetFPS))->EndInit();
			this->groupBox_WaitLoadEnd->ResumeLayout(false);
			this->groupBox_WaitLoadStart->ResumeLayout(false);
			this->groupBox_Stop->ResumeLayout(false);
			this->groupBox_ShowGame->ResumeLayout(false);
			this->groupBox_AddMouse->ResumeLayout(false);
			this->groupBox_AddMouse->PerformLayout();
			groupBox_SaveLoadFile->ResumeLayout(false);
			groupBox_SaveLoadFile->PerformLayout();
			groupBox_InputsList->ResumeLayout(false);
			groupBox_InputsList->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_EditingFrame))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numeric_StartFromFrame))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Button_StartSystem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Button_OpenSettings_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void numeric_StartFromFrame_ValueChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void bWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: System::Void bWorker_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e);
	private: System::Void bWorker_WorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e);
	private: System::Void button_AddKeyboardKey_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox_KB_Key_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void numUD_EditingFrame_ValueChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_AddKeyboardSpecialKey_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_DeleteInput_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void comboBox_SelectFunction_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_MClick_AddInput_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_AddMoveMouse_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_AddShowGame_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_AddStop_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_AddWaitLoadStart_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_AddWaitLoadEnd_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_AddSetFPS_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_File_Save_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_File_Load_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_AddComment_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void listBox_FramesNumber_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void comboBox_KB_SpecialKey_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
};
}
