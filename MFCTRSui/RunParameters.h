#ifndef RENPARAMETERS_H_
#define RUNPARAMETERS_H_
#include "TRSLibrary\ReportManager.h"
#include <Windows.h>
struct RunParameters
{
	char* path=nullptr;
	char* name = nullptr;
	char* tag = nullptr;
	unsigned int threads;
	ReportManager* reporter;
	RunParameters(){}
	RunParameters(char* path_, char* name_, char*tag_, unsigned int threads_, ReportManager* manager_);
	RunParameters& operator=(RunParameters&cur);
};

#endif