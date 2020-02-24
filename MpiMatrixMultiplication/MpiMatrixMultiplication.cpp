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
#define RESULT_FILE_NAME "MpiTest.txt"
//double start_time, end_time;
//start_time = MPI_Wtime();
//Think about using MPI_Barrier();
//Use MPI_Gather();
//Use MPI_type_vector() & MPI_commit()

int main(int argc, char** argv)
{
	int taskId, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskId);

	MatrixClass matrix1 = FromFile(RESULT_FILE_PATH, FILE_NAME1, "Data");
	MatrixClass matrix2 = FromFile(RESULT_FILE_PATH, FILE_NAME2, "Data");

	try
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
		
		MatrixClass* rankResult;
		
		try
		{
			rankResult = MultiplyMatrix(*A, *B, size, taskId);
		}
		catch (runtime_error& e)
		{
			exit(1);
		}
		catch (...)
		{
			exit(2);
		}
		auto testVector = From2DTo1D(rankResult->GetMatrixAll());

		auto maxCapacity = ComputeMaxMatrixCapacity(A->GetDemensionI(), size);
		auto vectorOfDoubles = CreateMpiVectorTypeOfDoubles(1, 10, 0);

		
		auto rBufVector = vector<double>((size*maxCapacity)*B->GetDemensionJ());
		auto rBufVectorCapacity = vector<int>(size);
		//ToDo: substitute testCapacityValue on single call in MPI_Gather
		auto testCapacityValue = rankResult->GetDemensionI();

		
		
		MPI_Gather(&testCapacityValue, 1, MPI_INT, rBufVectorCapacity.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);
		//ToDo: redundant rBufVector capacity
		MPI_Gather(testVector.data(), maxCapacity, vectorOfDoubles, rBufVector.data(), maxCapacity, vectorOfDoubles, 0, MPI_COMM_WORLD);
		if (taskId == 0) 
		{
			auto file = CreateNewFile(RESULT_FILE_PATH, "TestVectorOverMPI.txt", false);
			TryWriteToFile(file, rBufVector);
			auto fileCapacity = CreateNewFile(RESULT_FILE_PATH, "CapacityValuesMPI.txt", false);
			TryWriteToFile(fileCapacity, rBufVectorCapacity);

			
		}
		
	}
	catch (const char* msg)
	{
		cout << msg;
	}

	cout << " Number of process = " << size << "   My rank = " << taskId << endl;
	MPI_Finalize();
	system("pause");
	return 0;
}


