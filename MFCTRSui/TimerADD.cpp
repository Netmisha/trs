#include "stdafx.h"
#include "TimerADD.h"
#include "Functionality.h"

TimerADD::TimerADD()
{
	FILETIME fTime;
	GetSystemTimeAsFileTime(&fTime);
	unique_value += fTime.dwHighDateTime + fTime.dwLowDateTime;
}


TimerADD::~TimerADD()
{

}

bool TimerADD::Begin()
{
	TiXmlDocument doc("Timers.xml");
	if (doc.LoadFile())
	{

	}
	else
	{

	}
	return true;
}

bool TimerADD::End()
{

		TiXmlDocument newDoc;
		TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "", "");
		newDoc.LinkEndChild(dec);
		TiXmlElement* element = new TiXmlElement("Timers");
		newDoc.LinkEndChild(element);
		for (int i = 0; i < clocks.size(); ++i)
		{
			TiXmlElement* curTimer = new TiXmlElement("Suite");
			element->LinkEndChild(curTimer);
			char* DayC = new char[sizeof(clocks[i].get_time().get_day())];
			sprintf_s(DayC, sizeof(clocks[i].get_time().get_day()), "%S", clocks[i].get_time().get_day());
			TiXmlElement* day = new TiXmlElement("day");
			curTimer->LinkEndChild(day);
			TiXmlText* dayText = new TiXmlText(DayC);
			day->LinkEndChild(dayText);
			delete[] DayC;
			TiXmlElement* hour = new TiXmlElement("hour");
			curTimer->LinkEndChild(hour);
			char* HourC = new char[sizeof(clocks[i].get_time().get_hour())];
			sprintf_s(HourC, sizeof(clocks[i].get_time().get_hour()), "%S", clocks[i].get_time().get_hour());
			TiXmlText* textHour = new TiXmlText(HourC);
			hour->LinkEndChild(textHour);
			delete[] HourC;
			TiXmlElement* minute = new TiXmlElement("minute");
			curTimer->LinkEndChild(minute);
			char* MinuteC = new char[sizeof(clocks[i].get_time().get_minute())];
			sprintf_s(MinuteC, sizeof(clocks[i].get_time().get_minute()), "%S", clocks[i].get_time().get_minute());
			TiXmlText* textMinute = new TiXmlText(MinuteC);
			minute->LinkEndChild(textMinute);
			delete[] MinuteC;
			TiXmlElement* isRepeatable = new TiXmlElement("isRepeatable");
			curTimer->LinkEndChild(isRepeatable);
			if (clocks[i].IsWeekly())
			{
				TiXmlText* textRepeat = new TiXmlText("true");
				isRepeatable->LinkEndChild(textRepeat);
			}
			else
			{
				TiXmlText* textRepeat = new TiXmlText("false");
				isRepeatable->LinkEndChild(textRepeat);
			}
			TiXmlElement* Tag = new TiXmlElement("tag");
			curTimer->LinkEndChild(Tag);
			char* tagC = fromCStringToChar(tag);
			TiXmlText* textTag = new TiXmlText(tagC);
			Tag->LinkEndChild(textTag);
			delete[] tagC;
			TiXmlElement* Name = new TiXmlElement("name");
			curTimer->LinkEndChild(Name);
			char* nameC = fromCStringToChar(name);
			TiXmlText* textName = new TiXmlText(nameC);
			Name->LinkEndChild(textName);
			delete[] nameC;
			TiXmlElement* Threads = new TiXmlElement("threads");
			curTimer->LinkEndChild(Threads);
			char* threadsC = fromCStringToChar(threads);
			TiXmlText* textThreads = new TiXmlText(threadsC);
			Threads->LinkEndChild(textThreads);
			delete[] threadsC;
			TiXmlElement* ClockName = new TiXmlElement("clockName");
			curTimer->LinkEndChild(ClockName);
			char* clockNameC = fromCStringToChar(clock_name);
			TiXmlText* textClockName = new TiXmlText(clockNameC);
			ClockName->LinkEndChild(textClockName);
			delete[] clockNameC;
		}
		newDoc.SaveFile("Timers.xml");
		return true;
}

TimerADD& TimerADD::operator=(AddClockDlg& curDlg)
{
	tag = curDlg.get_tag();
	name = curDlg.get_name();
	clock_name = curDlg.get_clock_name();
	threads = curDlg.get_threads();
	std::list<Clock>::iterator it = curDlg.get_clock_collection().begin();
	for (it; it != curDlg.get_clock_collection().end(); ++it)
	{
		Clock curClock(*it);
		clocks.push_back(curClock);
	}
	return *this;
}