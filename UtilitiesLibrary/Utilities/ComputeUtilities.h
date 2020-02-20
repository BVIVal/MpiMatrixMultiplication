#ifndef COMPUTEUTILITIES_H
#define COMPUTEUTILITIES_H
#include <vector>
#include "MatrixUtilities.h"
#include "InputUtilities.h"

using namespace std;

MatrixClass* MultiplyMatrix(MatrixClass A, MatrixClass B, const int commSize, const int commRank);

#endif // COMPUTEUTILITIES_H
