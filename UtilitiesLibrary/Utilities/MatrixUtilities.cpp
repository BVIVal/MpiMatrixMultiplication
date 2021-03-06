#include "MatrixUtilities.h"
#include "VectorUtilities.h"

#pragma region Constructor

//ToDo: _i = _matrix.size(); _j = _matrix[0].size();
MatrixClass::MatrixClass(int i, int j, vector<vector<double>> matrix) : _i(i), _j(j), _matrix(matrix)
{
}

MatrixClass::MatrixClass(int i, int j) : _i(i), _j(j), _matrix(vector<vector<double>>(i, vector<double>(j)))
{
}

MatrixClass::MatrixClass()
{
	this->_i = -1;
	this->_j = -1;
	this->_matrix = {};
}

#pragma endregion

#pragma region Get/Set

double MatrixClass::Get(int i, int j)
{
	return _matrix[i][j];
}

vector<double> MatrixClass::Get(int i)
{
	return _matrix[i];
}

void MatrixClass::Set(int i, int j, double value)
{
	_matrix[i][j] = value;
}

void MatrixClass::Set(int i, vector<double> value)
{
	_matrix[i] = value;
}

#pragma endregion


void MatrixClass::PushRow(vector<double> value)
{
	_matrix.push_back(value);
}

int MatrixClass::GetDemensionI()
{
	return _i;
}
int MatrixClass::GetDemensionJ()
{
	return _j;
}

vector<vector<double>> MatrixClass::GetMatrixAll()
{
	return _matrix;
}

MatrixClass MatrixClass::CreateEmptyMatrixClass()
{
	this->_i = -1;
	this->_j = -1;
	this->_matrix = {};
	return *this;
}

bool MatrixClass::IsMatrixClassEmtpy(MatrixClass matrixClass)
{
	const vector<vector<double>> emtpyVector = {};
	if ((matrixClass.GetDemensionI() <= 0 && matrixClass.GetDemensionJ() <= 0)
		|| matrixClass.GetMatrixAll() == emtpyVector) return true;
	return false;
}

MatrixClass MatrixClass::Transpose(MatrixClass data)
{
	vector<vector<double>> result(data.GetDemensionJ(), vector<double>(data.GetDemensionI()));

	for (int i = 0; i < data.GetDemensionI(); i++)
		for (int j = 0; j < data.GetDemensionJ(); j++)
		{
			result[j][i] = data.Get(i, j);
		}

	return MatrixClass(data.GetDemensionJ(), data.GetDemensionI(), result);
}

MatrixClass MatrixClass::FromMpiGatherVectorToMatrixClass(vector<double> gatherVector, vector<int> capacityDemensionI, int demensionJ)
{
	auto demensionI = Sum(capacityDemensionI);
	auto numIterations = gatherVector.size();
	auto maxDemensionI = Max(capacityDemensionI);
	
	auto resultVector = vector<vector<double>>(demensionI, vector<double>(demensionJ));

	for (int i = 0; i < demensionI; i++)
	{

		resultVector[i] = GetVectorElements(gatherVector, (maxDemensionI * demensionJ * i) % (numIterations - demensionJ), demensionJ);

	}

	
	return MatrixClass(resultVector.size(), resultVector[0].size(), resultVector);
}

