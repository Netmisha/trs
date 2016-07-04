#include "stdafx.h"
#include "Metadata.h"

Metadata::Metadata(char* Name)
{
	autorName = new char[strlen(Name)];
	strncpy_s(autorName, strlen(Name), Name, strlen(Name));
}

Metadata::~Metadata()
{
	delete[] autorName;
	if (date)
	{
		delete[] date;
	}
	if (version)
	{
		delete[] version;
	}
	if (mail)
	{
		delete[] mail;
	}
	if (copyright)
	{
		delete[] copyright;
	}
	if (license)
	{
		delete[] license;
	}
	if (info)
	{
		delete[] info;
	}
}