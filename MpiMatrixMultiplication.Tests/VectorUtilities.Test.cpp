#include "CppUnitTest.h"

#include "MatrixUtilities.h"
#include "ComputeUtilities.h"
#include "VectorUtilities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MpiMatrixMultiplicationTests
{
	TEST_CLASS(VectorUtilitiesTests)
	{
	public:

		TEST_METHOD(ConvertVector2DToVector1D)
		{
			auto B = new MatrixClass(10, 10,
				{
					{2, 3, 8.968, 23, 0.24, 7, 23, 55, 19.04, 9.999},
					{7, 9.23, 723, 7, 2, 78, 0.11, 736, 7, 0.22},
					{7, 234, 561, 54.67, 0.24, 82.88, 12, 1.223, 0.689, 986},
					{3, 4, 5, 76.863, 2.868, 3, 2, 9, 0, 1.11},
					{7, 8, 9, 2, 5, 11, 8, 7, 67, 8},
					{92, 6235, 6, 2.87, 235, 692, 528, 2, 5, 2},
					{8, 235, 6.975, 2, 1.969, 256, 8698, 23, 5, 6},
					{2, 3, 3, 53, 78.83, 786, 2, 3, 7, 8},
					{3, 4, 5, 76.863, 2.868, 3, 2, 9, 0, 1.11},
					{8, 235, 6.975, 2, 1.969, 256, 8698, 235, 5, 6}
				});
			
			auto expectedResult = vector<double>
			{
				2, 3, 8.968, 23, 0.24, 7, 23, 55, 19.04, 9.999,
				7, 9.23, 723, 7, 2, 78, 0.11, 736, 7, 0.22,
				7, 234, 561, 54.67, 0.24, 82.88, 12, 1.223, 0.689, 986,
				3, 4, 5, 76.863, 2.868, 3, 2, 9, 0, 1.11,
				7, 8, 9, 2, 5, 11, 8, 7, 67, 8,
				92, 6235, 6, 2.87, 235, 692, 528, 2, 5, 2,
				8, 235, 6.975, 2, 1.969, 256, 8698, 23, 5, 6,
				2, 3, 3, 53, 78.83, 786, 2, 3, 7, 8,
				3, 4, 5, 76.863, 2.868, 3, 2, 9, 0, 1.11,
				8, 235, 6.975, 2, 1.969, 256, 8698, 235, 5, 6
			};
			
			auto result = From2DTo1D(B->GetMatrixAll());

			Assert::IsTrue(AreVectorsEqual(expectedResult, result, 0));
		}


	};
}
