#pragma once

#include <string>

class FileUtils
{
private:
public:
    FileUtils() = delete;
    ~FileUtils() = delete;

    static std::string LoadFile(std::string filePath);
};