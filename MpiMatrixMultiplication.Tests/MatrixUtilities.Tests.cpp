#include "CppUnitTest.h"

#include "MatrixUtilities.h"
#include "ComputeUtilities.h"
#include "VectorUtilities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MpiMatrixMultiplicationTests
{
	TEST_CLASS(MatrixUtilitiesTests)
	{
	public:

		TEST_METHOD(FromMpiGatherVectorToMatrixClassTest)
		{
			
			auto expectedGatherVector = vector<vector<double>>
			{
				{73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97},
				{1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44},
				{21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92},
				{2315.9, 147259.88, 4521.48, 730.5, 5618.15, 21882.72, 142851.38, 6091.21, 478.06, 1226.63},
				{637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45},
				{13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59},
				{113447.61, 4500316.53, 4522105.15, 50315.04, 177511.85, 1106195.89, 4980089.59, 4609747.16, 67270.03, 14690.07},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
				{2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44},
				{1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66},
				{94974.608, 3645537.952, 236257.84, 22113.71, 79614.71, 2442460.747, 75842929.302, 375530.31, 46895.07, 59953.09},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
			};

			auto singleDemensionExpectedGatherVector = From2DTo1D(expectedGatherVector);
			auto capacityDemensionI = vector<int>{ 4,3,3 };
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

			auto result = MatrixClass::FromMpiGatherVectorToMatrixClass(singleDemensionExpectedGatherVector, capacityDemensionI, expectedGatherVector[0].size());

			Assert::IsTrue(AreVectorsEqual(expectedResult, result.GetMatrixAll(), 30));
		}

		TEST_METHOD(VectorToMatrixClassTest)
		{

			auto expectedGatherVector = vector<vector<double>>
			{
				{73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97, 73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97, 73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97, 73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97},
				{1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44, 1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44, 1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44, 1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44},
				{21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92, 21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92, 21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92, 21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92},
				{2315.9, 147259.88, 4521.48, 730.5, 5618.15, 21882.72, 142851.38, 6091.21, 478.06, 1226.63, 2315.9, 147259.88, 4521.48, 730.5, 5618.15, 21882.72, 142851.38, 6091.21, 478.06, 1226.63, 2315.9, 147259.88, 4521.48, 730.5, 5618.15, 21882.72, 142851.38, 6091.21, 478.06, 1226.63, 2315.9, 147259.88, 4521.48, 730.5, 5618.15, 21882.72, 142851.38, 6091.21, 478.06, 1226.63},
				{637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45, 637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45, 637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45, 637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45},
				{13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59, 13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59, 13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59, 13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59},
				{113447.61, 4500316.53, 4522105.15, 50315.04, 177511.85, 1106195.89, 4980089.59, 4609747.16, 67270.03, 14690.07, 113447.61, 4500316.53, 4522105.15, 50315.04, 177511.85, 1106195.89, 4980089.59, 4609747.16, 67270.03, 14690.07, 113447.61, 4500316.53, 4522105.15, 50315.04, 177511.85, 1106195.89, 4980089.59, 4609747.16, 67270.03, 14690.07, 113447.61, 4500316.53, 4522105.15, 50315.04, 177511.85, 1106195.89, 4980089.59, 4609747.16, 67270.03, 14690.07},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
				{2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44, 2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44, 2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44, 2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44},
				{1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66, 1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66, 1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66, 1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66},
				{94974.608, 3645537.952, 236257.84, 22113.71, 79614.71, 2442460.747, 75842929.302, 375530.31, 46895.07, 59953.09, 94974.608, 3645537.952, 236257.84, 22113.71, 79614.71, 2442460.747, 75842929.302, 375530.31, 46895.07, 59953.09, 94974.608, 3645537.952, 236257.84, 22113.71, 79614.71, 2442460.747, 75842929.302, 375530.31, 46895.07, 59953.09, 94974.608, 3645537.952, 236257.84, 22113.71, 79614.71, 2442460.747, 75842929.302, 375530.31, 46895.07, 59953.09},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
			};

			auto singleDemensionExpectedGatherVector = From2DTo1D(expectedGatherVector);
			auto capacityDemensionI = vector<int>{ 4,3,3 };
			auto expectedResult = vector<vector<double>>
			{
				{73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97, 73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97, 73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97, 73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97},
				{637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45, 637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45, 637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45, 637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45},
				{2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44, 2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44, 2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44, 2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44},
				{1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44, 1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44, 1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44, 1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44},
				{13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59, 13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59, 13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59, 13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59},
				{1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66, 1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66, 1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66, 1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66},
				{21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92, 21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92, 21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92, 21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92},
				{113447.61, 4500316.53, 4522105.15, 50315.04, 177511.85, 1106195.89, 4980089.59, 4609747.16, 67270.03, 14690.07, 113447.61, 4500316.53, 4522105.15, 50315.04, 177511.85, 1106195.89, 4980089.59, 4609747.16, 67270.03, 14690.07, 113447.61, 4500316.53, 4522105.15, 50315.04, 177511.85, 1106195.89, 4980089.59, 4609747.16, 67270.03, 14690.07, 113447.61, 4500316.53, 4522105.15, 50315.04, 177511.85, 1106195.89, 4980089.59, 4609747.16, 67270.03, 14690.07},
				{94974.608, 3645537.952, 236257.84, 22113.71, 79614.71, 2442460.747, 75842929.302, 375530.31, 46895.07, 59953.09, 94974.608, 3645537.952, 236257.84, 22113.71, 79614.71, 2442460.747, 75842929.302, 375530.31, 46895.07, 59953.09, 94974.608, 3645537.952, 236257.84, 22113.71, 79614.71, 2442460.747, 75842929.302, 375530.31, 46895.07, 59953.09, 94974.608, 3645537.952, 236257.84, 22113.71, 79614.71, 2442460.747, 75842929.302, 375530.31, 46895.07, 59953.09},
				{2315.9, 147259.88, 4521.48, 730.5, 5618.15, 21882.72, 142851.38, 6091.21, 478.06, 1226.63, 2315.9, 147259.88, 4521.48, 730.5, 5618.15, 21882.72, 142851.38, 6091.21, 478.06, 1226.63, 2315.9, 147259.88, 4521.48, 730.5, 5618.15, 21882.72, 142851.38, 6091.21, 478.06, 1226.63, 2315.9, 147259.88, 4521.48, 730.5, 5618.15, 21882.72, 142851.38, 6091.21, 478.06, 1226.63},
			};

			auto result = MatrixClass::FromMpiGatherVectorToMatrixClass(singleDemensionExpectedGatherVector, capacityDemensionI, expectedGatherVector[0].size());

			Assert::IsTrue(AreVectorsEqual(expectedResult, result.GetMatrixAll(), 30));
		}

		TEST_METHOD(SixProcesses)
		{

			auto expectedGatherVector = vector<vector<double>>
			{
				{73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97, 73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97, 73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97, 73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97},
				{21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92, 21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92, 21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92, 21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92},
				{637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45, 637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45, 637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45, 637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
				{2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44, 2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44, 2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44, 2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
				{1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44, 1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44, 1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44, 1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
				{13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59, 13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59, 13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59, 13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
				{1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66, 1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66, 1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66, 1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66},
				{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
			};

			auto singleDemensionExpectedGatherVector = From2DTo1D(expectedGatherVector);
			auto capacityDemensionI = vector<int>{ 2,1,1,1,1,1 };
			auto expectedResult = vector<vector<double>>
			{
				{73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97, 73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97, 73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97, 73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97},
				{637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45, 637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45, 637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45, 637.29, 21007.97, 6199.1, 6775.47, 1664.35, 10953.99, 28967.01, 4165.8, 362.143, 5164.45},
				{2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44, 2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44, 2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44, 2171, 134162.92, 6053.736, 1780.68, 5434.7, 21380.4, 80880.44, 4967.115, 785.53, 5160.44},
				{1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44, 1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44, 1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44, 1529, 74882.84, 11484.376, 6457.13, 3410.97, 18890.92, 145437.88, 9047.007, 714.5, 9236.44},
				{13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59, 13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59, 13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59, 13846.27, 657976.26, 415105.38, 80064.53, 76589.84, 693312.22, 54427.49, 10621.256, 6373.71, 719027.59},
				{1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66, 1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66, 1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66, 1228.02, 48242.47, 28231.458, 4716.71, 6312.47, 55514.62, 91005.51, 26648.581, 1399.49, 7542.66},
				{21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92, 21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92, 21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92, 21358.13, 884968.61, 491706.69, 39022.98, 22299.81, 378767.58, 8731398.43, 405950.41, 7586.54, 559494.92},
			};

			auto result = MatrixClass::FromMpiGatherVectorToMatrixClass(singleDemensionExpectedGatherVector, capacityDemensionI, expectedGatherVector[0].size());

			Assert::IsTrue(AreVectorsEqual(expectedResult, result.GetMatrixAll(), 30));
		}

	};
}