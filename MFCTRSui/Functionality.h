#ifndef FUNCTIONALITY_H_
#define FUNCTIONALITY_H_
#include <Windows.h>
void Info(char*path,CTreeCtrl tree);
void convertToTCHAR(TCHAR*dest, char* path);
char* convertToChar(TCHAR*path);
#endif