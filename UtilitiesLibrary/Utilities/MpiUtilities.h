#ifndef MPIUTILITIES_H
#define MPIUTILITIES_H
#include <string>
#include "mpi.h"
#include <iostream>

using namespace std;

void MpiErrorExit(string msg);
MPI_Datatype CreateMpiVectorTypeOfDoubles(int numberOfBlocks, int blockLength, int stride);

#endif // MPIUTILITIES_H
