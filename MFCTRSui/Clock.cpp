#include "stdafx.h"
#include "Clock.h"
#include <string.h>
#include "SuiteRoot.h"

Clock::Clock(std::vector<SuiteRoot> suites, bool weekly, DWORD d, DWORD h, DWORD m) :
test_time(d, h, m), repeat(weekly), roots(suites)
{
}

Clock::Clock()
{

}

Clock::Clock(vector<SuiteRoot> suites, bool weekly, const Time& time) :
test_time(time), repeat(weekly), roots(suites)
{
}