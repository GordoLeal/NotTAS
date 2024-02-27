#include <iostream>
#include "Forms/Window_ControlPainel.h"
//#include <Windows.h>
//#include "MainWindow.h"
using namespace System::Windows::Forms;
using namespace NotTAS;

int main() {
	MainLogic::GetInstance().InitialSetup();
	Window_ControlPainel cp;
	Application::EnableVisualStyles();
	Application::Run(%cp);
	return 0;
}
