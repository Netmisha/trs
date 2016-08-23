#pragma once
#include "TimerADD.h"
#include "ClockInstance.h"
#include <vector>
class TimerAddCollection
{
public:
	TimerAddCollection();
	~TimerAddCollection();
	bool Init();
	bool Add(ClockInstance ins);
	bool Remove(ClockInstance ins);
	std::vector<ClockInstance> getTimers();
private:
	std::vector<ClockInstance> instanceColl;
	std::vector<TimerADD> timersColl;
};

extern TimerAddCollection timersCollection;