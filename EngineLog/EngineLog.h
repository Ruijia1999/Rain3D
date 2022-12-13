#ifndef RAIN_ENGINELOG_H
#define RAIN_ENGINELOG_H
#include <Windows.h>
namespace Rain {
	namespace EngineLog {
		void CreateLogFile(const char* i_fileName);
		void Log(const char* i_fileName, const char* i_msg);
	}
}
#endif // !RAIN_ENGINELOG_H
