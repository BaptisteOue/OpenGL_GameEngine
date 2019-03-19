#pragma once

#include <string>

class FileUtils
{
private:
public:
    FileUtils() = delete;
    ~FileUtils() = delete;

    static std::string LoadFile(const std::string filePath);
};