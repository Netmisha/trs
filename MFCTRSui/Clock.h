#ifndef CLOCK_HEADER
#define CLOCK_HEADER

#include "Time.h"

class Clock
{
public:
	Clock(const TCHAR* suite_path, bool weekly, DWORD d, DWORD h, DWORD m);
	Clock(const TCHAR* suite_path, bool weekly, const Time&);
	Clock(const Clock&);

	inline bool IsWeekly() const;
	inline TCHAR* get_path() const;
	inline Time get_time() const;
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

inline TCHAR* Clock::get_path() const
{
	return suite_root;
}

inline Time Clock::get_time() const
{
	return test_time;
}

inline Clock::~Clock()
{
	delete[] suite_root;
}

#endif