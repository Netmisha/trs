#ifndef SUITE_ROOT_H
#define SUITE_ROOT_H
#include "afxwin.h"
#include "afxcmn.h"

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
	inline TCHAR* get_path()
	{
		return dRoot;
	}

	~SuiteRoot()
	{
		delete[] dRoot;
	}
private:
	TCHAR* dRoot;
};

#endif