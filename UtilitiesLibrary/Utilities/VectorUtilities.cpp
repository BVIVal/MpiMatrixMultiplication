#include "VectorUtilities.h"

vector<double> From2DTo1D(vector<vector<double>> vector2D)
{
	vector<double> vector1D;
	for (auto row : vector2D)
	{
		copy(row.begin(), row.end(), back_inserter(vector1D));
	}
	return vector1D;
}
