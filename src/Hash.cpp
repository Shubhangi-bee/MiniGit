#include "Hash.h"

#include <fstream>
#include <sstream>
#include <functional>

std::string Hash::generateHash(const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file)
    {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string content = buffer.str();

    std::size_t hashValue = std::hash<std::string>{}(content);

    return std::to_string(hashValue);
}