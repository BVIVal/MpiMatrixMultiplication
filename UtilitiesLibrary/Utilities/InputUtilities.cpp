#include "InputUtilities.h"


//ToDo: normal description
int GetIntValue(ifstream& stream) {
	int value;
	stream.read(reinterpret_cast<char*>(&value), 4);
	if (value < 0 || value >= 2147483647) throw invalid_argument("Received negative i-value");
	return value;
}



//ToDo: How to do generic?!
vector<vector<double>> GetMatrixOfDoubles(ifstream& binaryFile, int& i, int& j, int varType = sizeof(double)) {
	vector<vector<double>> matrix2D;
	vector<double> matrix1D;
	int counter = 0;

	double numBuffer = -1;
	while (true) {
		if (counter % i == 0 && counter != 0) {
			matrix2D.push_back(matrix1D);
			matrix1D.clear();
		}
		if (binaryFile.peek() == EOF) break;
		binaryFile.read(reinterpret_cast<char*>(&numBuffer), varType);
		matrix1D.push_back(numBuffer);
		counter++;
	}
	if (counter == i * j)
		return matrix2D;
	printf("Not enough elements in file");
	return {};
}

//ToDo: Do I have to replace this function into 'FileUtilities' and make a link to 'MatrixClass'?
MatrixClass FromApplicationFolderFile(const string& fileName, const string& subFolder = "")
{
	ifstream binaryFile;
	try
	{
		binaryFile = GetReadStream(GetFileApplicationPath(fileName, subFolder));
	}
	catch(const runtime_error& e)
	{
		cout << e.what();
		return MatrixClass();
	}
	catch(...)
	{
		throw runtime_error("Unknown error in FromApplicationFolderFile");
	}
	
	if (!binaryFile.is_open()) return MatrixClass().CreateEmptyMatrixClass();

	int i = GetIntValue(binaryFile);
	int j = GetIntValue(binaryFile);

	return MatrixClass(i, j, GetMatrixOfDoubles(binaryFile, i, j));
}

//ToDo: Do I have to replace this function into 'FileUtilities' and make a link to 'MatrixClass'?
MatrixClass FromFile(const string& path, const string& fileName, const string& subFolder = "")
{
	ifstream binaryFile;
	try
	{
		binaryFile = GetReadStream(GetFilePath(path, fileName, subFolder));
	}
	catch (const runtime_error& e)
	{
		cout << e.what();
		return MatrixClass();
	}
	catch (...)
	{
		throw runtime_error("Unknown error in FromFile");
	}
	
	if (!binaryFile.is_open()) return MatrixClass().CreateEmptyMatrixClass();

	int i = GetIntValue(binaryFile);
	int j = GetIntValue(binaryFile);

	return MatrixClass(i, j, GetMatrixOfDoubles(binaryFile, i, j));
}

/**
 * @brief
Create new vector<uint32_t> of indexes, using process-rank, max value of vector, and common number of using processes;
 *
@param taskId - process rank;
@param vectorSize - max value of vector;
@param commSize - the number of involved processes;
 *
 * @return
 * New vector<uint32_t>;
 */
vector<int> GetVectorById(int taskId, int vectorSize, int commSize)
{
	vector<int> newVector;
	for (int i = taskId; i < vectorSize; i = i + commSize) newVector.push_back(i);
	return newVector;
}


