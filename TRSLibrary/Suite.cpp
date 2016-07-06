
#include"stdafx.h"
#define TRSLibrary_EXPORT
#include "Suite.h"

using std::ostream;

Suite::Suite(char*TestName, char*Description, char* DirName_) :TRSInfo(TestName, Description)
{
	directoryName = DirName_;
}

Suite::Suite() : TRSInfo()
{

}


Suite::~Suite() 
{
	

}

bool Suite::addTest(TRSTest& currentTest)
{
	testList.push_back(&currentTest);
	return true;
}

bool Suite::removeTest(char*testName)
{
	std::list<TRSTest*>::iterator it= testList.begin();
	for (it; it != testList.end(); ++it)
	{
		if (!strncmp(testName, (*it)->getName(), strlen(testName)))
		{
			testList.erase(it);
			return true;
		}
	}
	return false;
}

std::list<TRSTest*>& Suite::getList()
{
	return testList;
}

ostream& operator<<(ostream& out, Suite instance)
{
	std::list<TRSTest*> list = instance.getList();
	for each(auto val in list)
		out << val->getName()<<" ";
	return out;
}

bool Suite::Parse(TiXmlNode*pParent,char*name_,char*tag_)
{
	if (TRSInfo::Parse(pParent))
	{
		ParseSuit(pParent,name_,tag_);
		return true;
	}
	else
	{
		return false;
	}
}

bool Suite::setDir(char*dir_)
{
	if (directoryName)
	{
		delete[] directoryName;
		if (directoryName = new char[strlen(dir_) + 1])
		{
			strncpy_s(directoryName, strlen(dir_) + 1, dir_, strlen(dir_));
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (directoryName = new char[strlen(dir_) + 1])
		{
			strncpy_s(directoryName, strlen(dir_) + 1, dir_, strlen(dir_));
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Suite::setList(std::list<TRSTest*>& testList_)
{
	testList = testList_;
	if (testList.size() == testList_.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Suite::ParseSuit(TiXmlNode* pParent,char* name_,char* tag_)
{
	if (!pParent) return false;

	TiXmlNode* pChild;
	TiXmlText* pText;

	int t = pParent->Type();

	switch (t)
	{
	case TiXmlNode::TINYXML_ELEMENT:

		if ((strncmp(pParent->Value(), "test", strlen("test")) == 0))
		{
			
			TRSTest* currentTest = new TRSTest;
			currentTest->Parse(pParent);
			if (name_)
			{
				if (strlen(name_) > 0)
				{
					if (tag_)
					{
						if (strlen(tag_) > 0)
						{
							if (!strncmp(currentTest->getName(), name_, strlen(name_)) && !strncmp(currentTest->getTag(), tag_, strlen(tag_)))
							{
								getList().push_back(currentTest);
							}
						}
						else
						{
							if (!strncmp(currentTest->getName(), name_, strlen(name_)))
							{
								getList().push_back(currentTest);
							}
						}
					}
					else
					{
						if (!strncmp(currentTest->getName(), name_, strlen(name_)))
						{
							getList().push_back(currentTest);
						}
					}
				}
				else
				{
					if (tag_)
					{
						if (strlen(tag_) > 0)
						{
							if (!strncmp(currentTest->getName(), name_, strlen(name_)) && !strncmp(currentTest->getTag(), tag_, strlen(tag_)))
							{
								getList().push_back(currentTest);
							}
						}
					}
					else
					{
						if (!strncmp(currentTest->getName(), name_, strlen(name_)))
						{
							getList().push_back(currentTest);
						}
					}
				}
			}
			else
			{
				if (tag_)
				{
					if (strlen(tag_) > 0)
					{
						if (!strncmp(currentTest->getTag(),tag_,strlen(tag_)))
						{
							getList().push_back(currentTest);
						}
					}
					else
					{
						getList().push_back(currentTest);
					}
				}
				else
				{
					getList().push_back(currentTest);
				}
			}
			
		}
	}
	for (pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		ParseSuit(pChild,name_,tag_);
	}
	return true;
}