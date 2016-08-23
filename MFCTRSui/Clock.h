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
	Clock();
	inline bool IsWeekly() const;
	inline vector<SuiteRoot> get_suites() const;
	inline Time get_time() const;
	inline bool set_time(Time);
	inline bool set_Weekly(bool);
	inline bool add_path(SuiteRoot);
private:
	Time test_time;
	bool repeat;
	std::vector<SuiteRoot> roots; 
	
};

// ==========================================================================

inline bool Clock::add_path(SuiteRoot cur)
{
	roots.push_back(cur);
	return true;
}

inline bool Clock::IsWeekly() const
{
	return repeat;
}

inline std::vector<SuiteRoot> Clock::get_suites() const
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

inline bool Clock::set_Weekly(bool cur)
{
	repeat = cur;
	return true;
}

#endif