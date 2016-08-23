#ifndef FUNCTIONALITY_H_
#define FUNCTIONALITY_H_
#include <Windows.h>
#include "TRSLibrary\TinyXML\tinyxml.h"


void convertToTCHAR(TCHAR*dest, const char* path);
char* convertToChar(TCHAR*path);
char* fromCStringToChar(CString string);
bool ValidateProjXML(char* path);
bool CheckForModification(char* path, char* name, CListCtrl*List,CComboBox* Tag,CComboBox* threads,CComboBox* name_,bool Console);
BOOL validate(UINT nType, int cxx, int cyy);
DWORD UniqueNumber();
#endif