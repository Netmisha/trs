#include "stdafx.h"
#include "Metadata.h"

Metadata::Metadata(char* Name, char* Date, char* Version, char* Mail,char* Copyright, char* License, char* Info)
{
	autorName = new char[strlen(Name)];
	strncpy_s(autorName, strlen(Name), Name, strlen(Name));
	date = new char[strlen(Date)];
	strncpy_s(date, strlen(Date), Date, strlen(Date));
	version = new char[strlen(Version)];
	strncpy_s(version, strlen(Version),Version, strlen(Version));
	mail = new char[strlen(Mail)];
	strncpy_s(mail, strlen(Mail), Mail, strlen(Mail));
	copyright = new char[strlen(Copyright)];
	strncpy_s(copyright, strlen(Copyright),Copyright, strlen(Copyright));
	license = new char[strlen(License)];
	strncpy_s(license, strlen(License), License, strlen(License));
	info = new char[strlen(Info)];
	strncpy_s(info, strlen(Info), Info, strlen(Info));
}

Metadata::~Metadata()
{
	delete[] autorName;
	delete[] date;
	delete[] version;
	delete[] mail;
	delete[] copyright;
	delete[] license;
	delete[] info;
}