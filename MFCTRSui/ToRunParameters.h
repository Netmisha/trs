#ifndef TORUNPARAMETERS_H_
#define TORUNPARAMETERS_H_
#include <vector>
#include <MFCTRSui\MFCTRSuiDlg.h>
#include "TRSLibrary\ReportManager.h"
struct ToRunParameters
{
	std::vector<SuiteRoot> coll;
	ReportManager* manager;
	ToRunParameters(std::vector<SuiteRoot> coll_, ReportManager* manager_);
};

#endif