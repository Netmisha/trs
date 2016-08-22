#include "stdafx.h"
#include "ClockCollection.h"

bool ClockCollection::AddClock(TCHAR* suite_root, DWORD day_flag, DWORD hour, DWORD min, bool weekly)
{
	if (!suite_root || day_flag > EVERY_DAY)
		return false;

	days = day_flag; 

	for (int i = 0; i < DAYS_IN_WEEK; ++i)
	{
		DWORD day_of_week = day_flag & (1 << i);
		if (day_of_week)
			clocks.push_back(Clock(suite_root, weekly, day_of_week, hour, min));
	}

	return true;
}