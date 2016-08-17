#include "stdafx.h"
#include "Clock.h"
#include <string.h>

Clock::Clock(const TCHAR* suite_path, bool weekly, DWORD d, DWORD h, DWORD m) :
	test_time(d, h, m), repeat(weekly)
{
	if (suite_path)
	{
		size_t size = _tcslen(suite_path);
		suite_root = new TCHAR[size + 1];
		_tcscpy_s(suite_root, size + 1, suite_path);
	}
	else
	{
		suite_root = nullptr;
		logger << "A nullptr was passed as suite_path parameter to the Clock constructor";
	}
}

Clock::Clock(const TCHAR* suite_path, bool weekly, const Time& time) :
	Clock(suite_path, weekly, time.get_day(), time.get_hour(), time.get_minute())
{
}

Clock::Clock(const Clock& val) : repeat(val.repeat), test_time(val.test_time)
{
	size_t size = _tcslen(val.suite_root);
	suite_root = new TCHAR[size + 1];
	_tcscpy_s(suite_root, size + 1, val.suite_root);
}