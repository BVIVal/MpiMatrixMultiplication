#include <stdio.h>
#include <intrin.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include "MatrixUtilities.h"
#ifndef _INPUTUTILITIES_H_
#define _INPUTUTILITIES_H_

int GetIntValue(ifstream& stream);
string DataFilePath(string dataFileName);
ifstream FileOpenDat(string dataFilePath);
vector<vector<double>> GetMatrixOfDoubles(ifstream& binaryFile, int& i, int& j, int varType);
MatrixClass FromFile(string fileName);

#endif