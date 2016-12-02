#include "stdafx.h"
#include "TimerADD.h"
#include "Functionality.h"

TimerADD::TimerADD(CString tag_, CString name_, CString threads_, CString clock_name_, Clock& curClock,int uniq) :clocks(curClock)
{
	tag = tag_;
	name = name_;
	threads = threads_;
	clock_name = clock_name_;
	unique_value = uniq;
}


TimerADD::~TimerADD()
{

}


TimerADD& TimerADD::operator=(const TimerADD& val)
{
	tag = val.tag;
	name = val.name;
	threads = val.threads;
	clock_name = val.clock_name;
	unique_value = val.unique_value;
	clocks = val.clocks;
	return *this;
}
void TimerADD::setUnique(int val)
{
	unique_value = val;
}
TimerADD::TimerADD(const TimerADD& val)
{
	tag = val.tag;
	name = val.name;
	threads = val.threads;
	clock_name = val.clock_name;
	unique_value = val.unique_value;
	clocks = val.clocks;
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
		if (!strcmp(el->Value(), "isRepeatable"))
		{
			TiXmlNode* text = el->FirstChild();
			if (!strcmp(text->Value(), "false"))
			{
				clocks.set_Weekly(false);
			}
			if (!strcmp(text->Value(), "true"))
			{
				clocks.set_Weekly(true);
			}
		}
		if (!strcmp(el->Value(), "unique"))
		{
			TiXmlNode* text = el->FirstChild();
			unique_value = atoi(text->Value());
		}
		if (!strcmp(el->Value(), "Path"))
		{
			for (TiXmlNode* subel = el->FirstChild(); subel != 0; subel = subel->NextSibling())
			{
				if (!strcmp(subel->Value(), "currentPath"))
				{
					TiXmlNode* text = subel->FirstChild();
					TCHAR* buf = new TCHAR[strlen(text->Value()) + 1];
					convertToTCHAR(buf, text->Value());
					SuiteRoot currentRoot(buf);
					clocks.add_path(currentRoot);
					delete[] buf;
				}
			}
			
		}
	}
	Time curTime(atoi(day), atoi(hour), atoi(minute));
	clocks.set_time(curTime);
	
	return true;
}

bool TimerADD::End(TiXmlNode* root)
{

			TiXmlElement* curTimer = new TiXmlElement("Suite");
			root->LinkEndChild(curTimer);
			int lic = sizeof(clocks.get_time().get_day());
			char* DayC = new char[30];
			sprintf_s(DayC, 30, "%d", clocks.get_time().get_day());
			TiXmlElement* day = new TiXmlElement("day");
			curTimer->LinkEndChild(day);
			TiXmlText* dayText = new TiXmlText(DayC);
			day->LinkEndChild(dayText);
			delete[] DayC;
			TiXmlElement* hour = new TiXmlElement("hour");
			curTimer->LinkEndChild(hour);
			char* HourC = new char[30];
			lic = sizeof(clocks.get_time().get_hour());
			if ((int)clocks.get_time().get_hour() != 0)
			{
				sprintf_s(HourC, 30, "%d", clocks.get_time().get_hour());
			}
			else
			{
				sprintf_s(HourC, 30, "%s", "00");
			}
			TiXmlText* textHour = new TiXmlText(HourC);
			hour->LinkEndChild(textHour);
			delete[] HourC;
			TiXmlElement* minute = new TiXmlElement("minute");
			curTimer->LinkEndChild(minute);
			char* MinuteC = new char[30];
			lic = sizeof(clocks.get_time().get_minute());
			if ((int)clocks.get_time().get_minute() != 0)
			{
				sprintf_s(MinuteC, 30, "%d", clocks.get_time().get_minute());
			}
			else
			{
				sprintf_s(MinuteC, 30, "%s", "00");
			}
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
			TiXmlElement* Un = new TiXmlElement("unique");
			curTimer->LinkEndChild(Un);
			char buf[MAX_PATH];
			sprintf_s(buf, MAX_PATH, "%d", unique_value);
			TiXmlText* UnText = new TiXmlText(buf);
			Un->LinkEndChild(UnText);
			TiXmlElement* Path = new TiXmlElement("Path");
			curTimer->LinkEndChild(Path);
			for (int i = 0; i < clocks.get_suites().size(); ++i)
			{
				TiXmlElement* curPath = new TiXmlElement("currentPath");
				Path->LinkEndChild(curPath);
				char* way = convertToChar(clocks.get_suites()[i].get_path());
				TiXmlText* pathText = new TiXmlText(way);
				delete[] way;
				curPath->LinkEndChild(pathText);
			}
		
		return true;
}

