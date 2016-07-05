#include "stdafx.h"
#include "CppUnitTest.h"
#include "TRSLibrary\TRSManager.h"
#include <list>
#include <vector>

#define AMOUNT_OF_TESTS 18U
#define FIRST_BRANCH_AMOUNT 6U
#define SECOND_BRANCH_AMOUNT 7U
#define THIRD_BRANCH_AMOUNT 5U
#define MAX_TEST_NAME_LENGHT 10U
#define SUCCEED_TESTS 9U


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_CLASS_INITIALIZE(TestsInitialization)
		{
			Manager.Init();
		}
		
		TEST_CLASS_CLEANUP(TestsCleanUp)
		{
			Manager.Destroy();
		}

		//========================================================================================
		//========================================================================================
		TEST_METHOD(ListTest_Names)
		{
			std::list<Suite> list = Manager.List(R"(../TestData/TestStrcuture)", nullptr, nullptr);

			Assert::AreEqual(list.size(), AMOUNT_OF_TESTS);
			
			char name[MAX_TEST_NAME_LENGHT];

			std::list<Suite>::iterator iter = list.begin();
			int i = 1;
			for (; i <= FIRST_BRANCH_AMOUNT; ++iter, ++i)
			{
				sprintf(name, "Test %d", i);
				int cmp_result = strcmp(name, iter->getName());
				Assert::IsTrue(cmp_result == 0);
			}

			for (i = 1; i <= SECOND_BRANCH_AMOUNT; ++iter, ++i)
			{
				sprintf(name, "Test %d", i);
				int cmp_result = strcmp(name, iter->getName());
				Assert::IsTrue(cmp_result == 0);
			}

			for (i = 1; i <= THIRD_BRANCH_AMOUNT; ++iter, ++i)
			{
				sprintf(name, "Test %d", i);
				int cmp_result = strcmp(name, iter->getName());
				Assert::IsTrue(cmp_result == 0);
			}
		}



		TEST_METHOD(ListTest_TotalAmountRoot)
		{
			std::list<Suite> list = Manager.List(R"(../TestData/TestStrcuture)", nullptr, nullptr);
		
			Assert::AreEqual(list.size(), AMOUNT_OF_TESTS);
		}

		TEST_METHOD(ListTest_TotalAmountBranch1)
		{
			std::list<Suite> list = Manager.List(R"(../TestData/TestStrcuture/Suite1)", nullptr, nullptr);

			Assert::AreEqual(list.size(), FIRST_BRANCH_AMOUNT);
		}
		TEST_METHOD(ListTest_TotalAmountBranch11)
		{
			std::list<Suite> list = Manager.List(R"(../TestData/TestStrcuture/Suite1/Suite1)", nullptr, nullptr);

			Assert::AreEqual(list.size(), 5U);
		}
		TEST_METHOD(ListTest_TotalAmountBranch111)
		{
			std::list<Suite> list = Manager.List(R"(../TestData/TestStrcuture/Suite1/Suite1/Suite1)", nullptr, nullptr);

			Assert::AreEqual(list.size(), 2U);
		}

		TEST_METHOD(ListTest_TotalAmountBranch2)
		{
			std::list<Suite> list = Manager.List(R"(../TestData/TestStrcuture/Suite2)", nullptr, nullptr);

			Assert::AreEqual(list.size(), SECOND_BRANCH_AMOUNT);
		}

		TEST_METHOD(ListTest_TotalAmountBranch3)
		{
			std::list<Suite> list = Manager.List(R"(../TestData/TestStrcuture/Suite3)", nullptr, nullptr);

			Assert::AreEqual(list.size(), THIRD_BRANCH_AMOUNT);
		}
		//=============================================================================================================
		//=============================================================================================================

		TEST_METHOD(RunTest_Result)
		{
			std::vector<TRSResult> run_result = Manager.Run(R"(../TestData/TestStrcuture)", nullptr, nullptr);


			unsigned succeed_counter = 0;
			for each (auto val in run_result)
			{
				if (val.get_result() == true)
					++succeed_counter;
			}
			Assert::AreEqual(succeed_counter, SUCCEED_TESTS);
		}

		TEST_METHOD(RunTest_TotalAmountRoot)
		{
			std::vector<TRSResult> run_result = Manager.Run(R"(../TestData/TestStrcuture)", nullptr, nullptr);

			Assert::AreEqual(run_result.size(), AMOUNT_OF_TESTS);
		}

		TEST_METHOD(RunTest_TotalAmountBranch1)
		{
			std::vector<TRSResult> run_result = Manager.Run(R"(../TestData/TestStrcuture/Suite1)", nullptr, nullptr);

			Assert::AreEqual(run_result.size(), FIRST_BRANCH_AMOUNT);
		}
		TEST_METHOD(RunTest_TotalAmountBranch11)
		{
			std::vector<TRSResult> run_result = Manager.Run(R"(../TestData/TestStrcuture/Suite1/Suite1)", nullptr, nullptr);

			Assert::AreEqual(run_result.size(), 5U);
		}
		TEST_METHOD(RunTest_TotalAmountBranch111)
		{
			std::vector<TRSResult> run_result = Manager.Run(R"(../TestData/TestStrcuture/Suite1/Suite1/Suite1)", nullptr, nullptr);

			Assert::AreEqual(run_result.size(), 2U);
		}

		TEST_METHOD(RunTest_TotalAmountBranch2)
		{
			std::vector<TRSResult> run_result = Manager.Run(R"(../TestData/TestStrcuture/Suite2)", nullptr, nullptr);

			Assert::AreEqual(run_result.size(), SECOND_BRANCH_AMOUNT);
		}

		TEST_METHOD(RunTest_TotalAmountBranch3)
		{
			std::vector<TRSResult> run_result = Manager.Run(R"(../TestData/TestStrcuture/Suite3)", nullptr, nullptr);

			Assert::AreEqual(run_result.size(), THIRD_BRANCH_AMOUNT);
		}
	};
}