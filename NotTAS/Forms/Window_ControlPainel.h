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
			MainLogic::GetInstance().InitialSetup();
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
	private:
		bool IsRunning = false;
	private: System::Windows::Forms::Button^ Button_OpenSettings;
	private: System::Windows::Forms::Button^ Button_OpenEditor;
	public: System::Windows::Forms::Button^ Button_StartSystem;
	private: System::Windows::Forms::CheckBox^ checkBox_StartOnGameDetect;
	public:
	private:




	private: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::Windows::Forms::NumericUpDown^ numeric_StartFromFrame;
	private: System::ComponentModel::BackgroundWorker^ bWorker;


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
			this->Button_OpenSettings = (gcnew System::Windows::Forms::Button());
			this->Button_OpenEditor = (gcnew System::Windows::Forms::Button());
			this->Button_StartSystem = (gcnew System::Windows::Forms::Button());
			this->checkBox_StartOnGameDetect = (gcnew System::Windows::Forms::CheckBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->numeric_StartFromFrame = (gcnew System::Windows::Forms::NumericUpDown());
			this->bWorker = (gcnew System::ComponentModel::BackgroundWorker());
			Label_StartFromFrame = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numeric_StartFromFrame))->BeginInit();
			this->SuspendLayout();
			// 
			// Label_StartFromFrame
			// 
			Label_StartFromFrame->AutoSize = true;
			Label_StartFromFrame->Location = System::Drawing::Point(5, 23);
			Label_StartFromFrame->Name = L"Label_StartFromFrame";
			Label_StartFromFrame->Size = System::Drawing::Size(90, 13);
			Label_StartFromFrame->TabIndex = 9;
			Label_StartFromFrame->Text = L"Start From Frame:";
			// 
			// Button_OpenSettings
			// 
			this->Button_OpenSettings->Location = System::Drawing::Point(227, 15);
			this->Button_OpenSettings->Name = L"Button_OpenSettings";
			this->Button_OpenSettings->Size = System::Drawing::Size(83, 23);
			this->Button_OpenSettings->TabIndex = 0;
			this->Button_OpenSettings->Text = L"Settings";
			this->Button_OpenSettings->UseVisualStyleBackColor = true;
			this->Button_OpenSettings->Click += gcnew System::EventHandler(this, &Window_ControlPainel::Button_OpenSettings_Click);
			// 
			// Button_OpenEditor
			// 
			this->Button_OpenEditor->Location = System::Drawing::Point(327, 15);
			this->Button_OpenEditor->Name = L"Button_OpenEditor";
			this->Button_OpenEditor->Size = System::Drawing::Size(83, 23);
			this->Button_OpenEditor->TabIndex = 1;
			this->Button_OpenEditor->Text = L"Editor";
			this->Button_OpenEditor->UseVisualStyleBackColor = true;
			this->Button_OpenEditor->Click += gcnew System::EventHandler(this, &Window_ControlPainel::Button_OpenEditor_Click);
			// 
			// Button_StartSystem
			// 
			this->Button_StartSystem->Location = System::Drawing::Point(327, 83);
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
			this->checkBox_StartOnGameDetect->Location = System::Drawing::Point(190, 87);
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
			this->numeric_StartFromFrame->Location = System::Drawing::Point(101, 21);
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
			this->ClientSize = System::Drawing::Size(435, 118);
			this->Controls->Add(this->numeric_StartFromFrame);
			this->Controls->Add(this->checkBox_StartOnGameDetect);
			this->Controls->Add(Label_StartFromFrame);
			this->Controls->Add(this->Button_StartSystem);
			this->Controls->Add(this->Button_OpenEditor);
			this->Controls->Add(this->Button_OpenSettings);
			this->MaximizeBox = false;
			this->Name = L"Window_ControlPainel";
			this->Text = L"Window_ControlPainel";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numeric_StartFromFrame))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Button_OpenEditor_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Button_StartSystem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Button_OpenSettings_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void numeric_StartFromFrame_ValueChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void bWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: System::Void bWorker_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e);
	private: System::Void bWorker_WorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e);
	};
}
