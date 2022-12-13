#include "EngineLog.h"

void Rain::EngineLog::CreateLogFile(const char* i_fileName) {
	HANDLE hFile = CreateFile(L"Log.txt", GENERIC_READ | GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
	
	FlushFileBuffers(hFile);
	CloseHandle(hFile);

}
void Rain::EngineLog::Log(const char* i_fileName, const char* i_msg) {
	HANDLE hFile = CreateFile(L"Log.txt", GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
	SetFilePointer(hFile, 0, 0, FILE_END);
	DWORD count = 0;
	BOOL ret = WriteFile(hFile, i_msg, strlen(i_msg), &count, NULL);
	FlushFileBuffers(hFile);
	CloseHandle(hFile);
}