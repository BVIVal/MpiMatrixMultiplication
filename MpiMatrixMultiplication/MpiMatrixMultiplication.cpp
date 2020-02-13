#include <mpi.h>
#include "Utilities/MatrixUtilities.h"
#include "Utilities/InputUtilities.h"

#define BUFFER_SIZE 1024
#define FILE_NAME1 "EntryMatrixDouble1.dat"
#define FILE_NAME2 "EntryMatrixDouble2.dat"

using namespace std;

MPI_Status status;

#define N 10
double a[N][N], b[N][N], c[N][N];

int GridSize; // Size of virtual processor grid 
MatrixClass Transpose(MatrixClass& data);

int main(int argc, char** argv) {

	int numTasks, taskId, numworkers, source, dest, rows, offset, i, j, k;
	SYSTEMTIME start, stop;

	getchar();
	MatrixClass matrix1 = FromFile(FILE_NAME1);
	MatrixClass matrix2 = FromFile(FILE_NAME2);
	//ToDo: optimize matrix2 & transposedMatrix
	MatrixClass transposedMatrix = Transpose(matrix2);


	getchar();

	// Initialize the MPI environment.
	MPI_Init(&argc, &argv);
	// Get the number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &numTasks);
	// Get the rank of the process
	MPI_Comm_rank(MPI_COMM_WORLD, &taskId);

	cout << "Hello World Process #" << taskId << '\n';

	MPI_Status status1;
	// for delete
	try
	{
		int request;
		int с[10] = { 0,0,0,0,0,0,0,0,0,0 };
		int jk[10];
		if (taskId == 0)
		{
			request = MPI_Send(&с[0], 5, MPI_INT, 0, 99, MPI_COMM_WORLD);
			cout << "Request = ";
			cout << request;
		}
		else if (taskId == 1)
		{
			MPI_Recv(&jk[0], 10, MPI_INT, 0, 99, MPI_COMM_WORLD, &status1);
		}
	}
	catch (const char* msg)
	{
		cout << msg;
	}

	//

	MPI_Finalize();
	return 0;


	numworkers = numTasks - 1;

	vector<double> receivedRow;

	// If Master
	// Отправить каждому работнику транспонированную матрицу и отправить
	// пакет "лент" из первой матрицы.
	//

	
	if (taskId == 0) {
		MPI_Send(&matrix1.Get(0), 500, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&transposedMatrix.Get(0), 500, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
	}

	//MPI_Status status1;
	MPI_Status status2;
	// If Worker
	if (taskId > 0)
	{
		MPI_Recv(&receivedRow[0], 500, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status1);
		MPI_Recv(&receivedRow[1], 500, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status2);
	}

	getchar();



	/*---------------------------- worker----------------------------*/
	if (taskId > 0) {
		source = 0;
		MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&a, rows * N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&b, N * N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);

		/* Matrix multiplication */
		for (k = 0; k < N; k++)
			for (i = 0; i < rows; i++) {
				c[i][k] = 0.0;
				for (j = 0; j < N; j++)
					c[i][k] = c[i][k] + a[i][j] * b[j][k];
			}


		MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&c, rows * N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
	}


	// Finalize the MPI environment. No more MPI calls can be made after this
	MPI_Finalize();

	getchar();

}

MatrixClass Transpose(MatrixClass& data) {
	vector<vector<double>> result(data.GetI(), vector<double>(data.GetJ()));

	for (int a = 0; a < data.GetI(); a++)
		for (int b = 0; b < data.GetJ(); b++) {
			result[a][b] = data.Get(b, a);
		}

	return MatrixClass(data.GetJ(), data.GetI(), result);

}


//#include "mpi.h"
//#include "stdio.h"
//#include <iostream>
//using namespace std;
//int main(int argc, char** argv)
//{
//	int rank, size;
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	cout << " Number of process = " << size << "   My rank = " << rank << endl;
//	MPI_Finalize();
//	getchar();
//	return 0;
//
//}