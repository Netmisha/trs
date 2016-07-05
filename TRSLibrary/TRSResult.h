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
	TRSResult(const TRSResult&);
	~TRSResult();

	inline char* get_path() const
	{
		return path_;
	}
	inline char* get_name() const
	{
		return name_;
	}
	inline bool get_result() const
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