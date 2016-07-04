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
	delete[] date;
	delete[] version;
	delete[] mail;
	delete[] copyright;
	delete[] license;
	delete[] info;
}