#include <iostream>
#include <Windows.h>
#include "ScriptManager.h"
#include "MainWindow.h"

using namespace std;

int main() {
	////
	//cout << "reading..." << endl;
	//ScriptManager loader;
	//loader.LoadScript("D:\\Projetos Visual Studio\\GordoTAS\\x64\\Debug\\teste.txt");
	//vector<FrameCall> frames = loader.GetVectorFrameCalls();
	//for (FrameCall f : frames)
	//{
	//	cout << "call: " << f.call << " number: " << f.frame << endl;
	//	for (size_t i = 0; i < 5; i++)
	//	{
	//		cout << "args: " <<i <<" : " << f.args[i] << endl;
	//	}
	//};
	
	cout << "done..." << endl;

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
