#include <iostream>
#include "Forms/Window_ControlPainel.h"
//#include <Windows.h>
//#include "MainWindow.h"
using namespace System::Windows::Forms;
using namespace NotTAS;

int main() {

	Window_ControlPainel cp;
	Application::EnableVisualStyles();
	Application::Run(%cp);
	//bool KeepLooping = true;
	//MainWindow* mWindow = new MainWindow();
	/*while (KeepLooping) {
		if (mWindow->IsApplicationCloseRequest()) {
			KeepLooping = false;
		}
	}*/
	//delete mWindow;
	return 0;
}
