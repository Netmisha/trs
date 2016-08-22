#ifndef CLOCK_COLLECTION_HEADER
#define CLOCK_COLLECTION_HEADER

#include <math.h>

#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 4
#define THURSDAY 8
#define FRIDAY 16
#define SATURDAY 32
#define SUNDAY 64
#define WEEKDAYS (pow(2, 5) - 1) // 0011111
#define WEEKEND (pow(2, 6) + pow(2,5)) // 1100000
#define EVERY_DAY (pow(2,7) - 1) // 1111111
#define DAYS_IN_WEEK 7

#include "Resource.h"
#include "SuiteRoot.h"
#include "Clock.h"

#include <list>
#include <vector>

class ClockCollection
{
public:
	bool AddClocks(std::vector<SuiteRoot> suites, DWORD day_flag, DWORD hour, DWORD min, bool weekly);
	inline std::list<Clock> get_schedule() const;
private:
	std::list<Clock> clocks;
};

// ======================================================================================
inline std::list<Clock> ClockCollection::get_schedule() const
{
	return clocks;
}

#endif