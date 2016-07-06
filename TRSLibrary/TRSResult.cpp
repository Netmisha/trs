#include "stdafx.h"
#define TRSLibrary_EXPORT
#include "TRSResult.h"

TRSResult::TRSResult(char* path, char* name, bool result, duration<long long, std::milli> duration) 
: result_(result), duration_(duration)
{
	size_t path_size = strlen(path);
	path_ = new char[path_size + 1];
	strcpy_s(path_, path_size + 1, path);

	size_t name_size = strlen(name);
	name_ = new char[name_size + 1];
	strcpy_s(name_, name_size + 1, name);
}

TRSResult::TRSResult(const TRSResult& instance) : result_(instance.get_result()), duration_(instance.get_duration())
{
	size_t path_size = strlen(instance.get_path());
	path_ = new char[path_size + 1];
	strcpy_s(path_, path_size + 1, instance.get_path());

	size_t name_size = strlen(instance.get_name());
	name_ = new char[name_size + 1];
	strcpy_s(name_, name_size + 1, instance.get_name());
}

TRSResult::~TRSResult()
{
	// no harm will be if either of this pointers is nullptr

	delete[] name_;
	delete[] path_;
}

std::ostream& operator<<(std::ostream& out, TRSResult& instance)
{
	out << instance.get_name() << "  " << std::boolalpha << instance.get_result() << "  "<<instance.get_duration().count() << " msec  " << instance.get_path() ;
	return out;
}