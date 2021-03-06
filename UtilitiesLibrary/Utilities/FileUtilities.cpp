#include "FileUtilities.h"

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
	ios_base::openmode ofstreamMode = ios::trunc;
	auto fullPath = ToRawStringPath(path) + ToRawStringPath("\\" + name);

	if (!reCreateIfAlreadyExists)
	{
		if (FileExists(fullPath)) ofstreamMode = ios::app;
		else ofstreamMode = ios::trunc;
	}
	
	auto fileStream = new ofstream(fullPath, ofstreamMode);

	if (!IsFileOpen(fileStream)) throw runtime_error("File not created!\n Name: " + name + "\n Path: " + path);
	return fileStream;
}

bool IsFileOpen(ofstream* file)
{
	if (file->is_open()) return true;
	return false;
}

//ToDo: to do over generic type
bool TryWriteToFile(ofstream* file, const vector<int>& values)
{
	if (file->is_open())
	{
		for (auto& value : values)
		{
			try
			{
				*file << value << endl;
			}
			catch (...)
			{
				return false;
			}

		}
		return true;
	}

	return false;
}

//ToDo: to do over generic type
bool TryWriteToFile(ofstream* file, const vector<double>& values)
{
	if (file->is_open())
	{
		try
		{
			
			for (auto& value : values)
			{
				*file << value << " ";
			}
			*file << endl;
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	return false;
}

//ToDo: to do over generic type
bool TryWriteToFile(ofstream* file, const vector<vector<double>>& values)
{
	if (file->is_open())
	{
		try
		{
			for (auto row : values)
			{
				for (auto& value : row)
				{
					*file << value << " ";
				}
				*file << endl;
			}
		}
		catch (...)
		{
			return false;
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
	if (subFolder != "") filePath += "\\" + subFolder;
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
