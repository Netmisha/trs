#ifndef TESTSLISTVERIFYING_H_
#define TESTSLISTVERIFYING_H_
#include "TRSTest.h"
#include <vector>

int TestPosition(std::vector<TRSTest*> coll, char* testName);

bool VerifyTestsList(std::vector<TRSTest*>coll, int size, std::vector<char*>nameColl, int firstelem );
#endif