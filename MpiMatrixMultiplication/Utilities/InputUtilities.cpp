#include "InputUtilities.h"

using namespace std;

int GetIntValue(ifstream& stream) {
	int value;
	stream.read(reinterpret_cast<char*>(&value), 4);
	if (value < 0 || value >= 2147483647) throw invalid_argument("Received negative i-value");
	return value;
}

/**
 * Creating full-path to the object using project-path.
 *
 * @param dataFileName (string) - name of the file or relative-path to the object.
 * @return filePath (string) - path in project folder to the object.
 */
string DataFilePath(string dataFileName) {
	char szPath[0x100];
	GetModuleFileNameA(NULL, szPath, sizeof(szPath));
	string filePath = szPath;
	filePath = filePath.substr(0, filePath.find_last_of("\\"));
	filePath += "\\Data\\";
	return filePath += dataFileName;
}

ifstream FileOpenDat(string dataFilePath) {
	ifstream binaryFile;
	binaryFile.open(dataFilePath, std::fstream::binary);
	if (!binaryFile.is_open()) {
		printf("File is not exists");
	}
	return binaryFile;
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

MatrixClass FromFile(string fileName) {

	ifstream binaryFile = FileOpenDat(DataFilePath(fileName));
	if (!binaryFile.is_open()) return MatrixClass().CreateEmptyMatrixClass();

	int i = GetIntValue(binaryFile);
	int j = GetIntValue(binaryFile);

	return MatrixClass(i, j, GetMatrixOfDoubles(binaryFile, i, j));
}
