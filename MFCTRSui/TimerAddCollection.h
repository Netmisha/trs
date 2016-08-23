#pragma once
#include "TimerADD.h"
#include <vector>
class TimerAddCollection
{
public:
	TimerAddCollection();
	~TimerAddCollection();
	bool Init();
private:
	std::vector<TimerADD> timersColl;
};

