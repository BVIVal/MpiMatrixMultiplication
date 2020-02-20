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
