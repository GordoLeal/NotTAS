#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <iostream>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>
#include <future>

/// <summary>
/// responsable for holding the information about the process and functions that send inputs.
/// </summary>
class InputManager
{

public:
	enum MouseInputs {
		LeftRight = 0x01,
		RightClick = 0x02,
		MiddleClick = 0x04,
		errM
	};

	enum SpecialKeyboardInputs {
		Backspace = 0x08,
		Space = 0x20,
		LeftShift= 0xA0,
		RightShift = 0xA1,
		LeftCtrl = 0xA2,
		RightCtrl = 0xA3,
		Esc = 0x1B,
		errSK
	};


	enum HardwareTypes {
		Keyboard = 0,
		Mouse = 1,
		errH
	};

	// Post Message Structs
	enum KeyEvents
	{
		PM_KeyDown = WM_KEYDOWN,
		PM_KeyUp = WM_KEYUP,
		SI_KeyDown = 0x0000, // KEYEVENTF_KEYDOWN = basically 0 | NULL
		SI_KeyUp = KEYEVENTF_KEYUP,
		PM_MoveMouse = WM_MOUSEMOVE,
		SI_MoveMouse = MOUSEEVENTF_MOVE,
		err
	};
	
	struct InputStruct
	{
		KeyEvents keyevent;
		int dirX, dirY;
		HardwareTypes hardware;
		char key;
		INPUT siInput;
	};

	std::vector<InputStruct> inputsVector;
	static InputManager& GetInstance() {
		// We only need one call to this class, so making it a singleton would help reduce code.
		static InputManager instance;
		return instance;
	}

	// --- --- --- SCRIPT LOGIC FUNCTIONS --- --- ---
	//Anything created here needs to have an interpreter in (FuncInterpreter.h/.cpp) so we can translate any output from Scriptmanager args as parameters for the function.

	static void AddKeyboardInput(char key, KeyEvents inEvent);
	static void AddSpecialKeyboardInput(SpecialKeyboardInputs key, KeyEvents inEvent);
	static void AddMouseInput(MouseInputs key, KeyEvents inEvent);
	static void AddMouseMoveInput(int x, int y, InputManager::KeyEvents inEvent);
	static void FocusOnGameWindow();
	// static void SetFPS(uint x);
	// static void AddControllerButtonsInput(); //is possible todo something like this via code? 
	// static void AddJoystickInput(); // i can't find any referece or code of someone/something sending a joystick message to another application
	
	// --- --- --- --- --- --- --- --- --- --- ---
	
	//Program Specific.
	static bool SetGameHandle(const wchar_t gameName[], char gameWindowName[]);
	static void SendSavedInputs();

	//Helpers
	static KeyEvents ConvertToKeyEventHelper(std::string in);
	static SpecialKeyboardInputs ConvertToSpecialKeyboardKeyHelper(std::string in);
	static InputManager::MouseInputs ConvertToMouseClick(std::string in);
private:
	// Private constructor to prevent direct instantiation
	InputManager() {}
	//HANDLE gameHwnd = nullptr;
	//HWND gameWindowHwnd = nullptr;
	//InputManager() = default; 
	~InputManager() = default;
};
#endif 

