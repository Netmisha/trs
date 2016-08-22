#pragma once
#include "AddClockDlg.h"
#include <string>
class TimerADD
{
public:
	TimerADD();
	~TimerADD();
private:
	
	std::vector<Clock> clocks;
	CString tag;
	CString name;
	CString threads;
	CString clock_name;
	unsigned long unique_value=0;

public:
	bool Begin();
	bool End();
	TimerADD& operator=(AddClockDlg& curDlg);

};

extern TimerADD* curTime;