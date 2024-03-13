#include <Windows.h>
#include <iostream>
#include <vector>
#include "MemoryAccess.h"
#include "ProcessAccess.h"

float MemoryAccess::GetFloatInAddress(HANDLE handle, intptr_t address)
{
	float buffer1 = 0.000;
	int err1 = ReadProcessMemory(handle, (LPCVOID)address, &buffer1, sizeof(buffer1), nullptr);
	if (err1 == 0) {
		std::cout << ">> [GetFloatInAddress-ERROR]: error getting float from address:" << GetLastError() << std::endl;
		return 0;
	}
	return buffer1;
}

byte MemoryAccess::GetByteInAddress(HANDLE handle, intptr_t address)
{
	byte buffer1 = 0;
	ReadProcessMemory(handle, (LPCVOID)address, &buffer1, sizeof(byte), nullptr);
	return buffer1;
}

intptr_t MemoryAccess::GetAddressFromOffsets(HANDLE handle, intptr_t address, std::vector<DWORD> offsets)
{
	intptr_t holdAddress = address;
	//Get the starting address
	int err1 = ReadProcessMemory(handle, (LPCVOID)address, &holdAddress, sizeof(holdAddress), nullptr);
	if (err1 == 0) {
		std::cout << ">> [GetByteInAddress-ERROR]: error getting address:" << GetLastError() << std::endl;
	}
	//add all the offsets except the last one, since the last offset points to the value we want.
	for (int i = 0; i < offsets.size() - 1; i++) {

		int err2 = ReadProcessMemory(handle, (LPCVOID)(holdAddress + offsets.at(i)), &holdAddress, sizeof(holdAddress), nullptr);
		if (err2 == 0) {
			std::cout << i << ">> [GetAddressFromOffsets-ERROR]: error getting offset:" << GetLastError() << std::endl;
		}
	}
	return holdAddress + offsets.at(offsets.size() - 1);
}

void MemoryAccess::WriteFloatToAdress(HANDLE handle, intptr_t Address, float value) {
	int err = WriteProcessMemory(handle, (LPVOID)Address, &value, sizeof(value), nullptr);
	if (err == 0) {
		std::cout << ">> [WriteFloatToAddress-ERROR]: error writting memory :" << GetLastError() << std::endl;
	}
}