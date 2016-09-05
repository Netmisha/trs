#ifndef TORUNPARAMETERS_H_
#define TORUNPARAMETERS_H_
#include <vector>
#include <MFCTRSui\MFCTRSuiDlg.h>
#include "TRSLibrary\ReportManager.h"
#include "SuiteRoot.h"

struct ToRunParameters
{
	std::vector<SuiteRoot> coll;
	ReportManager* manager;
	CProgressCtrl* progress;
	CProgressCtrl* subProgress;
	CMFCTRSuiDlg* dialog;

//	ToRunParameters(std::vector<SuiteRoot> coll_, ReportManager* manager_, CProgressCtrl*progress, CProgressCtrl* subProgress);
};

#endif