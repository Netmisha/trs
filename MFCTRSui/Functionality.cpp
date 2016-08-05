#include "stdafx.h"
#include "Functionality.h"
#include <list>

#include "TRSLibrary\TRSManager.h"




void convertToTCHAR(TCHAR*dest, const char* path)
{
	if (dest != nullptr && path != nullptr)
	{
		TCHAR help = path[0];
		int i = 0;
		while (help)
		{
			dest[i] = help;
			++i;
			help = path[i];
		}
		dest[i] = '\0';
	}
}

char* convertToChar(TCHAR*path)//create buffer to set info to tinyXML doc constructor
{
	char* buf = new char[MAX_PATH];
	char help = path[0];
	int i = 0;
	while (help)//i tried to use memcpy,but it didn't work so i used while=(
	{
		buf[i] = help;
		++i;
		help = path[i];
	}
	buf[i] = '\0';
	return buf;
}

char* fromCStringToChar(CString string)
{
	char* buf = new char[string.GetLength()+1];
	char help = string[0];
	int i = 0;
	while (help)//i tried to use memcpy,but it didn't work so i used while=(
	{
		buf[i] = help;
		++i;
		help = string[i];
	}
	buf[i] = '\0';
	return buf;
}

bool ValidateProjXML(char* path)
{
	TiXmlDocument doc(path);
	if (doc.LoadFile())
	{
		TiXmlNode* first = doc.FirstChild();
		while (first->Type() != TiXmlNode::TINYXML_ELEMENT)
		{
			first = first->NextSibling();
		}
		if (!strncmp(first->Value(), "TRSProject", strlen(first->Value())))
		{
			TiXmlAttribute* art = first->ToElement()->FirstAttribute();
			if (!art)
				return false;
			if (strncmp(art->Name(), "name", 4))
			{
				return false;
			}
			art = art->Next();
			if (art)
			{
				if (strncmp(art->Name(), "ProjectPath", 11))
				{
					return false;
				}
			}
			else
			{
				return false;
			}
			TiXmlNode* head = first->FirstChild();
			for (head; head != 0; head = head->NextSibling())
			{
				if (strncmp(head->Value(), "path",strlen(head->Value())))
				{
					if (strncmp(head->Value(), "ListSelection", strlen("ListSelection")))
					{
						if (strncmp(head->Value(), "tag", strlen("tag")))
						{
							if (strncmp(head->Value(), "threads", strlen("threads")))
							{
								if (strncmp(head->Value(), "testName", strlen("testName")))
								{
									return false;
								}
							}
						}
					}
				}
			}
			return true;
		}
		return false;
	}
	return false;
}
BOOL validate(UINT nType, int cxx, int cyy)
{
	static int counter = 0;
	int a = cxx + cyy;
	for (int i = 0; i < counter; ++i)
	{
		int a = cxx * 2 + cyy - nType;
	}
	++counter;
	return counter * 3 + cxx != a - cyy + 6;
}

bool CheckForModification(char* path, char* name, CListBox* List,CComboBox* tag_,CComboBox* threads_,CComboBox* name_)
{
	TiXmlDocument doc(path);
	bool check = false;
	bool threadsCheck = false;
	bool nameCheck = false;
	if (doc.LoadFile())
	{
		TiXmlNode* first = doc.FirstChild();
		while (first->Type() != TiXmlNode::TINYXML_ELEMENT)
		{
			first = first->NextSibling();
		}
		if (!strncmp(first->Value(), "TRSProject", strlen(first->Value())))
		{
			TiXmlAttribute* atr = first->ToElement()->FirstAttribute();
			if (strncmp(atr->Value(), name, strlen(name)))
			{
				return false;
			}
			TiXmlNode* head = first->FirstChild();
			int i;
			int count = List->GetCount();
			for (head,i=0; head != 0; head = head->NextSibling(),++i)
			{
				if (!strncmp(head->Value(), "path", strlen(head->Value())))
				{
					if (i < count)
					{
						TiXmlNode* text = head->FirstChild();
						while (text->Type() != TiXmlNode::TINYXML_TEXT)
						{
							text = text->NextSibling();
						}
						CString buffer;
						List->GetText(i, buffer);
						char* p = fromCStringToChar(buffer);
						if (strncmp(text->Value(), p, strlen(p)))
						{
							return false;
						}
						delete[] p;
					}
				}
				if (!strncmp(head->Value(), "ListSelection", strlen("ListSelection")))
				{
					--i;
					int count = List->GetSelCount();
					TiXmlNode* subList = head->FirstChild();
					for (subList; subList != 0; subList = subList->NextSibling())
					{
						TiXmlNode* text = subList->FirstChild();
						if (!List->GetSel(atoi(text->Value())))
						{
							return false;
						}
						--count;
					}
					if (count != 0)
					{
						return false;
					}
				}
				if (!strncmp(head->Value(), "tag", strlen("tag")))
				{
					--i;
					check = true;
					TiXmlNode* text = head->FirstChild();
					if (atoi(text->Value()) != tag_->GetCurSel())
					{
						return false;
					}
				}
				if (!strncmp(head->Value(), "threads", strlen("threads")))
				{
					--i;
					threadsCheck = true;
					TiXmlNode* text = head->FirstChild();
					if (atoi(text->Value()) != threads_->GetCurSel())
					{
						return false;
					}
				}
				if (!strncmp(head->Value(), "testName", strlen("testName")))
				{
					--i;
					nameCheck = true;
					TiXmlNode* text = head->FirstChild();
					if (atoi(text->Value()) != name_->GetCurSel())
					{
						return false;
					}
				}
			}
			if (i != count)
			{
				return false;
			}
			if (!check)
			{
				if (tag_->GetCurSel())
				{
					return false;
				}
			}
			if (!threadsCheck)
			{
				if (threads_->GetCurSel())
				{
					return false;
				}
			}
			if (!nameCheck)
			{
				if (name_->GetCurSel())
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
	return false;
}