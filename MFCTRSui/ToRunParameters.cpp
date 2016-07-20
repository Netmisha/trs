#include "stdafx.h"
#include "ToRunParameters.h"

ToRunParameters::ToRunParameters(std::vector<SuiteRoot> coll_, ReportManager* manager_)
{
	coll = coll_;
	manager = manager_;
}