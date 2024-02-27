#pragma once

namespace NotTAS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Window_Settings
	/// </summary>
	public ref class Window_Settings : public System::Windows::Forms::Form
	{
	public:
		Window_Settings(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Window_Settings()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::TextBox^ textBox_AppExe;
	private: System::Windows::Forms::TextBox^ textBox_AppWindowName;
	private: System::Windows::Forms::Button^ button_SaveExit;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::Label^ label1;
			System::Windows::Forms::Label^ label2;
			this->textBox_AppExe = (gcnew System::Windows::Forms::TextBox());
			this->textBox_AppWindowName = (gcnew System::Windows::Forms::TextBox());
			this->button_SaveExit = (gcnew System::Windows::Forms::Button());
			label1 = (gcnew System::Windows::Forms::Label());
			label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			label1->AutoSize = true;
			label1->Location = System::Drawing::Point(9, 13);
			label1->Name = L"label1";
			label1->Size = System::Drawing::Size(80, 13);
			label1->TabIndex = 0;
			label1->Text = L"Application Exe";
			// 
			// label2
			// 
			label2->AutoSize = true;
			label2->Location = System::Drawing::Point(12, 62);
			label2->Name = L"label2";
			label2->Size = System::Drawing::Size(77, 13);
			label2->TabIndex = 2;
			label2->Text = L"Window Name";
			// 
			// textBox_AppExe
			// 
			this->textBox_AppExe->Location = System::Drawing::Point(12, 29);
			this->textBox_AppExe->Name = L"textBox_AppExe";
			this->textBox_AppExe->ReadOnly = true;
			this->textBox_AppExe->Size = System::Drawing::Size(325, 20);
			this->textBox_AppExe->TabIndex = 1;
			this->textBox_AppExe->Text = L"Pineapple-Win64-Shipping.exe";
			// 
			// textBox_AppWindowName
			// 
			this->textBox_AppWindowName->Location = System::Drawing::Point(12, 78);
			this->textBox_AppWindowName->Name = L"textBox_AppWindowName";
			this->textBox_AppWindowName->ReadOnly = true;
			this->textBox_AppWindowName->Size = System::Drawing::Size(325, 20);
			this->textBox_AppWindowName->TabIndex = 3;
			this->textBox_AppWindowName->Text = L"SpongeBob";
			// 
			// button_SaveExit
			// 
			this->button_SaveExit->Location = System::Drawing::Point(239, 113);
			this->button_SaveExit->Name = L"button_SaveExit";
			this->button_SaveExit->Size = System::Drawing::Size(98, 23);
			this->button_SaveExit->TabIndex = 5;
			this->button_SaveExit->Text = L"Save Settings";
			this->button_SaveExit->UseVisualStyleBackColor = true;
			this->button_SaveExit->Click += gcnew System::EventHandler(this, &Window_Settings::button_SaveExit_Click);
			// 
			// Window_Settings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(349, 150);
			this->Controls->Add(this->button_SaveExit);
			this->Controls->Add(this->textBox_AppWindowName);
			this->Controls->Add(label2);
			this->Controls->Add(this->textBox_AppExe);
			this->Controls->Add(label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Window_Settings";
			this->Text = L"Not Tas - Settings";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void checkBox_StartOnDetect_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_SaveExit_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox_ScriptPath_TextChanged(System::Object^ sender, System::EventArgs^ e);
	};
}
