#ifndef FUNCTIONALITY_H_
#define FUNCTIONALITY_H_
#include <Windows.h>

void convertToTCHAR(TCHAR*dest, char* path);
char* convertToChar(TCHAR*path);
char* fromCStringToChar(CString string);
#endif