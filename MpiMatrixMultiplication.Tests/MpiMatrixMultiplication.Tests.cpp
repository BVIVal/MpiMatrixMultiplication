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
	TEST_CLASS(MpiMatrixMultiplicationTests)
	{
	public:
		
		TEST_METHOD(TransposeTest)
		{
			auto testValue = new MatrixClass(2, 3, { {2,3,3},{3,4,5} });
			auto newValue = MatrixClass::Transpose(*testValue);

			
			Assert::IsTrue(AreVectorsEqual(vector<vector<double>> { {2, 3}, { 3,4 }, { 3,5 }},newValue.GetMatrixAll(), 0.01));
		}
		
		TEST_METHOD(MultiplyMatrixTest)
		{
			auto A = new MatrixClass(2, 3, { 
				{2,3,3},
				{3,4,5}
			});
			auto B = new MatrixClass(3, 2, { 
				{2,3},
				{3,4},
				{3,5}
			});
			MatrixClass* result;
			try
			{
				result = MultiplyMatrix(*A, *B);
			}
			catch (runtime_error& e)
			{
				Assert::Fail();
			}
			catch (...)
			{
				Assert::Fail();
			}
			
			Assert::IsTrue(AreVectorsEqual(vector<vector<double>>{ {22.0,33.0},{33.0,50.0}}, result->GetMatrixAll(), 0.01));
		}

		TEST_METHOD(MultiplyBigMatrixTest)
		{
			auto A = new MatrixClass(10, 10,
				{
					{2, 3, 3, 53, 78.83, 789, 2, 3, 7, 8},
					{3, 4, 5, 76.863, 2.69, 3, 2, 9, 0, 1.11},
					{2, 4, 5, 8, 8, 21, 1, 5, 6, 7},
					{7, 8, 9, 2, 5, 11, 8, 7, 67, 8},
					{7, 9.23, 723, 7, 2, 78, 0.11, 736, 7, 0.22},
					{1, 33, 7, 6, 9.86, 7, 2, 57, 7, 8},
					{7, 234, 561, 54.67, 0.24, 82.88, 12, 1.223, 0.689, 986},
					{92, 6235, 6, 2.87, 235, 692, 528, 2, 5, 2},
					{8, 235, 6.975, 2, 1.969, 256, 8698, 23, 5, 6},
					{9, 5, 0.986, 2, 1, 23, 8, 2, 1, 7}
				});
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
			MatrixClass* result;
			try
			{
				result = MultiplyMatrix(*A, *B);
			}
			catch (runtime_error& e)
			{
				Assert::Fail();
			}
			catch (...)
			{
				Assert::Fail();
			}
			auto expectedResult = vector<vector<double>>
			{
				{73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97},
				{637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45},
				{2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44},
				{1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44},
				{13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59},
				{1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66},
				{21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92},
				{113447.61, 4500316.53, 4522105.15, 50315.04, 177511.85, 1106195.89, 4980089.59, 4609747.16, 67270.03, 14690.07},
				{94974.608, 3645537.952, 236257.84, 22113.71, 79614.71, 2442460.747, 75842929.302, 375530.31, 46895.07, 59953.09},
				{2315.9, 147259.88, 4521.48, 730.5, 5618.15, 21882.72, 142851.38, 6091.21, 478.06, 1226.63}
			};
				
			
			auto answer = AreVectorsEqual(expectedResult, result->GetMatrixAll(), 20);
			vector<vector<double>> deltaResult;
			if (!answer) deltaResult = ComputeDelta(expectedResult, result->GetMatrixAll());
			Assert::IsTrue(answer);
		}

		TEST_METHOD(Task3MultiplyMatrixTest)
		{
			int commSize = 3;
			
			auto A = new MatrixClass(10, 10,
				{
					{2, 3, 3, 53, 78.83, 789, 2, 3, 7, 8},
					{3, 4, 5, 76.863, 2.69, 3, 2, 9, 0, 1.11},
					{2, 4, 5, 8, 8, 21, 1, 5, 6, 7},
					{7, 8, 9, 2, 5, 11, 8, 7, 67, 8},
					{7, 9.23, 723, 7, 2, 78, 0.11, 736, 7, 0.22},
					{1, 33, 7, 6, 9.86, 7, 2, 57, 7, 8},
					{7, 234, 561, 54.67, 0.24, 82.88, 12, 1.223, 0.689, 986},
					{92, 6235, 6, 2.87, 235, 692, 528, 2, 5, 2},
					{8, 235, 6.975, 2, 1.969, 256, 8698, 23, 5, 6},
					{9, 5, 0.986, 2, 1, 23, 8, 2, 1, 7}
				});
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
			MatrixClass* firstRankResult;
			MatrixClass* secondRankResult;
			MatrixClass* thirdRankResult;
			try
			{
				firstRankResult = MultiplyMatrix(*A, *B, commSize, 0);
				secondRankResult = MultiplyMatrix(*A, *B, commSize, 1);
				thirdRankResult = MultiplyMatrix(*A, *B, commSize, 2);
			}
			catch (runtime_error& e)
			{
				Assert::Fail();
			}
			catch (...)
			{
				Assert::Fail();
			}
			auto expectedFirstRankResult = vector<vector<double>>
			{
				{73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97},
				{1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44},
				{21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92},
				{2315.9, 147259.88, 4521.48, 730.5, 5618.15, 21882.72, 142851.38, 6091.21, 478.06, 1226.63}
			};
			auto expectedSecondRankResult = vector<vector<double>>
			{
				{637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45},
				{13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59},
				{113447.61, 4500316.53, 4522105.15, 50315.04, 177511.85, 1106195.89, 4980089.59, 4609747.16, 67270.03, 14690.07}
			};
			auto expectedThirdRankResult = vector<vector<double>>
			{
				{2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44},
				{1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66},
				{94974.608, 3645537.952, 236257.84, 22113.71, 79614.71, 2442460.747, 75842929.302, 375530.31, 46895.07, 59953.09},
			};
			Assert::IsTrue(AreVectorsEqual(expectedFirstRankResult, firstRankResult->GetMatrixAll(), 20));
			Assert::IsTrue(AreVectorsEqual(expectedSecondRankResult, secondRankResult->GetMatrixAll(), 20));
			Assert::IsTrue(AreVectorsEqual(expectedThirdRankResult, thirdRankResult->GetMatrixAll(), 20));
			
			
			auto expectedResult = vector<vector<double>>
			{
				{73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97},
				{637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45},
				{2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44},
				{1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44},
				{13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59},
				{1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66},
				{21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92},
				{113447.61, 4500316.53, 4522105.15, 50315.04, 177511.85, 1106195.89, 4980089.59, 4609747.16, 67270.03, 14690.07},
				{94974.608, 3645537.952, 236257.84, 22113.71, 79614.71, 2442460.747, 75842929.302, 375530.31, 46895.07, 59953.09},
				{2315.9, 147259.88, 4521.48, 730.5, 5618.15, 21882.72, 142851.38, 6091.21, 478.06, 1226.63}
			};

			/*auto outErrorIndex = vector<vector<size_t>>(1, vector<size_t>(1));
			auto answer = AreVectorsEqual(expectedResult, result->GetMatrixAll(), 20, outErrorIndex);
			vector<vector<double>> deltaResult;
			if (!answer) deltaResult = ComputeDelta(expectedResult, result->GetMatrixAll());
			Assert::IsTrue(answer);*/
			Assert::IsTrue(false);
		}
	};
}
