#include <fstream>
#include <sstream>
#include <iostream>
#include "FileUtils.h"

#pragma region Public API

std::string FileUtils::LoadFile(std::string filePath)
{
	std::ifstream file;
	file.open(filePath);

	if (!file.is_open())
	{
		std::cout << "Can't open " << filePath << std::endl;
		return nullptr;
	}
	
	std::stringstream fileContent;
	fileContent << file.rdbuf();

	return fileContent.str();
}

#pragma endregion