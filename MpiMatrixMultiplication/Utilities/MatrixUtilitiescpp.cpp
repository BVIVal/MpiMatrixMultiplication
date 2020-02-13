#include "MatrixUtilities.h"

#pragma region Constructor

MatrixClass::MatrixClass(int i, int j, vector<vector<double>> matrix) : _i(i), _j(j), _matrix(matrix)
{
}

MatrixClass::MatrixClass()
{
}

#pragma endregion

#pragma region Get/Set

double MatrixClass::Get(int i, int j) {
	return _matrix[i][j];
}

vector<double> MatrixClass::Get(int i) {
	return _matrix[i];
}

void MatrixClass::Set(int i, int j, double value) {
	_matrix[i][j] = value;
}

void MatrixClass::Set(int i, vector<double> value) {
	_matrix[i] = value;
}

#pragma endregion


void MatrixClass::PushRow(vector<double> value) {
	_matrix.push_back(value);
}

int MatrixClass::GetI() {
	return _i;
}
int MatrixClass::GetJ() {
	return _j;
}

MatrixClass MatrixClass::CreateEmptyMatrixClass()
{
	this->_i = -1;
	this->_j = -1;
	this->_matrix = {};
	return *this;
}

