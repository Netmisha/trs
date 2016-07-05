#include "stdafx.h"
#include "CppUnitTest.h"
#include "TRSLibrary\TRSManager.h"
#include <list>

#define AMOUNT_OF_TESTS 18
#define MAX_TEST_NAME_LENGHT 10

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(ListTest)
		{
			Manager.Init();

			std::list<Suite> list =
				Manager.List(R"(../TestData/TestStrcuture)", nullptr, nullptr);

			Assert::AreEqual(list.size(), (unsigned)AMOUNT_OF_TESTS);
			
			char name[MAX_TEST_NAME_LENGHT];
			bool result = true;

			std::list<Suite>::iterator iter = list.begin();
			int i = 1;
			for (; iter != list.end(); ++iter, ++i)
			{
				sprintf(name, "Test %d", i + 1);
				int cmp_result = strcmp(name, iter->getName());
				if (cmp_result != 0)
				{
					result = false;
					break;
				}
			}
			Manager.Destroy();

			Assert::IsTrue(result);
		}

	};
}