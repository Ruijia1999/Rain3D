#ifndef RAIN_TIME
#define RAIN_TIME

#include <cstdint>

namespace Rain
{
	namespace Time
	{

		uint64_t GetCurrentSystemTimeTickCount();

		double ConvertTicksToSeconds(const uint64_t i_tickCount);
		uint64_t ConvertSecondsToTicks(const double i_secondCount);
		double ConvertRatePerSecondToRatePerTick(const double i_rate_perSecond);

		void Initialize();
		void CleanUp();
	}
}

#endif
