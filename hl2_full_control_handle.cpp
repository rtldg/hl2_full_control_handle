#include <stdio.h>
#include <windows.h>
#include <TlHelp32.h>

DWORD GetPIDByName(const char* ProcName)
{
	PROCESSENTRY32 pe32;
	HANDLE hSnapshot = NULL;

	pe32.dwSize = sizeof(PROCESSENTRY32);
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(hSnapshot, &pe32))
	{
		do {
			if (strcmp(pe32.szExeFile, ProcName) == 0)
				return pe32.th32ProcessID;
		} while (Process32Next(hSnapshot, &pe32));
	}

	if (hSnapshot != INVALID_HANDLE_VALUE)
		CloseHandle(hSnapshot);

	return NULL;
}

int main()
{
	DWORD processID;
	printf("Waiting for CS:S to start...\n");
	while (1)
	{
		processID = GetPIDByName("hl2.exe");
		if (processID) break;
		Sleep(1000);
	}

	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	printf("handle = %x\n", process);
	LoadLibraryA("C:\\code\\sv_downloadurl_sniper\\x64\\Release\\sv_downloadurl_sniper.dll");
	WaitForSingleObject(process, INFINITE);
	return 0;
}