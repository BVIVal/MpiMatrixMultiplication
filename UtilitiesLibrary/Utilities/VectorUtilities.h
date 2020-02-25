#ifndef VECTORUTILITIES_H
#define VECTORUTILITIES_H
#include <vector>

using namespace std;

vector<double> From2DTo1D(vector<vector<double>> vector2D);
int Sum(vector<int> inVector);
int Max(vector<int> inVector);
vector<double> GetVectorElements(vector<double> inVector, int fromIndex, int numOfElements);
#endif // VECTORUTILITIES_H
