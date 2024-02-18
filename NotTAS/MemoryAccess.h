#ifndef MEMORYACCESS_H
#define MEMORYACCESS_H
#include <iostream>
#include <string>

class MemoryAccess
{
public:
	//Getters
	static float GetFloatInAddress(HANDLE handle, intptr_t address);
	static intptr_t GetAddressFromOffsets(HANDLE handle, intptr_t address, std::vector<DWORD> offsets);
	//Setters
	static void WriteFloatToAdress(HANDLE handle, intptr_t Address, float value);
	static void DoingMemoryTest();
private:
	MemoryAccess();
	
};
#endif // !MEMORYACCESS_H


