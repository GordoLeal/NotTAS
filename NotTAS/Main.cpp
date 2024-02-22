#include <iostream>
#include <Windows.h>
#include "MainWindow.h"

using namespace std;

int main() {
	bool KeepLooping = true;
	MainWindow* mWindow = new MainWindow();
	while (KeepLooping) {
		if (mWindow->IsApplicationCloseRequest()) {
			KeepLooping = false;
		}
	}
	delete mWindow;
	return 0;
}
