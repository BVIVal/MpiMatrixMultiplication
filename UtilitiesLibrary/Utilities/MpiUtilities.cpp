#include "MpiUtilities.h"

/**
 * @brief Finalize mpi-routine and exit from the program finally;
 * @param msg - string, that describes the reason for exit;
 */
void MpiErrorExit(string msg)
{
	cout << msg << endl;
	MPI_Finalize();
	exit(1);
}

/**
 * \brief Creating new MPI_Datatype of vector of doubles
 * \param numberOfBlocks - one block for 'blockLength' numer of values
 * \param blockLength - number of values in sending
 * \param stride - space among blocks
 * \return - commited MPI_Datatype
 */
MPI_Datatype CreateMpiVectorTypeOfDoubles(int numberOfBlocks, int blockLength, int stride)
{
	MPI_Datatype vectorOfDoubles;
	MPI_Type_vector(numberOfBlocks, blockLength, stride, MPI_DOUBLE, &vectorOfDoubles);
	MPI_Type_commit(&vectorOfDoubles);
	return vectorOfDoubles;
}

double StartTimer()
{
    return MPI_Wtime();
}

double StopTimer(double startPoint)
{
    return MPI_Wtime() - startPoint;
}
