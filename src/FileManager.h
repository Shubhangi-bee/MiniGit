#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager
{
public:
    bool fileExists(const std::string& path);
    bool copyFile(const std::string& source, const std::string& destination);
};

#endif