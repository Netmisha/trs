#include "stdafx.h"
#include "Metadata.h"

Metadata::Metadata(char* Name)
{
	autorName = new char[strlen(Name)];
	strncpy_s(autorName, strlen(Name), Name, strlen(Name));
}

Metadata::Metadata(const Metadata& val)
{
	int len;
	if (val.autorName)
	{

		len = strlen(val.autorName);
		autorName = new char[len + 1];
		strcpy_s(autorName, len + 1, val.autorName);
	}
	if (val.date)
	{
		len = strlen(val.date);
		date = new char[len + 1];
		strcpy_s(date, len + 1, val.date);
	}
	if (val.version)
	{
		len = strlen(val.version);
		version = new char[len + 1];
		strcpy_s(version, len + 1, val.version);
	}
	if (val.mail)
	{
		len = strlen(val.mail);
		mail = new char[len + 1];
		strcpy_s(mail, len + 1, val.mail);
	}
	if (val.copyright)
	{
		len = strlen(val.copyright);
		copyright = new char[len + 1];
		strcpy_s(copyright, len + 1, val.copyright);
	}
	if (val.license)
	{
		len = strlen(val.license);
		license = new char[len + 1];
		strcpy_s(license, len + 1, val.license);
	}
	if (val.info)
	{
		len = strlen(val.info);
		info = new char[len + 1];
		strcpy_s(info, len + 1, val.info);
	}
}

Metadata::Metadata()
{

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