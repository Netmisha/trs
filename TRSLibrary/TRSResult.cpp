#include "stdafx.h"
#define TRSLibrary_EXPORT
#include "TRSResult.h"
//#include <iomanip>

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
<<<<<<< HEAD
	//delete[] name_;
	//delete[] path_;
=======
	delete[] name_;
	delete[] path_;
}

std::ostream& operator<<(std::ostream& out, TRSResult& instance)
{
	out << instance.get_path() << "  " << instance.get_name() << "  " << std::boolalpha << instance.get_result();

	return out;
>>>>>>> fa010d5cb344da2fde716b7de14e0bbd4ed22df6
}