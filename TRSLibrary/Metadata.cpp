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

bool Metadata::setDate(char*date_)
{
	if (date)
	{
		delete[] date;
		date = new char[strlen(date_)];
		strncpy_s(date, strlen(date_), date_, strlen(date_));
		return true;
	}
	else
	{
		if (date = new char[strlen(date_)])
		{
			strncpy_s(date, strlen(date_), date_, strlen(date_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Metadata::setCopyright(char*copyright_)
{
	if (copyright)
	{
		delete[] copyright;
		copyright = new char[strlen(copyright_)];
		strncpy_s(copyright, strlen(copyright_), copyright_, strlen(copyright));
		return true;
	}
	else
	{
		if (copyright = new char[strlen(copyright_)])
		{
			strncpy_s(copyright, strlen(copyright_), copyright_, strlen(copyright_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Metadata::setVersion(char*version_)
{
	if (version)
	{
		delete[] version;
		version = new char[strlen(version_)];
		strncpy_s(version, strlen(version_), version_, strlen(version_));
		return true;
	}
	else
	{
		if (version = new char[strlen(version_)])
		{
			strncpy_s(version, strlen(version_), version_, strlen(version_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Metadata::setLicense(char*license_)
{
	if (license)
	{
		delete[] license;
		license = new char[strlen(license_)];
		strncpy_s(license, strlen(license_), license_, strlen(license_));
		return true;
	}
	else
	{
		if (license = new char[strlen(license_)])
		{
			strncpy_s(license, strlen(license_), license_, strlen(license_));
			return true;
		}
		else
		{
			return false;
		}
	}
}