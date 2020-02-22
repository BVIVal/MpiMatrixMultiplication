#ifndef _MATRIXUTILITIES_H_
#define _MATRIXUTILITIES_H_
#include <vector>
using namespace std;


#pragma once


class MatrixClass
{
private:

#pragma region Fields

	int _i;
	int _j;
	vector<vector<double>> _matrix;

#pragma endregion

public:

#pragma region Constructors

	MatrixClass(int i, int j, vector<vector<double>> matrix);

	MatrixClass(int i, int j);

	MatrixClass();

#pragma endregion

#pragma region Get/Set

	double Get(int i, int j);

	vector<double> Get(int i);

	void Set(int i, int j, double value);

	void Set(int i, vector<double> value);

#pragma endregion

	void PushRow(vector<double> value);

	int GetDemensionI();

	int GetDemensionJ();

	vector<vector<double>> GetMatrixAll();

	bool IsMatrixClassEmtpy(MatrixClass matrixClass);

	MatrixClass CreateEmptyMatrixClass();

	static MatrixClass Transpose(MatrixClass data);

};

#endif
