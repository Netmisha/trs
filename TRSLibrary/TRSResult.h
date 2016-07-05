#ifndef TRSResult_H_
#define TRSResult_H_

#ifdef TRSLibrary_EXPORT
#define TRSResult_API  __declspec(dllexport) 
#else
#define TRSResult_API  __declspec(dllimport) 
#endif

class TRSResult_API TRSResult
{
public:
	TRSResult(char*, char*, bool);

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
private:
	char* path_;
	char* name_;
	bool result_;
};


#endif