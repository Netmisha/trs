#ifndef CLOCK_INSTANCE_HEADER
#define CLOCK_INSTANCE_HEADER

#include "SuiteRoot.h"

#include <vector>

class ClockInstance
{
public:
	

private:
	std::vector<SuiteRoot> suites;
	DWORD days;
	CString clock_name;
	CString tag;
	CString name;
	CString threads;
	CString hour;
	CString minute;
	bool repeat;
};

#endif