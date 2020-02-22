#ifndef COMPUTEUTILITIES_H
#define COMPUTEUTILITIES_H
#include <vector>
#include "MatrixUtilities.h"
#include "InputUtilities.h"

using namespace std;

MatrixClass* MultiplyMatrix(MatrixClass A, MatrixClass B, const int commSize = 1, const int commRank = 0);
bool AreVectorsEqual(vector<vector<double>> matrixA, vector<vector<double>> matrixB, double measurementError);
vector<vector<double>> ComputeDelta(vector<vector<double>> matrixA, vector<vector<double>> matrixB);
int ComputeMatrixCapacityByRank(int rowsNumber, int commSize, int commRank);

#endif // COMPUTEUTILITIES_H
