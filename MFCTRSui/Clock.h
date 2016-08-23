#ifndef CLOCK_HEADER
#define CLOCK_HEADER

#include "Time.h"
#include <vector>
#include "SuiteRoot.h"
using std::vector;
class Clock
{
public:
	Clock(std::vector<SuiteRoot> suites, bool weekly, DWORD d, DWORD h, DWORD m);
	Clock(std::vector<SuiteRoot> suites, bool weekly, const Time&);

	inline bool IsWeekly() const;
	inline vector<SuiteRoot> get_path() const;
	inline Time get_time() const;
	inline bool set_time(Time);
private:
	Time test_time;
	bool repeat;
	std::vector<SuiteRoot> roots; 
	
};

// ==========================================================================

inline bool Clock::IsWeekly() const
{
	return repeat;
}

inline std::vector<SuiteRoot> Clock::get_path() const
{
	return roots;
}

inline Time Clock::get_time() const
{
	return test_time;
}

inline bool Clock::set_time(Time cur)
{
	test_time = cur;
	return true;
}

#endif