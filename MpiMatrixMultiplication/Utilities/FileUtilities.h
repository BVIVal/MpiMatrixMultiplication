#ifndef _FILEUTILITIES_
#define _FILEUTILITIES_
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>
#include "StringUtilities.h"



using namespace std;

bool FileExists(const string& filename);
bool IsFileClosedSuccessfully(ofstream* file);
ofstream* CreateNewFile(const string& path, const string& name, bool reCreateIfAlreadyExists);
bool IsFileOpen(ofstream* file);
bool TryWriteToFile(ofstream* file, const vector<uint32_t>& values);
string GetFilePath(const string& path, const string& fileName, const string subFolder);
string GetFileApplicationPath(const string& fileName, string subFolder);
ifstream GetReadStream(const string& filePath);

#endif
