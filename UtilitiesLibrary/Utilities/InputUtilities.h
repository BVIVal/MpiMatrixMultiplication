#ifndef _INPUTUTILITIES_H_
#define _INPUTUTILITIES_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "MatrixUtilities.h"
#include "FileUtilities.h"


using namespace std;

int GetIntValue(ifstream& stream);
vector<vector<double>> GetMatrixOfDoubles(ifstream& binaryFile, int& i, int& j, int varType);
MatrixClass FromApplicationFolderFile(const string& fileName, const string& subFolder);
MatrixClass FromFile(const string& path, const string& fileName, const string& subFolder);
vector<int> GetVectorById(int taskId, int vectorSize, int commSize);

#endif