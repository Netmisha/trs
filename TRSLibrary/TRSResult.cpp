#include "stdafx.h"
#define TRSLibrary_EXPORT
#include "TRSResult.h"

TRSResult::TRSResult(char* path, char* name, bool result) : result_(result)
{
	size_t path_size = strlen(path);
	path_ = new char[path_size + 1];
	strcpy_s(path_, path_size + 1, path);

	size_t name_size = strlen(name);
	name_ = new char[name_size + 1];
	strcpy_s(name_, name_size + 1, name);
}

TRSResult::~TRSResult()
{
	// no harm will be if either of this pointers is nullptr
	//delete[] name_;
	//delete[] path_;
}