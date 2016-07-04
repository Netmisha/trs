#include "stdafx.h"
#include <string>
#include "TinyXML\tinyxml.h"
#include <Windows.h>
#include "Suite.h"

const unsigned int NUM_INDENTS_PER_SPACE = 2;

bool Validate(std::wstring&);
char* convertToChar( TCHAR*);
void convertToTCHAR(TCHAR*,char*);
void dump_to_stdout(TiXmlNode* pParent, unsigned int indent = 0);
const char * getIndent(unsigned int numIndents);
const char * getIndentAlt(unsigned int numIndents);
int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent);
