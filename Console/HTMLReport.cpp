#include "stdafx.h"
#include "HTMLReport.h"

HTMLReport::HTMLReport()
{
	output.open("Report.html");
	output << R"(<!DOCTYPE html>
<html>
<head>
<style>
table, th, td {
    border: 1px solid black;
    border-collapse: collapse;
}
th, td ,{
    padding: 5px;
    text-align: left;
}

</style>
</head>
<body>

<table style="width:100%">
  <h1>Test Report</h1></br>
	<font>Date:)";
	SYSTEMTIME time;
	GetLocalTime(&time);
	if (time.wDay < 10)
	{
		output << "0" << time.wDay;
	}
	else
	{
		output << time.wDay;
	}
	output << ".";
	if (time.wMonth < 10)
	{
		output << "0" << time.wMonth;
	}
	else
	{
		output << time.wMonth;
	}
	output << "." << time.wYear << " at " << time.wHour << ":" << time.wMinute << ":" << time.wSecond << std::endl << std::endl;
	output << "</font></br>";
	
	output<<R"(
<tr>
	<th>Number</th>
    <th>Name</th>
    <th>Info</th>
	<th>Description</th>
	<th>Path</th>
	<th>Duration</th>
  </tr>)";
	time_ = 0;
	amount = 0;
	passedAmount = 0;
	failedAmount = 0;
}

HTMLReport::~HTMLReport()
{
	
	//std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	output << "<font>Summary:</font></br>";
	output << "<font>Tests amount: " << (int)amount << "</font></br>";
	output << "<font>Passed: " << (int)passedAmount << "(" << int((passedAmount / amount) * 100) << "%)"<<"</font></br>";
	output << "<font>Failed: " << (int)failedAmount << "(" << int((failedAmount / amount) * 100) << "%)" << "</font></br>";
	output << "<font>Total time: " << (time_ /1000)/600<< " min.</font></br></br>";
	output << R"(</table>)";
	output << "</body>\n</html>";
	output.close();
}

void HTMLReport::Begin()
{
	
}

void HTMLReport::End()
{

}

void HTMLReport::BeforeExecution(TRSInfo pInfo)
{
	
}

void HTMLReport::ErrorOutput()
{
	output << R"(<font color="red">AN ERROR OCCURED</font></br>)";
}

void HTMLReport::AfterExecution(TRSInfo pInfo, TRSResult pResult)
{
	output << "<tr>\n\t<td>" << mCount << "</td>";
	++mCount;
	output << "<td>" << pResult.get_name() << "</td>\n\t" ;
	++amount;
	time_ += pResult.get_duration().count();
	if (pResult.get_result())
	{
		output << R"(<td><font color="green">Passed</font></td>)";
		++passedAmount;
	}
	else
	{
		output << R"(<td><font color="red">Failed</font></td>)";
		++failedAmount;
	}
	output << "<td>" << pResult.get_description() << "</td>";
	output<< "\n\t<td>" << pResult.get_path() << "</td>\n\t<td>"<<pResult.get_duration().count()<<"</td>\n\t</tr>";
}
