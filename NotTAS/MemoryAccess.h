#include <iostream>
#ifndef MEMORYACCESS_H
#define MEMORYACCESS_H


class MemoryAccess
{
public:
	//Getters
	static float GetFloatInAddress(HANDLE handle, intptr_t address);
	static byte GetByteInAddress(HANDLE handle, intptr_t address);
	static intptr_t GetAddressFromOffsets(HANDLE handle, intptr_t address, std::vector<DWORD> offsets);
	//Setters
	static void WriteFloatToAdress(HANDLE handle, intptr_t Address, float value);
private:
	MemoryAccess();
	
};
#endif // !MEMORYACCESS_H


