#include "stdafx.h"
#include <string>
#include "TinyXML\tinyxml.h"
#include <Windows.h>
#include "Suite.h"

extern const unsigned int NUM_INDENTS_PER_SPACE;

bool Validate(std::wstring&);
char* convertToChar( TCHAR*);
void convertToTCHAR(TCHAR*,char*);
void dump_to_stdout(TiXmlNode* pParent, std::list<Suite>& suiteList,char*dir,unsigned int indent = 0);
const char * getIndent(unsigned int numIndents);
const char * getIndentAlt(unsigned int numIndents);
int dump_attribs_to_stdout(TiXmlElement* pElement, Suite*curSuite,unsigned int indent);
