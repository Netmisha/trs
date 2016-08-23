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
			ClockInstance instance;
			instance.clock_name = currentTimer.getClockName();
			instance.days = currentTimer.getClock().get_time().get_day();
			char* hour = new char[sizeof(currentTimer.getClock().get_time().get_hour()) + 1];
			sprintf_s(hour, sizeof(currentTimer.getClock().get_time().get_hour()), "%S", currentTimer.getClock().get_time().get_hour());
			instance.hour = hour;
			char* minute = new char[sizeof(currentTimer.getClock().get_time().get_minute()) + 1];
			sprintf_s(minute, sizeof(currentTimer.getClock().get_time().get_minute()), "%S", currentTimer.getClock().get_time().get_minute());
			instance.days = currentTimer.getClock().get_time().get_day();
			instance.minute = minute;
			instance.ident = currentTimer.getUnique();
			instance.name = currentTimer.getName();
			instance.repeat = currentTimer.getClock().IsWeekly();
			instance.tag = currentTimer.getTag();
			instance.threads = currentTimer.getThreads();
			instance.suites = currentTimer.getClock().get_suites();
			timersColl.push_back(currentTimer);
			instanceColl.push_back(instance);
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
	timersColl.push_back(cutTimer);
	instanceColl.push_back(curIn);
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

std::vector<ClockInstance> TimerAddCollection::getTimers()
{
	return instanceColl;
}

bool TimerAddCollection::Remove(ClockInstance curIn)
{
	std::vector<TimerADD>::iterator it = timersColl.begin();
	for (it; it != timersColl.end(); ++it)
	{
		if (it->getUnique() == curIn.ident)
		{
			timersColl.erase(it);
			break;
		}
	}
	std::vector<ClockInstance>::iterator iter = instanceColl.begin();
	for (iter; iter != instanceColl.end(); ++iter)
	{
		if (iter->ident == curIn.ident)
		{
			instanceColl.erase(iter);
			break;
		}
	}
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