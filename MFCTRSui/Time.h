#ifndef TIME_HEADER
#define TIME_HEADER

#include "afxwin.h"
#include "afxcmn.h"
#include "TRSLibrary\TRSManager.h"

class Time
{
public:
	Time(DWORD day, DWORD hour, DWORD min);
	Time();
	bool operator<(const Time&);
	bool operator>(const Time&);

	inline DWORD get_day() const;
	inline DWORD get_hour() const;
	inline DWORD get_minute() const;
private:
	DWORD day_of_week;
	DWORD hour;
	DWORD minute;
};

// ==========================================================================

inline DWORD Time::get_day() const
{
	return day_of_week;
}

inline DWORD Time::get_hour() const
{
	return hour;
}

inline DWORD Time::get_minute() const
{
	return minute;
}
#endif