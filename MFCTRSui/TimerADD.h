#pragma once
#include "AddClockDlg.h"
#include <string>
class TimerADD
{
public:
	TimerADD(CString tag_,CString name_,CString threads_,CString clock_name_,Clock& curClock);
	TimerADD(const TimerADD&);
	~TimerADD();

private:
	
	Clock clocks;
	CString tag;
	CString name;
	CString threads;
	CString clock_name;
	unsigned long unique_value=0;

public:
	bool Begin(TiXmlNode* root);
	bool End(TiXmlNode* root);
	inline Clock getClock();
	inline CString getTag();
	inline CString getName();
	inline CString getThreads();
	inline CString getClockName();
	TimerADD& operator=(const TimerADD&);
	inline unsigned long getUnique();
};

inline Clock TimerADD::getClock()
{
	return clocks;
}

inline unsigned long TimerADD::getUnique()
{
	return unique_value;
}



inline CString TimerADD::getTag()
{
	return tag;
}

inline CString TimerADD::getName()
{
	return name;
}

inline CString TimerADD::getThreads()
{
	return threads;
}

inline CString TimerADD::getClockName()
{
	return clock_name;
}

extern TimerADD* curTime;