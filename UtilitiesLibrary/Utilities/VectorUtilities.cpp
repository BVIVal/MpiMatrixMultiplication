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

/**
 * \brief Summarize all elements in 'inVector'
 * \param inVector - input vector
 * \return Sum of all elements
 */
int Sum(vector<int> inVector)
{
	if (inVector.empty()) return INT_MIN;
	int result = 0;
	for (auto element : inVector)
	{
		result += element;
	}
	return result;
}

/**
 * \brief Get maximum value from vector
 * \param inVector - input vector
 * \return Max-value from vector
 */
int Max(vector<int> inVector)
{
	int result = INT_MIN;
	for (auto element : inVector)
	{
		if(result < element) result = element;
	}
	return result;
}

vector<double> GetVectorElements(vector<double> inVector, int fromIndex, int numOfElements)
{
	if (inVector.size() < fromIndex + numOfElements) return vector<double>(0);
	auto result = vector<double>(numOfElements);
	for(int i = 0; i < numOfElements; i++)
	{
		result.at(i) = inVector.at(fromIndex + i);
	}
	return result;
}