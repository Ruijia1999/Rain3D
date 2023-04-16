#ifndef RAIN_ENGINELOG_H
#define RAIN_ENGINELOG_H
#include <Windows.h>
namespace Rain {
	namespace EngineLog {
		void CreateLogFile();
		void Log(const char* i_msg);
		void LogError(const char* i_msg);
		void LogWarning(const char* i_msg);
	}
}
#endif // !RAIN_ENGINELOG_H
