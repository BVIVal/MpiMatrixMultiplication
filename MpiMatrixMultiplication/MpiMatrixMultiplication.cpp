
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
#include "Utilities/StringUtilities.h"
#include "Utilities/FileUtilities.h"
#include "Utilities/InputUtilities.h"
#include "Utilities/MpiUtilities.h"

using namespace std;


int main(int argc, char** argv)
{
	int taskId, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskId);
	auto vectorSize = 5;

	MatrixClass matrix1 = FromApplicationFolderFile(FILE_NAME1, "\\Data\\");
	MatrixClass matrix2 = FromApplicationFolderFile(FILE_NAME2, "\\Data\\");
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
		int с[10] = { 1,0,0,0,0,0,0,0,0,1 };
		int jk[10];
		if (taskId == 0)
		{
			request = MPI_Send(&с[0], 10, MPI_INT, 1, 99, MPI_COMM_WORLD);
			cout << "Request = ";
			cout << request;
		}
		else if (taskId == 1)
		{
			MPI_Recv(&jk[0], 10, MPI_INT, 0, 99, MPI_COMM_WORLD, &status1);
			ofstream File(R"(C:\Users\Public\Pictures\TestReceive)");
			if (File.is_open())
			{
				for (int element : jk)
				{
					File << element << endl;
				}
				File.close();
			}
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

