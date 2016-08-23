#include "stdafx.h"
#include "TimerADD.h"
#include "Functionality.h"

TimerADD::TimerADD(CString tag_, CString name_, CString threads_, CString clock_name_, Clock& curClock) :clocks(curClock)
{
	tag = tag_;
	name = name_;
	threads = threads_;
	clock_name = clock_name_;
	FILETIME fTime;
	GetSystemTimeAsFileTime(&fTime);
	unique_value += fTime.dwHighDateTime + fTime.dwLowDateTime;
}


TimerADD::~TimerADD()
{

}

bool TimerADD::Begin(TiXmlNode* root)
{
	char* day=nullptr;
	char* hour=nullptr;
	char* minute=nullptr;
	for (TiXmlNode* el = root->FirstChild(); el != 0; el = el->NextSibling())
	{
		
		if (!strcmp(el->Value(), "day"))
		{
			TiXmlNode* text = el->FirstChild();
			day = new char[strlen(text->Value()) + 1];
			strncpy_s(day, strlen(text->Value()) + 1, text->Value(), strlen(text->Value()));
		}
		if (!strcmp(el->Value(), "hour"))
		{
			TiXmlNode* text = el->FirstChild();
			hour = new char[strlen(text->Value()) + 1];
			strncpy_s(hour, strlen(text->Value()) + 1, text->Value(), strlen(text->Value()));
		}
		if (!strcmp(el->Value(), "minute"))
		{
			TiXmlNode* text = el->FirstChild();
			minute = new char[strlen(text->Value()) + 1];
			strncpy_s(minute, strlen(text->Value()) + 1, text->Value(), strlen(text->Value()));
		}
		if (!strcmp(el->Value(), "name"))
		{
			TiXmlNode* text = el->FirstChild();
			CString Cname( text->Value());
			name = Cname;
		}
		if (!strcmp(el->Value(), "tag"))
		{
			TiXmlNode* text = el->FirstChild();
			CString Cname(text->Value());
			tag = Cname;
		}
		if (!strcmp(el->Value(), "threads"))
		{
			TiXmlNode* text = el->FirstChild();
			CString Cname(text->Value());
			threads = Cname;
		}
		if (!strcmp(el->Value(), "clockName"))
		{
			TiXmlNode* text = el->FirstChild();
			CString Cname(text->Value());
			clock_name = Cname;
		}
	}
	Time curTime((DWORD)day, (DWORD)hour, (DWORD)minute);
	clocks.set_time(curTime);
	return true;
}

bool TimerADD::End(TiXmlNode* root)
{

			TiXmlElement* curTimer = new TiXmlElement("Suite");
			root->LinkEndChild(curTimer);
			char* DayC = new char[sizeof(clocks.get_time().get_day())];
			sprintf_s(DayC, sizeof(clocks.get_time().get_day()), "%S", clocks.get_time().get_day());
			TiXmlElement* day = new TiXmlElement("day");
			curTimer->LinkEndChild(day);
			TiXmlText* dayText = new TiXmlText(DayC);
			day->LinkEndChild(dayText);
			delete[] DayC;
			TiXmlElement* hour = new TiXmlElement("hour");
			curTimer->LinkEndChild(hour);
			char* HourC = new char[sizeof(clocks.get_time().get_hour())];
			sprintf_s(HourC, sizeof(clocks.get_time().get_hour()), "%S", clocks.get_time().get_hour());
			TiXmlText* textHour = new TiXmlText(HourC);
			hour->LinkEndChild(textHour);
			delete[] HourC;
			TiXmlElement* minute = new TiXmlElement("minute");
			curTimer->LinkEndChild(minute);
			char* MinuteC = new char[sizeof(clocks.get_time().get_minute())];
			sprintf_s(MinuteC, sizeof(clocks.get_time().get_minute()), "%S", clocks.get_time().get_minute());
			TiXmlText* textMinute = new TiXmlText(MinuteC);
			minute->LinkEndChild(textMinute);
			delete[] MinuteC;
			TiXmlElement* isRepeatable = new TiXmlElement("isRepeatable");
			curTimer->LinkEndChild(isRepeatable);
			if (clocks.IsWeekly())
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
		
		
		return true;
}

