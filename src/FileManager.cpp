#include "FileManager.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

bool FileManager::fileExists(const std::string& path)
{
    return fs::exists(path);
}

bool FileManager::copyFile(const std::string& source, const std::string& destination)
{
    try
    {
        fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
        return true;
    }
    catch (...)
    {
        return false;
    }
}