
//#define BUFFER_SIZE 1024
#define FILE_NAME1 "EntryMatrixDouble1.dat"
#define FILE_NAME2 "EntryMatrixDouble2.dat"
#define RESULT_FILE_PATH "C:\\Users\\Public\\Pictures"
#define RESULT_FILE_NAME "MpiTest.txt"
//double start_time, end_time;
//start_time = MPI_Wtime();
//Think about using MPI_Barrier();
//Use MPI_Gather();
//Use MPI_type_vector() & MPI_commit()

//MPI_Status status;
//
//#define N 10
//double a[N][N], b[N][N], c[N][N];
//
//int GridSize; // Size of virtual processor grid 
//MatrixClass Transpose(MatrixClass& data);
//
//int main(int argc, char** argv) {
//
//	int numTasks, taskId, numworkers, source, dest, rows, offset, i, j, k;
//	SYSTEMTIME start, stop;
//
//	//getchar();
//	MatrixClass matrix1 = FromFile(FILE_NAME1, "\\Data\\");
//	MatrixClass matrix2 = FromFile(FILE_NAME2, "\\Data\\");
//	//ToDo: optimize matrix2 & transposedMatrix
//	MatrixClass transposedMatrix = Transpose(matrix2);
//
//
//	//getchar();
//
//	// Initialize the MPI environment.
//	MPI_Init(&argc, &argv);
//	// Get the number of processes
//	MPI_Comm_size(MPI_COMM_WORLD, &numTasks);
//	// Get the rank of the process
//	MPI_Comm_rank(MPI_COMM_WORLD, &taskId);
//
//	cout << "Hello World Process #" << taskId << '\n';
//
//	MPI_Status status1;
//	// for delete
//	try
//	{
//		int request;
//		int с[10] = { 1,0,0,0,0,0,0,0,0,1 };
//		int jk[10];
//		if (taskId == 0)
//		{
//			request = MPI_Send(&с[0], 10, MPI_INT, 1, 99, MPI_COMM_WORLD);
//			cout << "Request = ";
//			cout << request;
//		}
//		else if (taskId == 1)
//		{
//			MPI_Recv(&jk[0], 10, MPI_INT, 0, 99, MPI_COMM_WORLD, &status1);
//			ofstream File(R"(C:\Users\Public\Pictures)");
//			if(File.is_open())
//			{
//				for (int element : jk)
//				{
//					File << element << endl;
//				}
//				File.close();
//			}
//		}
//	}
//	catch (const char* msg)
//	{
//		cout << msg;
//	}
//
//	//
//
//	MPI_Finalize();
//	return 0;
//
//
//	numworkers = numTasks - 1;
//
//	vector<double> receivedRow;
//
//	// If Master
//	// Отправить каждому работнику транспонированную матрицу и отправить
//	// пакет "лент" из первой матрицы.
//	//
//
//	
//	if (taskId == 0) {
//		MPI_Send(&matrix1.Get(0), 500, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
//		MPI_Send(&transposedMatrix.Get(0), 500, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
//	}
//
//	//MPI_Status status1;
//	MPI_Status status2;
//	// If Worker
//	if (taskId > 0)
//	{
//		MPI_Recv(&receivedRow[0], 500, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status1);
//		MPI_Recv(&receivedRow[1], 500, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status2);
//	}
//
//	getchar();
//
//
//
//	/*---------------------------- worker----------------------------*/
//	if (taskId > 0) {
//		source = 0;
//		MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
//		MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
//		MPI_Recv(&a, rows * N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
//		MPI_Recv(&b, N * N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
//
//		/* Matrix multiplication */
//		for (k = 0; k < N; k++)
//			for (i = 0; i < rows; i++) {
//				c[i][k] = 0.0;
//				for (j = 0; j < N; j++)
//					c[i][k] = c[i][k] + a[i][j] * b[j][k];
//			}
//
//
//		MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
//		MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
//		MPI_Send(&c, rows * N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
//	}
//
//
//	// Finalize the MPI environment. No more MPI calls can be made after this
//	MPI_Finalize();
//
//	getchar();
//
//}
//


#include <iostream>
#include "mpi.h"
#include <fstream>
#include "MatrixUtilities.h"
#include "ComputeUtilities.h"

using namespace std;


int main(int argc, char** argv)
{
	int taskId, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskId);
	auto vectorSize = 5;

	MatrixClass matrix1 = FromFile(RESULT_FILE_PATH, FILE_NAME1, "Data");
	MatrixClass matrix2 = FromFile(RESULT_FILE_PATH, FILE_NAME2, "Data");
	//ToDo: checking on 2x3 & 3x2 - only calculate 500x500 or 2x2 (square matrices)
	/*if (taskId == 0)
	{
		auto file = CreateNewFile(RESULT_FILE_PATH, RESULT_FILE_NAME, true);
		if (!TryWriteToFile(file, GetVectorById(taskId, vectorSize, size)))	MpiErrorExit("TryWriteToFile: return false");

		if (!IsFileClosedSuccessfully(file)) MpiErrorExit("IsFileClosedSuccessfully: return false");

	}*/
	MPI_Status status1;
	try
	{
		int request;
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
		auto testSendVector = vector<double>
		{73451.81, 4923380.33, 9692.156, 7442.93, 186244.586, 552449.77, 504410.97, 6926.479, 9358.76, 5337.97};
		
		MPI_Datatype vectorOfDoubles;
		auto numberOfBlocks = 10;//ten values in one vector
		auto blockLength = 1;// one double-value
		auto stride = 1; // space between values
		MPI_Type_vector(numberOfBlocks, blockLength, stride, MPI_DOUBLE, &vectorOfDoubles);
		MPI_Type_commit(&vectorOfDoubles);

		vector<double> testVector = vector<double>(10);

		if(taskId == 0)
		{
			//MPI_Send(&testSendVector, 1, vectorOfDoubles, 1, 99, MPI_COMM_WORLD);
			MPI_Send(&testSendVector[0], 1, vectorOfDoubles, 1, 99, MPI_COMM_WORLD);
		}
		else if(taskId == 1)
		{
			MPI_Recv(&testVector[0], 1, vectorOfDoubles, 0, 99, MPI_COMM_WORLD, &status1);
			auto file = CreateNewFile(RESULT_FILE_PATH, "TestVectorOverMPI.txt", false);
			TryWriteToFile(file, testVector);
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

