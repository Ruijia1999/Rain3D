#include "EngineLog.h"
#include <string>
void Rain::EngineLog::CreateLogFile() {
	HANDLE hFile = CreateFile(L"Log.txt", GENERIC_READ | GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
	
	FlushFileBuffers(hFile);
	CloseHandle(hFile);

}
void Rain::EngineLog::Log(const char* i_msg) {
	std::string msg;
	msg.append(i_msg);
	msg.append("\n");
	HANDLE hFile = CreateFile(L"Log.txt", GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
	SetFilePointer(hFile, 0, 0, FILE_END);
	DWORD count = 0;
	BOOL ret = WriteFile(hFile, msg.c_str(), msg.length(), &count, NULL);
	FlushFileBuffers(hFile);
	CloseHandle(hFile);
}
void Rain::EngineLog::LogWarning(const char* i_msg) {
	std::string msg;
	msg.append("[Warning]:");
	msg.append(i_msg);
	msg.append("\n");
	HANDLE hFile = CreateFile(L"Log.txt", GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
	SetFilePointer(hFile, 0, 0, FILE_END);
	DWORD count = 0;
	BOOL ret = WriteFile(hFile, msg.c_str(), msg.length(), &count, NULL);
	FlushFileBuffers(hFile);
	CloseHandle(hFile);
}
void Rain::EngineLog::LogError(const char* i_msg) {

	std::string msg;
	msg.append("[Error]:");
	msg.append(i_msg);
	msg.append("\n");
	HANDLE hFile = CreateFile(L"Log.txt", GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
	SetFilePointer(hFile, 0, 0, FILE_END);
	DWORD count = 0;
	BOOL ret = WriteFile(hFile, msg.c_str(), msg.length(), &count, NULL);
	FlushFileBuffers(hFile);
	CloseHandle(hFile);
}