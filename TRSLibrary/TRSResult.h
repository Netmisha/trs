#ifndef TRSResult_H_
#define TRSResult_H_

#ifdef TRSLibrary_EXPORT
#define TRSResult_API  __declspec(dllexport) 
#else
#define TRSResult_API  __declspec(dllimport) 
#endif

#include <iostream>

class TRSResult_API TRSResult
{
public:
	TRSResult(char* path, char* name, bool);
	~TRSResult();

	inline char* get_path()
	{
		return path_;
	}
	inline char* get_name()
	{
		return name_;
	}
	inline bool get_result()
	{
		return result_;
	}

	friend TRSResult_API std::ostream& operator<<(std::ostream&, TRSResult&);
private:
	char* path_;
	char* name_;
	bool result_;
};


#endif