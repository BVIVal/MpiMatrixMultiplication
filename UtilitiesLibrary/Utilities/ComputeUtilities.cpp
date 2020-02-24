#include "ComputeUtilities.h"



MatrixClass* MatricesProduct(MatrixClass A, MatrixClass B, int commSize, int commRank)
{
	if (A.GetDemensionJ() != B.GetDemensionI()) return new MatrixClass;

	//auto indexes = GetVectorById(commRank, )
	auto result = MultiplyMatrix(A, B, 1, 0);
	//for (int i = 0; i < A.GetDemensionI(); i++)
	//	for (int k = 0; k < A.GetDemensionJ(); k++)
	//		for (int j = 0; j < B.GetDemensionJ(); j++)
	//			C->Set(i, j, A.Get(i, k) + B.Get(k, j));
	///*for (i = 0; i < SIZE; i++) {
	//	for (j = 0; j < SIZE; j++) {
	//		for (k = 0; k < SIZE; k++)
	//			c[i][j] = c[i][j] + a[i][k] * b[j][k];
	//	}
	//}*/
	return result;
}

MatrixClass* MultiplyMatrix(MatrixClass A, MatrixClass B, const int commSize, const int commRank)
{
	if (A.GetDemensionJ() != B.GetDemensionI()) throw runtime_error("Impossible to multiply matrices");
	auto transposedB = MatrixClass::Transpose(B);
	auto C = new MatrixClass(ComputeMatrixCapacityByRank(A.GetDemensionI(), commSize, commRank), B.GetDemensionJ());
	for (int i = commRank, z = 0; i < A.GetDemensionI(); i += commSize, z += 1)
		for (int j = 0; j < transposedB.GetDemensionI(); j++)
			for (int k = 0; k < A.GetDemensionJ(); k++)
				C->Set(i - (commRank + z * (commSize - 1)), j, 
					C->Get(i - (commRank + z * (commSize - 1)), j) + A.Get(i, k) * transposedB.Get(j, k));
	return C;
}

//ToDo: to do it over generics
bool AreVectorsEqual(vector<vector<double>> matrixA, vector<vector<double>> matrixB, double measurementError)
{
	if ((matrixA.size() != matrixB.size()) || (matrixA[0].size() != matrixB[0].size())) return false;
	for (size_t i = 0; i < matrixA.size(); i++)
	{
		for (size_t j = 0; j < matrixA[0].size(); j++)
		{
			if (fabs((matrixA[i][j] - matrixB[i][j])) > measurementError) return false;
		}
	}
	return true;
}

//ToDo: to do it over generics
bool AreVectorsEqual(vector<double> matrixA, vector<double> matrixB, double measurementError)
{
	if (matrixA.size() != matrixB.size()) return false;
	for (size_t i = 0; i < matrixA.size(); i++)
	{
		if(fabs((matrixA[i] - matrixB[i])) > measurementError) return false;
	}
	return true;
}

vector<vector<double>> ComputeDelta(vector<vector<double>> matrixA, vector<vector<double>> matrixB)
{
	auto deltaResult = vector<vector<double>>(matrixA.size(), vector<double>(matrixA[0].size()));

	for (size_t i = 0; i < matrixA.size(); i++)
	{
		for (size_t j = 0; j < matrixA[0].size(); j++)
		{
			deltaResult[i][j] = fabs((matrixA[i][j] - matrixB[i][j]));
		}
	}
	return deltaResult;
}

int ComputeMatrixCapacityByRank(int rowsNumber, int commSize, int commRank)
{
	return (((rowsNumber - commRank) - 1) / commSize) + 1;
}

int ComputeMaxMatrixCapacity(int rowsNumber, int commSize)
{
	int maxCapacity = -1;
	for(int i = 0; i < commSize; i++)
	{
		auto variable = ComputeMatrixCapacityByRank(rowsNumber, commSize, i);
		if(maxCapacity < variable) maxCapacity = variable;
	}
	return maxCapacity;
}

