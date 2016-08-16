#ifndef CLOCK_HEADER
#define CLOCK_HEADER

#include "Time.h"

class Clock
{
public:
	Clock(const TCHAR* suite_path, bool weekly, DWORD d, DWORD h, DWORD m);
	Clock(const TCHAR* suite_path, bool weekly, const Time&);

	inline bool IsWeekly() const;
	inline ~Clock();
private:
	Time test_time;
	bool repeat;
	TCHAR* suite_root; 
};

// ==========================================================================

inline bool Clock::IsWeekly() const
{
	return repeat;
}

inline Clock::~Clock()
{
	delete[] suite_root;
}

#endif