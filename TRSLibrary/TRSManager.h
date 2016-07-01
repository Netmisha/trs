
class TRSManager
{
public:
	TRSManager();
	~TRSManager();
	bool Init();
	bool Verify(char* path, char* name, char* tag);
	bool Run(char* path, char* name, char* tag);
	bool Pause(char* path, char* name, char* tag);
	bool Stop(char* path, char* name, char* tag);
	bool List(char* path, char* name, char* tag);
	bool Status(char* path, char* name, char* tag);
	bool Info(char* path, char* name, char* tag);
	bool Destroy(char* path, char* name, char* tag);
};