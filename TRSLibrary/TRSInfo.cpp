#include "stdafx.h"

#define TRSLibrary_EXPORT
#include "TRSInfo.h"
#include <iostream>
TRSInfo::TRSInfo(char*TestName, char*Description) 
{
	if (Name&&description)
	{
		int size = strlen(TestName);
		int count = strlen(Description);
		Name = new char[size];
		strncpy_s(Name, size, TestName, size);
		description = new char[count];
		strncpy_s(description, count + 1, Description, count);
	}
}

TRSInfo::TRSInfo(const TRSInfo& val)
{
	if (val.metadata != nullptr)
	{
		metadata = new Metadata(*val.metadata);
	}
	if (val.path != nullptr)
	{
		int size = strlen(val.path);
		path = new char[size + 1];
		strncpy_s(path, size + 1, val.path, size);
	}
	if (val.executablePath != nullptr)
	{
		int size = strlen(val.executablePath);
		executablePath = new char[size + 1];
		strncpy_s(executablePath, size + 1, val.executablePath, size);
	}
	if (val.disable != nullptr)
	{
		int size = strlen(val.disable);
		disable = new char[size + 1];
		strcpy_s(disable, size + 1, val.disable);
	}
	if (val.priority != nullptr)
	{
		int size = strlen(val.priority);
		priority = new char[size + 1];
		strcpy_s(priority, size + 1, val.priority);
	}
	if (val.executableName != nullptr)
	{
		int size = strlen(val.executableName);
		executableName = new char[size + 1];
		strcpy_s(executableName, size + 1, val.executableName);
	}
	if (val.description != nullptr)
	{
		int size = strlen(val.description);
		description = new char[size + 1];
		strcpy_s(description, size + 1, val.description);
	}
	if (val.expectedResult != nullptr)
	{
		int size = strlen(val.expectedResult);
		expectedResult = new char[size + 1];
		strcpy_s(expectedResult, size + 1, val.expectedResult);
	}
	if (val.maxThreads != nullptr)
	{
		int size = strlen(val.maxThreads);
		maxThreads = new char[size + 1];
		strcpy_s(maxThreads, size + 1, val.maxThreads);
	}
	if (val.maxTime != nullptr)
	{
		int size = strlen(val.maxTime);
		maxTime = new char[size + 1];
		strcpy_s(maxTime, size + 1, val.maxTime);
	}
	if (val.Name != nullptr)
	{
		int size = strlen(val.Name);
		Name = new char[size + 1];
		strcpy_s(Name, size + 1, val.Name);
	}
	if (val.repeat != nullptr)
	{
		int size = strlen(val.repeat);
		repeat = new char[size + 1];
		strcpy_s(repeat, size + 1, val.repeat);
	}
	if (val.tag != nullptr)
	{
		int size = strlen(val.tag);
		tag = new char[size + 1];
		strcpy_s(tag, size + 1, val.tag);
	}
	if (val.waitfor != nullptr)
	{
		int size = strlen(val.waitfor);
		waitfor = new char[size + 1];
		strcpy_s(waitfor, size + 1, val.waitfor);
	}
	if (val.parameters != nullptr)
	{
		int size = strlen(val.parameters);
		parameters = new char[size + 1];
		strcpy_s(parameters, size + 1, val.parameters);
	}
}

TRSInfo::TRSInfo()
{
	metadata = new Metadata;
}

TRSInfo::~TRSInfo()
{
	delete metadata;
	delete[] Name;
	delete[] description;
	delete[] tag;
	delete[] repeat;
	delete[] maxTime;
	delete[] maxThreads;
	delete[] waitfor;
	delete[] expectedResult;
	delete[] executableName;
	delete[] priority;
	delete[] disable;
	delete[] parameters;
	delete[] executablePath;
	delete[] path;
}

char* TRSInfo::getName() const
{
	return Name;
}
char* TRSInfo::getWaitFor() const
{
	return waitfor;
}
char* TRSInfo::getParameters() const
{
	return parameters;
}

char* TRSInfo::getDescription() const
{
	return description;
}

char* TRSInfo::getMaxThreads() const
{ 
	return maxThreads;
}

char* TRSInfo::getTag() const
{
	return tag;
}

char* TRSInfo::getDisable() const
{
	return disable;
}

char* TRSInfo::getExecutablePath() const
{
	if (parameters&&executablePath&&executableName)
	{
		int sizePath = strlen(executablePath);
		int sizeName = strlen(executableName);
		int sizeParam = strlen(parameters);
		char* result = new char[sizePath + sizeName + sizeParam + 2];
		strncpy_s(result, sizePath + 1, executablePath, sizePath);
		strncpy_s(result + sizePath, sizeName + 1, executableName, sizeName);

		
		DWORD dwAttrib = GetFileAttributesA(result);
		if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
		{
			delete[] result;
			return nullptr;
		}
		else
		{
			strncpy_s(result + sizePath + sizeName + 1, 2, " ", 1);
			strncpy_s(result + sizePath + sizeName + 2, sizeParam + 1, parameters, sizeParam);
			return result;
		}
	}
	else
	{
		if (parameters&&!executablePath&&executableName)
		{
			int sizePath = strlen(path);
			int sizeName = strlen(executableName);
			int sizeParam = strlen(parameters);
			char* result = new char[sizePath + sizeParam + sizeName + 2];
			strncpy_s(result, sizePath + 1, path, sizePath);
			strncpy_s(result + sizePath, sizeName + 1, executableName, sizeName);
			strncpy_s(result + sizePath + sizeName, 2, " ", 1);
			strncpy_s(result + sizePath + sizeName + 1, sizeParam + 1, parameters, sizeParam);
			return result;
		}
		if (executablePath&&!parameters&&executableName)
		{
			int sizePath = strlen(executablePath);
			int sizeName = strlen(executableName);
			char* result = new char[sizePath + sizeName + 2];
			strncpy_s(result, sizePath + 1, executablePath, sizePath);
			strncpy_s(result + sizePath, sizeName + 1, executableName, sizeName);
			return result;
		}
		if (!parameters&&!executablePath&&executableName)
		{
			int sizePath = strlen(path);
			int sizeName = strlen(executableName);
			int sizeParam = strlen(parameters);
			char* result = new char[sizePath + sizeName + 1];
			strncpy_s(result, sizePath + 1, path, sizePath);
			strncpy_s(result + sizePath, sizeName + 1, executableName, sizeName);
			strncpy_s(result + sizeName + sizeParam, sizeParam + 1, parameters, sizeParam);

			return result;
		}
	}
}

char* TRSInfo::getPath() const
{
	return path;
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

bool TRSInfo::setParameters(char*parameters_)
{
	if (parameters)
	{
		delete[] parameters;
		parameters = new char[strlen(parameters_) + 1];
		strncpy_s(parameters, strlen(parameters_) + 1, parameters_, strlen(parameters_));
		return true;
	}
	else
	{
		if (parameters = new char[strlen(parameters_) + 1])
		{
			strncpy_s(parameters, strlen(parameters_) + 1, parameters_, strlen(parameters_));
			return true;
		}
	}
	return false;
}

bool TRSInfo::setDisable(char*disable_)
{
	if (disable)
	{
		delete[] disable;
		disable = new char[strlen(disable_) + 1];
		strncpy_s(disable, strlen(disable_) + 1, disable_, strlen(disable_));
		return true;
	}
	else
	{
		if (disable = new char[strlen(disable_) + 1])
		{
			strncpy_s(disable, strlen(disable_) + 1, disable_, strlen(disable_));
			return true;
		}
	}
	return false;
}

bool TRSInfo::setWaitFor(char* wait_)
{
	if (waitfor)
	{
		delete[] waitfor;
		waitfor = new char[strlen(wait_) + 1];
		strncpy_s(tag, strlen(wait_) + 1, wait_, strlen(wait_));
		return true;
	}
	else
	{
		if (waitfor = new char[strlen(wait_) + 1])
		{
			strncpy_s(waitfor, strlen(wait_) + 1, wait_, strlen(wait_));
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
			
			if (getName())
			{
				return true;
			}
			TiXmlAttribute*atr = pParent->ToElement()->FirstAttribute();

			if (!strncmp(atr->Name(),"name",strlen("name")))
			{
				char*name = new char[strlen(atr->Value()) + 1];
				strncpy_s(name, strlen(atr->Value()) + 1, atr->Value(), strlen(atr->Value()));
				setName(name);
				delete[] name;
				atr = atr->Next();
				if (atr)
				{
					if (!strncmp(atr->Name(), "description", strlen("description")) )
					{
						char*desc = new char[strlen(atr->Value()) + 1];
						strncpy_s(desc, strlen(atr->Value()) + 1, atr->Value(), strlen(atr->Value()));
						setDescription(desc);
						delete[] desc;
					}
				}
			}	
			if (!strncmp(atr->Name(), "description", strlen("description")))
			{
				char*desc = new char[strlen(atr->Value()) + 1];
				strncpy_s(desc, strlen(atr->Value()) + 1, atr->Value(), strlen(atr->Value()));
				setDescription(desc);
				delete[] desc;
			}
			break;
		}
		if ((strncmp(pParent->Value(), "tag", strlen("tag")) == 0))
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				if (child)
				{
					if (strlen(child->Value()) > 0)
					{
						char*Tag = new char[strlen(child->Value()) + 1];
						strncpy_s(Tag, strlen(child->Value()) + 1, child->Value(), strlen(child->Value()));
						setTag(Tag);
						delete[] Tag;
					}
				}
			}
			break;
		}
		if ((strncmp(pParent->Value(), "parameters", strlen("parameters")) == 0))
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				if (child)
				{
					if (strlen(child->Value()) > 0)
					{
						char*Parameters = new char[strlen(child->Value()) + 1];
						strncpy_s(Parameters, strlen(child->Value()) + 1, child->Value(), strlen(child->Value()));
						setParameters(Parameters);
						delete[] Parameters;
					}
				}
			}
			break;
		}
		if ((strncmp(pParent->Value(), "priority", strlen("priority")) == 0))
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				if (child)
				{
					if (strlen(child->Value()) > 0)
					{
						char*Priority = new char[strlen(child->Value()) + 1];
						strncpy_s(Priority, strlen(child->Value()) + 1, child->Value(), strlen(child->Value()));
						setPriority(Priority);
						delete[] Priority;
					}
				}
			}
			break;
		}
		if ((strncmp(pParent->Value(), "waitFor", strlen("waitFor")) == 0) &&getName())
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child && child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				if (strlen(child->Value()) > 0)
				{
					char *wait = new char[strlen(child->Value()) + 1];
					strncpy_s(wait, strlen(child->Value()) + 1, child->Value(), strlen(child->Value()));
					setWaitFor(wait);
					delete[] wait;
				}
			}
			break;
		}
		if ((strncmp(pParent->Value(), "disable", strlen("disable")) == 0) &&getName())
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child && child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				if (strlen(child->Value()) > 0)
				{
					char *dis = new char[strlen(child->Value()) + 1];
					strncpy_s(dis, strlen(child->Value()) + 1, child->Value(), strlen(child->Value()));
					setDisable(dis);
					delete[] dis;
				}
			}
			break;
		}
		if ((strncmp(pParent->Value(), "repeat", strlen("repeat")) == 0)&&getName())
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				if (child)
				{
					if (strlen(child->Value()) > 0)
					{
						char*Repeat = new char[strlen(child->Value()) + 1];
						strncpy_s(Repeat, strlen(child->Value()) + 1, child->Value(), strlen(child->Value()));
						setRepeat(Repeat);
						delete[] Repeat;
					}
				}
			}
			break;
		}
		if ((strncmp(pParent->Value(), "maxTime", strlen("maxTime")) == 0) &&getName())
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child)
			{
				if (child->Type() == TiXmlNode::TINYXML_TEXT)
				{
					if (child)
					{
						if (strlen(child->Value()) > 0)
						{
							char*MaxTime = new char[strlen(child->Value()) + 1];
							strncpy_s(MaxTime, strlen(child->Value()) + 1, child->Value(), strlen(child->Value()));
							setMaxTime(MaxTime);
							delete[] MaxTime;
						}
					}
				}
			}
			break;
		}
		if ((strncmp(pParent->Value(), "maxThreads", strlen("maxThreads")) == 0)&&getName())
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				if (child)
				{
					if ((strlen(child->Value()) > 0)&&atoi(child->Value())>0)
					{
						char*MaxThreads = new char[strlen(child->Value()) + 1];
						strncpy_s(MaxThreads, strlen(child->Value()) + 1, child->Value(), strlen(child->Value()));
						setMaxThreads(MaxThreads);
						delete[] MaxThreads;
					}
				}
			}
			break;
		}
		if ((strncmp(pParent->Value(), "execution", strlen("execution")) == 0) &&getName())
		{
			TiXmlAttribute*atr = pParent->ToElement()->FirstAttribute();
			
			if (atr)
			{
				if ((!strncmp(atr->Name(), "path", strlen("path"))))
				{
					if (atr->Value())
					{
						char*executablePath_ = new char[strlen(atr->Value()) + 1];
						strncpy_s(executablePath_, strlen(atr->Value()) + 1, atr->Value(), strlen(atr->Value()));
						setExecutablePath(executablePath_);
						delete[] executablePath_;
					}
				}
			}
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				if (child)
				{
					if (strlen(child->Value()) > 0)
					{
						
						
							char*executableName = new char[strlen(child->Value()) + 1];
							strncpy_s(executableName, strlen(child->Value()) + 1, child->Value(), strlen(child->Value()));
							setExecutableName(executableName);
							delete[] executableName;
						
					}
				}
			}
			break;
		}
		if ((strncmp(pParent->Value(), "result", strlen("result")) == 0)&&getName())
		{
			TiXmlNode* child = pParent->FirstChild();
			if (child->Type() == TiXmlNode::TINYXML_TEXT)
			{
				if (child)
				{
					if (strlen(child->Value()) > 0)
					{
						char*Res = new char[strlen(child->Value()) + 1];
						strncpy_s(Res, strlen(child->Value()) + 1, child->Value(), strlen(child->Value()));
						setExpectedResult(Res);
						delete[] Res;
					}
				}
			}
			break;
		}
		if ((strncmp(pParent->Value(), "metadata", strlen("metadata")) == 0) &&getName())
		{
			
			for (TiXmlNode* child = pParent->FirstChild(); child != 0; child = child->NextSibling())
			{
				if (child->Type() == TiXmlNode::TINYXML_ELEMENT)
				{
					TiXmlNode* subChild;
					if (strncmp(child->Value(),"author",strlen("author"))==0)
					{
						subChild = child->FirstChild();
						if (subChild)
						{
							if (subChild->Type() == TiXmlNode::TINYXML_TEXT)
							{
								if (strlen(subChild->Value()) > 0)
								{
									char* name = new char[strlen(subChild->Value()) + 1];
									strncpy_s(name, strlen(subChild->Value()) + 1, subChild->Value(), strlen(subChild->Value()));
									metadata->setName(name);
									delete[] name;
								}
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
								delete[] Date;
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
								delete[] Version;
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
								delete[] Mail;
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
								delete[] Copyright;
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
								delete[] License;
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
								delete[] Info;
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

Metadata* TRSInfo::getMetadata()  const
{
	return metadata;
}

bool TRSInfo::setMetadata(Metadata*metadata_)
{
	metadata = metadata_;
	return true;
}

char* TRSInfo::getRepeat()  const
{
	return repeat;
}

char* TRSInfo::getMaxTime()  const
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

bool TRSInfo::setPath(char* path_)
{
	if (path)
	{
		delete[] path;
		path = new char[strlen(path_) + 1];
		strncpy_s(path, strlen(path_) + 1, path_, strlen(path_));
		return true;
	}
	else
	{
		if (path = new char[strlen(path_) + 1])
		{
			strncpy_s(path, strlen(path_) + 1, path_, strlen(path_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool TRSInfo::setExecutablePath(char* path)
{
	if (executablePath)
	{
		delete[] executablePath;
		executablePath = new char[strlen(path) + 1];
		strncpy_s(executablePath, strlen(path) + 1, path, strlen(path));
		return true;
	}
	else
	{
		if (executablePath = new char[strlen(path) + 1])
		{
			strncpy_s(executablePath, strlen(path) + 1, path, strlen(path));
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

bool TRSInfo::setPriority(char* prior)
{
	if (priority)
	{
		delete[] priority;
		priority = new char[strlen(prior) + 1];
		strncpy_s(priority, strlen(prior) + 1, prior, strlen(prior));
		return true;
	}
	else
	{
		if (priority = new char[strlen(prior) + 1])
		{
			strncpy_s(priority, strlen(prior) + 1, prior, strlen(prior));
			return true;
		}
		else
		{
			return false;
		}
	}
}

char* TRSInfo::getPriority() const
{
	return priority;
}