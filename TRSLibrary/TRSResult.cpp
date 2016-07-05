#include "stdafx.h"
#define TRSLibrary_EXPORT
#include "TRSResult.h"

TRSResult::TRSResult(char* path, char* name, bool result) : path_(path), name_(name), result_(result)
{

}