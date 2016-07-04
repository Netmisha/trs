#include "stdafx.h"
#include "FunctionalityForXML.h"

bool Validate(std::wstring& name)//just check ;last 3 letters
{
	if (name[name.length() - 1] == 'l')
	{
		if (name[name.length() - 2] == 'm')
		{
			if (name[name.length() - 3] == 'x')
			{
				if (name[name.length() - 4] == '.')
				{
					return true;
				}
			}
		}
	}
	return false;
}

const char * getIndent(unsigned int numIndents)
{
	static const char * pINDENT = "                                      + ";
	static const unsigned int LENGTH = strlen(pINDENT);
	unsigned int n = numIndents*NUM_INDENTS_PER_SPACE;
	if (n > LENGTH) n = LENGTH;

	return &pINDENT[LENGTH - n];
}

// same as getIndent but no "+" at the end
const char * getIndentAlt(unsigned int numIndents)
{
	static const char * pINDENT = "                                        ";
	static const unsigned int LENGTH = strlen(pINDENT);
	unsigned int n = numIndents*NUM_INDENTS_PER_SPACE;
	if (n > LENGTH) n = LENGTH;

	return &pINDENT[LENGTH - n];
}

int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent)//search for attributes
{
	if (!pElement) return 0;

	TiXmlAttribute* pAttrib = pElement->FirstAttribute();
	int i = 0;
	int ival;
	double dval;
	const char* pIndent = getIndent(indent);
	printf("\n");
	while (pAttrib)
	{
		printf("%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());

		if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS)    printf(" int=%d", ival);
		if (pAttrib->QueryDoubleValue(&dval) == TIXML_SUCCESS) printf(" d=%1.1f", dval);
		printf("\n");
		i++;
		pAttrib = pAttrib->Next();
	}
	return i;
}



void dump_to_stdout(TiXmlNode* pParent, std::list<Suite>&suitList, char* dirName,unsigned int indent)//check all XML-file tags and output everything
{
	if (!pParent) return;

	TiXmlNode* pChild;
	TiXmlText* pText;
	Suite* currentSuite;
	int t = pParent->Type();
	printf("%s", getIndent(indent));
	int num;

	switch (t)
	{
	case TiXmlNode::TINYXML_DOCUMENT:
		printf("Document");
		break;

	case TiXmlNode::TINYXML_ELEMENT:
		printf("Element [%s]", pParent->Value());
		if (pParent->Value() == "suite")
		{
			TiXmlAttribute*atr = pParent->ToElement()->FirstAttribute();
			char*name = new char[strlen(atr->Value())];
			strncpy_s(name, strlen(atr->Value()), atr->Value(), strlen(atr->Value()));
			atr = atr->Next();
			char*desc = new char[strlen(atr->Value())];
			strncpy_s(desc, strlen(atr->Value()), atr->Value(), strlen(atr->Value()));
			currentSuite = new Suite(name, desc, dirName);
		}
		num = dump_attribs_to_stdout(pParent->ToElement(), indent + 1);
		switch (num)
		{
		case 0:  printf(" (No attributes)");  break;
		case 1:  printf("%s1 attribute", getIndentAlt(indent)); 
			
			break;
		default: printf("%s%d attributes", getIndentAlt(indent), num);
			
			break;
		}
		break;

	case TiXmlNode::TINYXML_COMMENT:
		printf("Comment: [%s]", pParent->Value());
		break;

	case TiXmlNode::TINYXML_UNKNOWN:
		printf("Unknown");
		break;

	case TiXmlNode::TINYXML_TEXT:
		pText = pParent->ToText();
		printf("Text: [%s]", pText->Value());
		break;

	case TiXmlNode::TINYXML_DECLARATION:
		printf("Declaration");
		break;
	default:
		break;
	}
	printf("\n");
	for (pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		dump_to_stdout(pChild,suitList,dirName);
	}
}

char* convertToChar( TCHAR*path)//create buffer to set info to tinyXML doc constructor
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

void convertToTCHAR(TCHAR*dest,char* path)
{
	if (dest != nullptr)
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