#ifndef SUITE_ROOT_H
#define SUITE_ROOT_H
#include "afxwin.h"
#include "afxcmn.h"
#include <string.h>

class SuiteRoot
{
public:
	SuiteRoot()
	{
		dRoot = nullptr;
	}
	SuiteRoot(TCHAR* path)
	{
		int size = wcslen(path);
		dRoot = new TCHAR[size + 1];
		wcscpy_s(dRoot, size + 1, path);
	}
	SuiteRoot(CString path)
	{
		int size = _tcslen(path);
		dRoot = new TCHAR[size + 1];
		_tcscpy_s(dRoot, size + 1, path);
	}
	SuiteRoot(const SuiteRoot& var)
	{
		int size = wcslen(var.dRoot);
		dRoot = new TCHAR[size + 1];
		wcscpy_s(dRoot, size + 1, var.dRoot);
	}
	//SuiteRoot(const SuiteRoot&& var)
	//{
	//	int size = wcslen(var.dRoot);
	//	dRoot = new TCHAR[size + 1];
	//	wcscpy_s(dRoot, size + 1, var.dRoot);
	//}
	SuiteRoot operator=(const SuiteRoot& var)
	{
		if (this != &var)
		{
			int size = wcslen(var.dRoot);
			dRoot = new TCHAR[size + 1];
			wcscpy_s(dRoot, size + 1, var.dRoot);
		}
		return *this;
	}

	inline TCHAR* get_path()
	{
		return dRoot;
	}
	bool operator==(const SuiteRoot& var)
	{
		return !_tccmp(dRoot, var.dRoot);
	}// _tcscmp!!!

	~SuiteRoot()
	{
		delete[] dRoot;
	}
private:
	TCHAR* dRoot;
};

#endif