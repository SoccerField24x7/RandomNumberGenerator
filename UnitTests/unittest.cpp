#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JAQRandomNumGen/RandomNumberGenerator.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	
	TEST_CLASS(UnitTests)
	{
	public:

		static std::vector<long> tstArray;
		
		TEST_CLASS_INITIALIZE(setup)
		{
			tstArray[0] = 300;
			tstArray[1] = 456789;
			tstArray[2] = 300;
			tstArray[3] = 400;
			tstArray[4] = 400;
			tstArray[5] = 1010;
			tstArray[6] = 1;
			tstArray[7] = 1117;
			tstArray[8] = 12;
			tstArray[9] = 727;
		}	

		TEST_METHOD(GenerateSingleNumber)
		{
			RandomNumberGenerator *rng = new RandomNumberGenerator();
			long val = rng->GenerateNumber();
			
			Assert::IsTrue(val > 0);
			Assert::IsTrue(val <= 10);
		}

		TEST_METHOD(GenerateMultipleNumbers)
		{
			RandomNumberGenerator *rng = new RandomNumberGenerator();
			std::vector<long> vals = rng->GenerateMultiple(10000);

			Assert::IsTrue(vals.size() == 10000);
		}

		TEST_METHOD(SortIncorrectMethod)
		{			
			bool exceptionThrown = false;
			RandomNumberGenerator *rng = new RandomNumberGenerator();
					
			try
			{
				rng->SortResults(tstArray, "TEST");
			}
			catch (const std::exception& ex)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(SortCaseInsensitive)
		{
			RandomNumberGenerator *rng = new RandomNumberGenerator();
			bool exceptionThrown = false;
			try {
				rng->SortResults(tstArray, "dEsC");
			}
			catch (const std::exception &ex)
			{
				exceptionThrown = true;
			}

			Assert::IsFalse(exceptionThrown);
		}

		TEST_METHOD(GetUniqueNumbers)
		{
			RandomNumberGenerator *rng = new RandomNumberGenerator();
			std::vector<long> trimmed = rng->GetUniqueNumbers(tstArray);
			Assert::IsTrue(trimmed.size() == 8);
		}

		TEST_METHOD(InitRange)
		{
			RandomNumberGenerator *rng = new RandomNumberGenerator();
			Assert::IsTrue(rng->GetRangeHigh() == 10);
			Assert::IsTrue(rng->GetRangeLow() == 1);
		}

		TEST_METHOD(InitWithParamsRange)
		{
			RandomNumberGenerator *rng = new RandomNumberGenerator(-3,5555);
			Assert::IsTrue(rng->GetRangeHigh() == 5555);
			Assert::IsTrue(rng->GetRangeLow() == -3);
		}

		TEST_METHOD(SortNoSortMethod)
		{
			RandomNumberGenerator *rng = new RandomNumberGenerator();
			std::vector<long> result = rng->SortResults(tstArray);

			Assert::IsTrue(result[0] == 1); //should default to ASC and 1 is the 
		}
		TEST_METHOD(SortDesc)
		{
			RandomNumberGenerator *rng = new RandomNumberGenerator();
			std::vector<long> result = rng->SortResults(tstArray, "DESC");

			Assert::IsTrue(result[0] == 456789);
		}

		TEST_METHOD(TopNumbers)
		{
			RandomNumberGenerator *rng = new RandomNumberGenerator();
			std::vector<long> result = rng->GetTopNumbers(tstArray);
			Assert::IsTrue(result.size() == 2);
			Assert::IsTrue(result[0] == 400);
			Assert::IsTrue(result[1] == 300);
		}
	};

	std::vector<long> UnitTests::tstArray = std::vector<long>(10);
}