#ifndef TRSResult_H_
#define TRSResult_H_

#ifdef TRSLibrary_EXPORT
#define TRSResult_API  __declspec(dllexport) 
#else
#define TRSResult_API  __declspec(dllimport) 
#endif

#include <iostream>
#include <chrono>
using namespace std::chrono;


class TRSResult_API TRSResult
{
public:
	TRSResult(char* path, char* name, bool, duration<long long, std::milli>);
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
	inline duration<long long, std::milli> get_duration() const
	{
		return duration_;
	}

	friend TRSResult_API std::ostream& operator<<(std::ostream&, TRSResult&);
private:
	duration<long long, std::milli>  duration_;
	char* path_;
	char* name_;
	bool result_;
};


#endif