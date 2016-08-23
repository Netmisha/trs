#ifndef CLOCK_INSTANCE_HEADER
#define CLOCK_INSTANCE_HEADER

#include "SuiteRoot.h"

#include <vector>

struct ClockInstance
{
	std::vector<SuiteRoot> suites;
	DWORD days;
	CString clock_name;
	CString tag;
	CString name;
	CString threads;
	CString hour;
	CString minute;
	bool repeat;
	DWORD ident;
};

#endif