#ifndef MAINWINDOW_H
#define MAINWINDOW_H

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class MainWindow
{
public: 
	MainWindow();
	bool IsApplicationCloseRequest();
private:
	bool IsQuitRequest = false;
};
#endif // !MAINWINDOW_H 

