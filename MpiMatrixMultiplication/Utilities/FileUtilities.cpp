#include "FileUtilities.h"



// Function: FileExists
/**
    Check if a file exists
@param[in] filename - the name of the file to check

@return    true if the file exists, else false

*/
bool FileExists(const string& filename)
{
    struct stat buf{};
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

bool IsFileClosedSuccessfully(ofstream* file)
{
    file->close();
    if (!file) return false;
    return true;
}

//ToDo: Is it wrong implementation? Do I need a destructor? Or better use std::move()?
ofstream* CreateNewFile(const string& path, const string& name, bool reCreateIfAlreadyExists)
{
	auto fullPath = ToRawStringPath(path) + ToRawStringPath("\\" + name);

	if (!reCreateIfAlreadyExists)
	{
		if (FileExists(fullPath)) throw "File with Name: " + name + " already exists\n by Path: " + path;
	}
	auto fileStream = new ofstream(fullPath);

	if (!IsFileOpen(fileStream)) throw "File not created!\n Name: " + name + "\n Path: " + path;
	return fileStream;
}

bool IsFileOpen(ofstream* file)
{
	if (file->is_open()) return true;
	return false;
}

bool TryWriteToFile(ofstream* file, const vector<uint32_t>& values)
{

	if (file->is_open())
	{
		for (auto& value : values)
		{
			try
			{
				*file << value << endl;
			}
			catch (exception e)
			{
				return false;
			}

		}
		return true;
	}

	return false;
}

/**
 * Creating full-path to the object using project-path.
 * @warning Requires "windows.h"-library or you'll get a problem with "winnt.h"
 *
 * @param fileName (string) - name of the file or relative-path to the object.
 * @return filePath (string) - path in project folder to the object.
 */
string GetFileApplicationPath(const string& fileName, string subFolder = "")
{
	char szPath[0x100];
	GetModuleFileNameA(NULL, szPath, sizeof(szPath));
	string filePath = szPath;
	filePath = filePath.substr(0, filePath.find_last_of("\\"));
	if(subFolder != "") filePath += "\\" + subFolder;
	return filePath += "\\" + fileName;
}

string GetFilePath(const string& path, const string& fileName, const string subFolder = "")
{
	string filePath = ToRawStringPath(path);
	if (subFolder == "") return filePath += "\\" + fileName;
	filePath += "\\" + subFolder;
	return filePath += "\\" + fileName;
}

ifstream GetReadStream(const string& filePath)
{
	ifstream binaryFile;
	binaryFile.open(filePath, fstream::binary);
	if (!binaryFile.is_open()) {
		//throw exception("GetReadStream: File does not exist");
		throw runtime_error("GetReadStream: File does not exist");
	}
	return binaryFile;
}
