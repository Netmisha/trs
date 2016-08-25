#include "stdafx.h"
#include "Time.h"

Time::Time(DWORD day, DWORD h, DWORD min) :
	day_of_week(day), hour(h), minute(min) 
{
}
Time::Time()
{

}
bool Time::operator<(const Time& val)
{
	if (day_of_week != val.day_of_week)
	{
		return day_of_week < val.day_of_week ? true : false;
	}
	else
	{
		if (hour != val.hour)
		{
			return hour < val.day_of_week ? true : false;
		}
		else
		{
			return minute < val.minute ? true : false;
		}
	}
}

bool Time::operator>(const Time& val)
{
	return !(operator<(val));
}

bool Time::operator == (const Time& val)
{
	if (day_of_week == val.day_of_week)
	{
		if (hour == val.hour)
		{
			if (minute == val.minute)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

LARGE_INTEGER Time::operator-(SYSTEMTIME& sis)
{
	
	LARGE_INTEGER result;
	result.QuadPart = this->day_of_week - sis.wDayOfWeek;
	result.QuadPart += this->hour - sis.wHour;
	result.QuadPart += this->minute - sis.wMinute;
	return result;
}