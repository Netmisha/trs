#include "stdafx.h"
#include "Metadata.h"

Metadata::Metadata(char* Name)
{
	autorName = new char[strlen(Name)];
	strncpy_s(autorName, strlen(Name), Name, strlen(Name));
}

Metadata::Metadata()
{

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
		date = new char[strlen(date_)+1];
		strncpy_s(date, strlen(date_)+1, date_, strlen(date_));
		return true;
	}
	else
	{
		if (date = new char[strlen(date_)+1])
		{
			strncpy_s(date, strlen(date_)+1, date_, strlen(date_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Metadata::setInfo(char*info_)
{
	if (info)
	{
		delete[] info;
		info = new char[strlen(info_)+1];
		strncpy_s(info, strlen(info_) + 1, info_, strlen(info_));
		return true;
	}
	else
	{
		if (info = new char[strlen(info_)+1])
		{
			strncpy_s(info, strlen(info_)+1, info_, strlen(info_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Metadata::setMail(char*mail_)
{
	if (mail)
	{
		delete[] mail;
		mail = new char[strlen(mail_) + 1];
		strncpy_s(mail, strlen(mail_) + 1, mail_, strlen(mail_));
		return true;
	}
	else
	{
		if (mail = new char[strlen(mail_)+1])
		{
			strncpy_s(mail, strlen(mail_)+1, mail_, strlen(mail_));
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
		copyright = new char[strlen(copyright_)+1];
		strncpy_s(copyright, strlen(copyright_)+1, copyright_, strlen(copyright));
		return true;
	}
	else
	{
		if (copyright = new char[strlen(copyright_)+1])
		{
			strncpy_s(copyright, strlen(copyright_)+1, copyright_, strlen(copyright_));
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
		version = new char[strlen(version_)+1];
		strncpy_s(version, strlen(version_)+1, version_, strlen(version_));
		return true;
	}
	else
	{
		if (version = new char[strlen(version_)+1])
		{
			strncpy_s(version, strlen(version_)+1, version_, strlen(version_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Metadata::setName(char*name_)
{
	if (autorName)
	{
		delete[] autorName;
		autorName = new char[strlen(name_)+1];
		strncpy_s(autorName, strlen(name_)+1, name_, strlen(name_));
		return true;
	}
	else
	{
		if (autorName = new char[strlen(name_)+1])
		{
			strncpy_s(autorName, strlen(name_)+1, name_, strlen(name_));
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
		license = new char[strlen(license_)+1];
		strncpy_s(license, strlen(license_)+1, license_, strlen(license_));
		return true;
	}
	else
	{
		if (license = new char[strlen(license_)+1])
		{
			strncpy_s(license, strlen(license_)+1, license_, strlen(license_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

char* Metadata::getDate()
{
	return date;
}

char* Metadata::getVersion()
{
	return version;
}

char* Metadata::getMail()
{
	return mail;
}

char* Metadata::getCopyright()
{
	return copyright;
}

char* Metadata::getLicense()
{
	return license;
}

char* Metadata::getInfo()
{
	return info;
}