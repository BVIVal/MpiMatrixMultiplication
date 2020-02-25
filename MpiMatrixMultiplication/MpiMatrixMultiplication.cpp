#include <iostream>
#include "mpi.h"
#include <fstream>
#include "MatrixUtilities.h"
#include "ComputeUtilities.h"
#include "MpiUtilities.h"
#include "VectorUtilities.h"

using namespace std;

#define FILE_NAME1 "EntryMatrixDouble1.dat"
#define FILE_NAME2 "EntryMatrixDouble2.dat"
#define RESULT_FILE_PATH "C:\\Users\\Public\\Pictures"
#define RESULT_FILE_NAME "MpiResult.txt"

int main(int argc, char** argv)
{
	int taskId, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskId);
	
	auto executionStartedTimePoint = StartTimer();
	
	MatrixClass matrix1;
	MatrixClass matrix2;
	try
	{
		matrix1 = FromFile(RESULT_FILE_PATH, FILE_NAME1, "Data");
		matrix2 = FromFile(RESULT_FILE_PATH, FILE_NAME2, "Data");
	}
	catch (...)
	{
		exit(2);
	}
	
	if (matrix1.GetMatrixAll().empty() || matrix2.GetMatrixAll().empty()) exit(1);
	double computingStartedTimePoint;
	double computingTime;
	try
	{
		MatrixClass* rankResult;
		
		try
		{
			computingStartedTimePoint = StartTimer();
			rankResult = MultiplyMatrix(matrix1, matrix2, size, taskId);
			computingTime = StopTimer(computingStartedTimePoint);
		}
		catch (runtime_error&)
		{
			exit(1);
		}
		catch (...)
		{
			exit(2);
		}
		auto rankResultVector = From2DTo1D(rankResult->GetMatrixAll());

		auto maxCapacity = ComputeMaxMatrixCapacity(matrix1.GetDemensionI(), size);
		auto vectorOfDoubles = CreateMpiVectorTypeOfDoubles(1, matrix1.GetDemensionJ(), 0);
		auto rBufVector = vector<double>((size*maxCapacity)*matrix2.GetDemensionJ());
		auto rBufVectorCapacity = vector<int>(size);
		//ToDo: substitute testCapacityValue on single call in MPI_Gather
		auto testCapacityValue = rankResult->GetDemensionI();
		
		MPI_Gather(&testCapacityValue, 1, MPI_INT, rBufVectorCapacity.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);
		//ToDo: redundant rBufVector capacity
		MPI_Gather(rankResultVector.data(), maxCapacity, vectorOfDoubles, rBufVector.data(), maxCapacity, vectorOfDoubles, 0, MPI_COMM_WORLD);
		if (taskId == 0) 
		{
			auto file = CreateNewFile(RESULT_FILE_PATH, "MpiTestVectorOver.txt", false);
			TryWriteToFile(file, rBufVector);
			auto fileCapacity = CreateNewFile(RESULT_FILE_PATH, "MpiCapacityValues.txt", false);
			TryWriteToFile(fileCapacity, rBufVectorCapacity);
			
			auto result = MatrixClass::FromMpiGatherVectorToMatrixClass(rBufVector, rBufVectorCapacity, rankResult->GetDemensionJ());
			
			auto resultFile = CreateNewFile(RESULT_FILE_PATH, RESULT_FILE_NAME, false);
			TryWriteToFile(resultFile, result.GetMatrixAll());
		}
		
	}
	catch (const char* msg)
	{
		cout << msg;
	}
	auto executionTime = StopTimer(executionStartedTimePoint);
	cout << "Time of the program execution = " << executionTime << endl;
	cout << "Time of computing = " << computingTime << endl;
	cout << " Number of processes = " << size << "   My rank = " << taskId << endl;
	MPI_Finalize();
	std::system("pause");
	return 0;
}


