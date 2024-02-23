#include <iostream>
#include <thread>
#include "InputManager.h"
#include "ScriptManager.h"
#include "Access/ProcessAccess.h"

#ifndef MAINLOGIC_H
#define MAINLOGIC_H


/// <summary>
/// Responsable for the main functions of the program like: calling scriptmanager to read from file and inserting the result into input manager,
/// Holding the current frame of work and asking the inputManager to send the inputs from the scriptmanager.
/// </summary>
class MainLogic
{
private:
	MainLogic() {};
	std::thread loopThread;
	bool keepLooping = false;
	unsigned long currentFrame = 0;
	void ExecutionThread(char* filename);
	void ExecuteFrame(unsigned long frame);
	ScriptManager& _sm = ScriptManager::GetInstance();
	InputManager& _inm = InputManager::GetInstance();
	ProcessAccess& _pa = ProcessAccess::GetInstance();
	bool isInLoad = false;
	void CheckLoad();
public:
	static MainLogic& GetInstance() {
		// We only need one call to this class, so making it a singleton would help reduce code.
		static MainLogic instance;
		return instance;
	}
	std::string AppExeName;
	std::string AppWindowName;
	std::string ScriptName = "";
	unsigned long startingFrame = 0;
	bool WaitingLoadingToStart = false;
	bool WaitingLoadingToEnd = false;
	/// <summary>
	/// Register all the functions. must be done before anything.
	/// </summary>
	void InitialSetup();
	/// <summary>
	/// if running, stop the tas loop.
	/// </summary>
	void StopExecution();
	void LoadTASSCript();
	bool IsRunning();
	unsigned long GetCurrentFrame();

	void ExecuteScript(char* fileName);
};
#endif // !MAINLOGIC_H



