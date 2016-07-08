#include "TRSManager.h"
#include "ProcessCollection.h"
#include "Suite.h"
#include "ProcessInfo.h"

#include <list>



class SuitCollection
{
public:
	SuitCollection(const std::list<Suite> &);

	bool Run();
private:
	ProcessInfo GetNext();
private:
	std::list<ProcessCollection> suits_;
};