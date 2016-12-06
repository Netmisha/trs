#ifndef TCHARPATHCONVERTER_H_
#define TCHARPATHCONVERTER_H_
#include <windows.h>
#include <strsafe.h>
TCHAR* convertPath(TCHAR*inPath);
char*  convertToChar(TCHAR*);
void  convertToTCHAR(TCHAR*, char*);
#endif