#include "HelperFile.hpp"

#include <cassert>
#include <iostream>
#include <fstream>

namespace Flounder
{
	bool HelperFile::FileExists(const std::string &filepath)
	{
		if (FILE *file = fopen(filepath.c_str(), "r")) 
		{
			fclose(file);
			return true;
		}

		return false;
	}

	std::string HelperFile::ReadTextFile(const std::string &filepath)
	{
		FILE *file = fopen(filepath.c_str(), "rt");

		assert(file != nullptr && "Could not find file!");

		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char *data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result = std::string(data);
		delete[] data;
		return result;
	}

	std::vector<char> HelperFile::ReadBinaryFile(const std::string &filepath)
	{
		// TODO: Move from ifsteam to normal C binary file loading.
		std::ifstream ifs = std::ifstream(filepath, std::ios::ate | std::ios::binary);

		assert(ifs.is_open() && "Could not find file!");

		size_t fileSize = static_cast<size_t>(ifs.tellg());
		std::vector<char> buffer(fileSize);

		ifs.seekg(0);
		ifs.read(buffer.data(), fileSize);
		ifs.close();

		return buffer;
	}
}
