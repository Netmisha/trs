#include "stdafx.h"

#define TRSLibrary_EXPORT
#include "TRSInfo.h"
#include <iostream>
TRSInfo::TRSInfo(char*TestName, char*Description) 
{
	if (Name&&description)
	{
		Name = new char[strlen(TestName)];
		strncpy_s(Name, strlen(TestName), TestName, strlen(TestName));
		description = new char[strlen(Description)];
		strncpy_s(description, strlen(Description), Description, strlen(Description));
	}
}

TRSInfo::TRSInfo()
{
	metadata = new Metadata;
}

TRSInfo::~TRSInfo()
{
	delete[] Name;
	delete[] description;
	if (tag)
	{
		delete[] tag;
	}
	if (repeat)
	{
		delete[] repeat;
	}
	if (maxTime)
	{
		delete[] maxTime;
	}
	if (maxThreads)
	{
		delete[] maxThreads;
	}
	
}

char* TRSInfo::getName()
{
	return Name;
}

char* TRSInfo::getDescription()
{
	return description;
}

char* TRSInfo::getMaxThreads()
{
	return maxThreads;
}

char* TRSInfo::getTag()
{
	return tag;
}

bool TRSInfo::setTag(char*Tag)
{
	if (tag)
	{
		delete[] tag;
		tag = new char[strlen(Tag)+1];
		strncpy_s(tag, strlen(Tag)+1, Tag, strlen(Tag));
		return true;
	}
	else
	{
		if (tag = new char[strlen(Tag)+1])
		{
			strncpy_s(tag, strlen(Tag)+1, Tag, strlen(Tag));
			return true;
		}
	}
	return false;
}

bool TRSInfo::setRepeat(char*Repeat)
{
	if (repeat)
	{
		delete[] repeat;
		repeat = new char[strlen(Repeat)+1];
		strncpy_s(repeat, strlen(Repeat)+1, Repeat, strlen(Repeat));
		return true;
	}
	else
	{
		if (repeat = new char[strlen(Repeat)+1])
		{
			strncpy_s(repeat, strlen(Repeat)+1, Repeat, strlen(Repeat));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool TRSInfo::setName(char*Name_)
{
	if (Name)
	{
		delete[] Name;
		Name = new char[strlen(Name_)+1];
		strncpy_s(Name, strlen(Name_)+1, Name_, strlen(Name_));
		return true;
	}
	else
	{
		if (Name = new char[strlen(Name_)+1])
		{
			strncpy_s(Name, strlen(Name_)+1, Name_, strlen(Name_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool TRSInfo::setDescription(char*Desc_)
{
	if (description)
	{
		delete[] description;
		description = new char[strlen(Desc_)+1];
		strncpy_s(description, strlen(Desc_)+1, Desc_, strlen(Desc_));
		return true;
	}
	else
	{
		if (description = new char[strlen(Desc_)+1])
		{
			strncpy_s(description, strlen(Desc_)+1, Desc_, strlen(Desc_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool TRSInfo::Parse(TiXmlNode* pParent)
{
	if (!pParent) return false;
	
	TiXmlNode* pChild;
	TiXmlText* pText;

	int t = pParent->Type();

	switch (t)
	{
	case TiXmlNode::TINYXML_ELEMENT:
		
		if ((strncmp(pParent->Value(), "suite", strlen("suite")) == 0) || (strncmp(pParent->Value(), "test", strlen("test")) == 0))
		{
			TiXmlAttribute*atr = pParent->ToElement()->FirstAttribute();
				char*name = new char[strlen(atr->Value()) + 1];
				strncpy_s(name, strlen(atr->Value()) + 1, atr->Value(), strlen(atr->Value()));
				setName(name);
				atr = atr->Next();
				char*desc = new char[strlen(atr->Value()) + 1];
				strncpy_s(desc, strlen(atr->Value()) + 1, atr->Value(), strlen(atr->Value()));
				setDescription(desc);
			
			break;
		}
		if ((strncmp(pParent->Value(), "tag", strlen("tag")) == 0))
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				char*Tag = new char[strlen(child->Value())+1];
				strncpy_s(Tag, strlen(child->Value())+1, child->Value(), strlen(child->Value()));
				setTag(Tag);
			}
			break;
		}
		if ((strncmp(pParent->Value(), "repeat", strlen("repeat")) == 0))
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				char*Repeat = new char[strlen(child->Value())+1];
				strncpy_s(Repeat, strlen(child->Value())+1, child->Value(), strlen(child->Value()));
				setRepeat(Repeat);
			}
			break;
		}
		if ((strncmp(pParent->Value(), "maxTime", strlen("maxTime")) == 0))
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				char*MaxTime = new char[strlen(child->Value())+1];
				strncpy_s(MaxTime, strlen(child->Value())+1, child->Value(), strlen(child->Value()));
				setMaxTime(MaxTime);
			}
			break;
		}
		if ((strncmp(pParent->Value(), "maxThreads", strlen("maxThreads")) == 0))
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				char*MaxThreads = new char[strlen(child->Value())+1];
				strncpy_s(MaxThreads, strlen(child->Value())+1, child->Value(), strlen(child->Value()));
				setMaxThreads(MaxThreads);
			}
			break;
		}
		if ((strncmp(pParent->Value(), "execution", strlen("execution")) == 0))
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				char*executableName = new char[strlen(child->Value()) + 1];
				strncpy_s(executableName, strlen(child->Value()) + 1, child->Value(), strlen(child->Value()));
				setExecutableName(executableName);
			}
			break;
		}
		if ((strncmp(pParent->Value(), "result", strlen("result")) == 0))
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				char*Res = new char[strlen(child->Value()) + 1];
				strncpy_s(Res, strlen(child->Value()) + 1, child->Value(), strlen(child->Value()));
				setExpectedResult(Res);
			}
			break;
		}
		if ((strncmp(pParent->Value(), "metadata", strlen("metadata")) == 0))
		{
			
			for (TiXmlNode* child = pParent->FirstChild(); child != 0; child = child->NextSibling())
			{
				if (child->Type() == TiXmlNode::TINYXML_ELEMENT)
				{
					TiXmlNode* subChild;
					if (strncmp(child->Value(),"autor",strlen("autor"))==0)
					{
						subChild = child->FirstChild();
						if (subChild)
						{
							if (subChild->Type() == TiXmlNode::TINYXML_TEXT)
							{
								char* name = new char[strlen(subChild->Value()) + 1];
								strncpy_s(name, strlen(subChild->Value()) + 1, subChild->Value(), strlen(subChild->Value()));
								metadata->setName(name);
							}
						}
					}
					if (strncmp(child->Value(), "date", strlen("date"))==0)
					{
						subChild = child->FirstChild();
						if (subChild)
						{
							if (subChild->Type() == TiXmlNode::TINYXML_TEXT)
							{
								char* Date = new char[strlen(subChild->Value()) + 1];
								strncpy_s(Date, strlen(subChild->Value()) + 1, subChild->Value(), strlen(subChild->Value()));
								metadata->setDate(Date);
							}
						}
					}
					if (strncmp(child->Value(), "version", strlen("version"))==0)
					{
						subChild = child->FirstChild();
						if (subChild)
						{
							if (subChild->Type() == TiXmlNode::TINYXML_TEXT)
							{
								char* Version = new char[strlen(subChild->Value()) + 1];
								strncpy_s(Version, strlen(subChild->Value()) + 1, subChild->Value(), strlen(subChild->Value()));
								metadata->setVersion(Version);
							}
						}
					}
					if (strncmp(child->Value(), "mail", strlen("mail"))==0)
					{
						subChild = child->FirstChild();
						if (subChild)
						{
							if (subChild->Type() == TiXmlNode::TINYXML_TEXT)
							{
								char* Mail = new char[strlen(subChild->Value()) + 1];
								strncpy_s(Mail, strlen(subChild->Value()) + 1, subChild->Value(), strlen(subChild->Value()));
								metadata->setMail(Mail);
							}
						}
					}
					if (strncmp(child->Value(), "copyright", strlen("copyright"))==0)
					{
						subChild = child->FirstChild();
						if (subChild)
						{
							if (subChild->Type() == TiXmlNode::TINYXML_TEXT)
							{
								char* Copyright = new char[strlen(subChild->Value()) + 1];
								strncpy_s(Copyright, strlen(subChild->Value()) + 1, subChild->Value(), strlen(subChild->Value()));
								metadata->setCopyright(Copyright);
							}
						}
					}
					if (strncmp(child->Value(), "license", strlen("license"))==0)
					{
						subChild = child->FirstChild();
						if (subChild)
						{
							if (subChild->Type() == TiXmlNode::TINYXML_TEXT)
							{
								char* License = new char[strlen(subChild->Value()) + 1];
								strncpy_s(License, strlen(subChild->Value()) + 1, subChild->Value(), strlen(subChild->Value()));
								metadata->setLicense(License);
							}
						}
					}
					if (strncmp(child->Value(), "info", strlen("info"))==0)
					{
						subChild = child->FirstChild();
						if (subChild)
						{
							if (subChild->Type() == TiXmlNode::TINYXML_TEXT)
							{
								char* Info = new char[strlen(subChild->Value()) + 1];
								strncpy_s(Info, strlen(subChild->Value()) + 1, subChild->Value(), strlen(subChild->Value()));
								metadata->setInfo(Info);
							}
						}
					}
				}
			}
			
		}
	}
	for (pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		Parse(pChild);
	}
	return true;
}

Metadata* TRSInfo::getMetadata()
{
	return metadata;
}

bool TRSInfo::setMetadata(Metadata*metadata_)
{
	metadata = metadata_;
	return true;
}

char* TRSInfo::getRepeat()
{
	return repeat;
}

char* TRSInfo::getMaxTime()
{
	return maxTime;
}

bool TRSInfo::setMaxThreads(char* maxThreads_)
{
	if (maxThreads)
	{
		delete[] maxThreads;
		maxThreads = new char[strlen(maxThreads_)+1];
		strncpy_s(maxThreads, strlen(maxThreads_) + 1, maxThreads_, strlen(maxThreads_));
		return true;
	}
	else
	{
		if (maxThreads = new char[strlen(maxThreads_)+1])
		{
			strncpy_s(maxThreads, strlen(maxThreads_) + 1, maxThreads_, strlen(maxThreads_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool TRSInfo::setMaxTime(char*maxTime_)
{
	if (maxTime)
	{
		delete[] maxTime;
		maxTime = new char[strlen(maxTime_) + 1];
		strncpy_s(maxTime, strlen(maxTime_) + 1, maxTime_, strlen(maxTime_));
		return true;
	}
	else
	{
		if (maxTime = new char[strlen(maxTime_) + 1])
		{
			strncpy_s(maxTime, strlen(maxTime_) + 1, maxTime_, strlen(maxTime_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool TRSInfo::setExecutableName(char*exeName)
{
	if (executableName)
	{
		delete[] executableName;
		executableName = new char[strlen(exeName) + 1];
		strncpy_s(executableName, strlen(exeName) + 1, exeName, strlen(exeName));
		return true;
	}
	else
	{
		if (executableName = new char[strlen(exeName) + 1])
		{
			strncpy_s(executableName, strlen(exeName) + 1, exeName, strlen(exeName));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool TRSInfo::setExpectedResult(char* res)
{
	if (expectedResult)
	{
		delete[] expectedResult;
		expectedResult = new char[strlen(res) + 1];
		strncpy_s(expectedResult, strlen(res) + 1, res, strlen(res));
		return true;
	}
	else
	{
		if (expectedResult = new char[strlen(res) + 1])
		{
			strncpy_s(expectedResult, strlen(res) + 1, res, strlen(res));
			return true;
		}
		else
		{
			return false;
		}
	}
}