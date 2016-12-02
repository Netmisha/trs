#pragma once
#include "TimerAddCollection.h"
#include <Windows.h>

struct TimerData
{
	TimerAddCollection* coll;
	LPVOID dlg;
};