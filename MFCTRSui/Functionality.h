#ifndef FUNCTIONALITY_H_
#define FUNCTIONALITY_H_
#include <Windows.h>
#include "TRSLibrary\TinyXML\tinyxml.h"

void convertToTCHAR(TCHAR*dest, char* path);
char* convertToChar(TCHAR*path);
char* fromCStringToChar(CString string);
bool ValidateProjXML(char* path);
#endif