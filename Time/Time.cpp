#include "Time.h"
#include <Windows.h>


namespace
{
	uint64_t s_tickCountPerSecond = 0;
}


uint64_t Rain::Time::GetCurrentSystemTimeTickCount()
{
	LARGE_INTEGER totalTickCountSinceSystemBoot;
	const auto result = QueryPerformanceCounter(&totalTickCountSinceSystemBoot);
	return static_cast<uint64_t>(totalTickCountSinceSystemBoot.QuadPart);
}

double Rain::Time::ConvertTicksToSeconds(const uint64_t i_tickCount)
{
	return static_cast<double>(i_tickCount) / static_cast<double>(s_tickCountPerSecond);
}

uint64_t Rain::Time::ConvertSecondsToTicks(const double i_secondCount)
{

	return static_cast<uint64_t>((i_secondCount * static_cast<double>(s_tickCountPerSecond)) + 0.5);
}

double Rain::Time::ConvertRatePerSecondToRatePerTick(const double i_rate_perSecond)
{
	return i_rate_perSecond / static_cast<double>(s_tickCountPerSecond);
}


 void Rain::Time::Initialize()
{

	 LARGE_INTEGER tickCountPerSecond;
	 if (QueryPerformanceFrequency(&tickCountPerSecond) != FALSE)
	 {
		 if (tickCountPerSecond.QuadPart != 0)
		 {
			 s_tickCountPerSecond = static_cast<uint64_t>(tickCountPerSecond.QuadPart);
		 }
	 }

}

void Rain::Time::CleanUp()
{
}
