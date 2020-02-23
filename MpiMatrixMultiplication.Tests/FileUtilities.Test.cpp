#include "CppUnitTest.h"

#include "MatrixUtilities.h"
#include "ComputeUtilities.h"


#define FILE_NAME1 "EntryMatrixDouble1.dat"
#define FILE_NAME2 "EntryMatrixDouble2.dat"
#define RESULT_FILE_PATH "C:\\Users\\Public\\Pictures"
#define RESULT_FILE_NAME "MpiTest.txt"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MpiMatrixMultiplicationTests
{
	TEST_CLASS(FileUtilitiesTests)
	{
	public:

		TEST_METHOD(TryWriteToFileTest)
		{
			auto testValue = new MatrixClass(2, 3, { {2,3,3},{3,4,5} });
			ofstream* file;
			try
			{
				file = CreateNewFile(RESULT_FILE_PATH, "MpiTryWriteVectorTest.txt", false);
			}
			catch (runtime_error& e)
			{
				//File cann't exist or already open
				Assert::Fail();
			}
			catch(...)
			{
				Assert::Fail();
			}
			for (auto vector : testValue->GetMatrixAll())
			{
				TryWriteToFile(file, vector);
			}

			//ToDo:: to do over ReadFileStream
			Assert::IsTrue(true);
		}

		
	};
}
