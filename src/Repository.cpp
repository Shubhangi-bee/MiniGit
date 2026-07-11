#include "Repository.h"
#include "Commit.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "FileManager.h"
#include "Hash.h"
#include <vector>
#include <sstream>
namespace fs = std::filesystem;

Repository::Repository()
{
}

bool Repository::init()
{
    // Check if repository already exists
    if (fs::exists(repoFolder))
    {
        std::cout << "MiniGit repository already exists!" << std::endl;
        return false;
    }

    try
    {
        // Create main repository folder
        fs::create_directory(repoFolder);

        // Create subfolders
        fs::create_directory(repoFolder + "/commits");
        fs::create_directory(repoFolder + "/objects");
        fs::create_directory(repoFolder + "/staging");

        // Create HEAD file
        std::ofstream head(repoFolder + "/HEAD");

        if (!head)
        {
            std::cout << "Failed to create HEAD file." << std::endl;
            return false;
        }

        head << "NULL";
        head.close();
        
        std::ofstream index(repoFolder + "/index");
        index.close();

        std::cout << "MiniGit repository initialized successfully!" << std::endl;

        return true;
    }
    catch (const std::exception& e)
    {
        std::cout << "Initialization failed: " << e.what() << std::endl;
        return false;
    }
}
bool Repository::add(const std::string& filename)
{
    if (!fileManager.fileExists(filename))
    {
        std::cout << "File not found!" << std::endl;
        return false;
    }

    std::string hash = hashManager.generateHash(filename);

    std::string objectPath = repoFolder + "/objects/" + hash;

    if (!fileManager.fileExists(objectPath))
    {
        fileManager.copyFile(filename, objectPath);
    }

    std::string stagingPath = repoFolder + "/staging/" + filename;

    if (!fileManager.copyFile(filename, stagingPath))
    {
        std::cout << "Failed to stage file!" << std::endl;
        return false;
    }
    std::ifstream inFile(repoFolder + "/index");

std::vector<std::string> entries;
std::string line;
bool found = false;

while (getline(inFile, line))
{
    if (line.substr(0, filename.size()) == filename)
    {
        entries.push_back(filename + " " + hash);
        found = true;
    }
    else
    {
        entries.push_back(line);
    }
}

inFile.close();

if (!found)
{
    entries.push_back(filename + " " + hash);
}

std::ofstream outFile(repoFolder + "/index");

for (const auto& entry : entries)
{
    outFile << entry << std::endl;
}

outFile.close();
    std::cout << "File staged successfully!" << std::endl;
    std::cout << "Hash : " << hash << std::endl;

    return true;
}
bool Repository::commit(const std::string& message)
{
    return commitManager.createCommit(message);
}
bool Repository::log()
{
    namespace fs = std::filesystem;

    std::string commitFolder = ".minigit/commits";

    if (!fs::exists(commitFolder))
    {
        std::cout << "No commits found!" << std::endl;
        return false;
    }

    for (const auto& entry : fs::directory_iterator(commitFolder))
    {
        std::ifstream file(entry.path());

        std::string line;

        while (getline(file, line))
        {
            std::cout << line << std::endl;
        }

        std::cout << "----------------------" << std::endl;
    }

    return true;
}
bool Repository::status()
{
    namespace fs = std::filesystem;

    std::cout << "========== MiniGit Status ==========\n";

    // HEAD
    std::ifstream headFile(".minigit/HEAD");
    std::string head;

    if (headFile)
    {
        getline(headFile, head);
        std::cout << "Current HEAD : " << head << std::endl;
    }

    // Number of commits
    int commitCount = 0;
    for (const auto& entry : fs::directory_iterator(".minigit/commits"))
    {
        commitCount++;
    }

    std::cout << "Total Commits : " << commitCount << std::endl;

    // Staged files
    std::cout << "\nStaged Files:\n";

    bool empty = true;

    for (const auto& entry : fs::directory_iterator(".minigit/staging"))
    {
        std::cout << "- " << entry.path().filename().string() << std::endl;
        empty = false;
    }

    if (empty)
    {
        std::cout << "No staged files." << std::endl;
    }

    std::cout << "\nModified Files:\n";

// Read current HEAD
std::ifstream headFileRead(".minigit/HEAD");

std::string currentCommit;

getline(headFileRead, currentCommit);

headFileRead.close();

if (currentCommit == "NULL")
{
    std::cout << "No commits yet." << std::endl;
}
else
{
    std::string commitPath =
        ".minigit/commits/" + currentCommit + ".commit";

    std::ifstream commitFile(commitPath);

    if (!commitFile)
    {
        std::cout << "Failed to open latest commit." << std::endl;
        return false;
    }

    std::string line;

    // Skip first three lines
    getline(commitFile, line);
    getline(commitFile, line);
    getline(commitFile, line);

    std::cout << "Tracked Files:\n";

    while (getline(commitFile, line))
{
    std::stringstream ss(line);

    std::string filename;
    std::string hash;
    uintmax_t fileSize;

    ss >> filename >> hash >> fileSize;

    if (!fileManager.fileExists(filename))
    {
        std::cout << "Deleted : " << filename << std::endl;
        continue;
    }

    std::string currentHash = hashManager.generateHash(filename);

    if (currentHash == hash)
    {
        std::cout << "Unchanged : " << filename << std::endl;
    }
    else
    {
        std::cout << "Modified : " << filename << std::endl;
    }
}
    commitFile.close();
}

    std::cout << "====================================" << std::endl;

    return true;
}
bool Repository::checkout(int commitID)
{
    namespace fs = std::filesystem;

    std::string commitFile =
        ".minigit/commits/" + std::to_string(commitID) + ".commit";

    if (!fs::exists(commitFile))
    {
        std::cout << "Commit does not exist!" << std::endl;
        return false;
    }

    std::ofstream head(".minigit/HEAD");

    if (!head)
    {
        std::cout << "Failed to update HEAD!" << std::endl;
        return false;
    }

    head << commitID;
    head.close();
    std::ifstream commit(commitFile);

std::string line;

// Skip header
getline(commit, line);
getline(commit, line);
getline(commit, line);

std::cout << "\nFiles in Commit:\n";

while (getline(commit, line))
{
    std::stringstream ss(line);

std::string filename;
std::string hash;
uintmax_t fileSize;

ss >> filename >> hash >> fileSize;

std::string objectPath = ".minigit/objects/" + hash;

if (fileManager.copyFile(objectPath, filename))
{
    std::cout << "Restored : " << filename << std::endl;
}
else
{
    std::cout << "Failed to restore : " << filename << std::endl;
}
}

commit.close();

    std::cout << "Switched to commit " << commitID << std::endl;

    return true;
}