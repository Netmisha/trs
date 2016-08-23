#include "stdafx.h"
#include "TimerAddCollection.h"
#include "Functionality.h"

TimerAddCollection::TimerAddCollection()
{
}


TimerAddCollection::~TimerAddCollection()
{
}

bool TimerAddCollection::Init()
{
	TiXmlDocument doc("Timers.xml");
	if (doc.LoadFile())
	{
		for (TiXmlNode* element = doc.FirstChild(); element != 0; element = element->NextSibling())
		{
			CString tag_, name, threads, clock_name;
			Clock Clo;
			TimerADD currentTimer(tag_, name, threads, clock_name, Clo);
			while (!strcmp(element->Value(), "Suite"))
			{
				element = element->FirstChild();
			}
			currentTimer.Begin(element);
			timersColl.push_back(currentTimer);
		}
		return true;
	}
	return false;
}

bool TimerAddCollection::Add(ClockInstance curIn)
{
	char* hour = fromCStringToChar(curIn.hour);
	char* minute = fromCStringToChar(curIn.minute);
	Time* curTime=new Time(curIn.days, (DWORD)hour, (DWORD)minute);
	delete[] hour;
	delete[] minute;
	Clock* curClock=new Clock(curIn.suites, curIn.repeat, *curTime);
	TimerADD cutTimer(curIn.tag, curIn.name, curIn.threads, curIn.clock_name, *curClock);
	TiXmlDocument doc("Timers.xml");
	if (doc.LoadFile())
	{
		TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "", "");
		doc.LinkEndChild(dec);
		for (int i = 0; i < timersColl.size(); ++i)
		{
			timersColl[i].End(dec);
		}
	}
	else
	{
		TiXmlDocument newDoc;
		TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "", "");
		newDoc.LinkEndChild(dec);
		for (int i = 0; i < timersColl.size(); ++i)
		{
			timersColl[i].End(dec);
		}
		newDoc.SaveFile("Timers.xml");
	}
	return true;
}

bool TimerAddCollection::Remove(ClockInstance curIn)
{
	std::vector<TimerADD>::iterator it = timersColl.begin();
	for (it; it != timersColl.end(); ++it)
	{
		if (it->getUnique() == curIn.ident)
		{
			timersColl.erase(it);
			return true;
		}
	}
}