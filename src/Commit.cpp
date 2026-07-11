#include "Commit.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

bool Commit::createCommit(const std::string& message)
{
    std::string commitFolder = ".minigit/commits";
    std::string stagingFolder = ".minigit/staging";
    std::string objectFolder = ".minigit/objects";

    int commitID = 1;

    while (fs::exists(commitFolder + "/" + std::to_string(commitID) + ".commit"))
    {
        commitID++;
    }

    std::ofstream commitFile(commitFolder + "/" + std::to_string(commitID) + ".commit");

    if (!commitFile)
    {
        std::cout << "Failed to create commit." << std::endl;
        return false;
    }

    commitFile << "Commit ID: " << commitID << "\n";
    commitFile << "Message: " << message << "\n";
    commitFile << "Files:\n";
    std::ifstream indexFile(".minigit/index");

std::string line;

while (getline(indexFile, line))
{
    std::stringstream ss(line);

std::string filename;
std::string hash;

ss >> filename >> hash;

std::string objectPath = ".minigit/objects/" + hash;

uintmax_t fileSize = 0;

if (fs::exists(objectPath))
{
    fileSize = fs::file_size(objectPath);
}

commitFile << filename << " "
           << hash << " "
           << fileSize << "\n";
}

indexFile.close();

    commitFile.close();

    std::ofstream head(".minigit/HEAD");
    head << commitID;
    head.close();
    // Clear staging folder
for (const auto& entry : fs::directory_iterator(stagingFolder))
{
    fs::remove(entry.path());
}

// Clear index
std::ofstream clearIndex(".minigit/index");
clearIndex.close();

    std::cout << "Commit " << commitID << " created successfully!" << std::endl;

    return true;
}