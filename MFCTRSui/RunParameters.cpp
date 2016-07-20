#include "stdafx.h"
#include "RunParameters.h"

RunParameters::RunParameters(char* path_, char* name_, char*tag_, unsigned int threads_, ReportManager* manager_)
{
	path = new char[strlen(path_) + 1];
	int count = 0;
	char current = path_[count];
	while (current)
	{
		path[count] = current;
		++count;
		current = path_[count];
	}
	path[count] = '\0';
	int size;
	if (name_)
	{
		size = strlen(name_);
		name = new char[size + 1];
		strncpy_s(name, size + 1, name_, size);
	}
	if (tag_)
	{
		size = strlen(tag_);
		tag = new char[size + 1];
		strncpy_s(tag, size + 1, tag, size);
	}
	threads = threads_;

	reporter = manager_;
}

RunParameters& RunParameters::operator=(RunParameters&cur)
{
	path = cur.path;
	name = cur.name;
	tag = cur.tag;
	threads = cur.threads;
	reporter = cur.reporter;

	return *this;
}