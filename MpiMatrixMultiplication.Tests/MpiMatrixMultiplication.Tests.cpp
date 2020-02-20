#include "pch.h"
#include "CppUnitTest.h"
#include "MatrixUtilities.h"
#include "ComputeUtilities.h"
//#include "../MpiMatrixMultiplication/Utilities/MatrixUtilities.h"
#/*include "MatrixUtilities.h"
#include "InputUtilities.h"*/

#define FILE_NAME1 "EntryMatrixDouble1.dat"
#define FILE_NAME2 "EntryMatrixDouble2.dat"
#define RESULT_FILE_PATH "C:\\Users\\Public\\Pictures"
#define RESULT_FILE_NAME "MpiTest.txt"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MpiMatrixMultiplicationTests
{
	TEST_CLASS(MpiMatrixMultiplicationTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			auto testValue = new MatrixClass(2, 3, { {2,3,3},{3,4,5} });
			auto newValue = MatrixClass::Transpose(*testValue);
			auto b = FromFile(RESULT_FILE_PATH, FILE_NAME1, "DATA");
			auto cTest = FromApplicationFolderFile(FILE_NAME1, "");

			//auto b = FromFile(RESULT_FILE_PATH, FILE_NAME1, "DATA");
			//auto cTest = FromApplicationFolderFile(FILE_NAME1, "");
			////autob
			Assert::IsTrue(true);
		}
		
	};
}
