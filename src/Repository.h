#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string>
#include "FileManager.h"
#include "Commit.h"
#include "Hash.h"
class Repository
{
public:
    Repository();

    bool init();
    bool add(const std::string& filename);
    bool commit(const std::string& message);
    bool log();
    bool status();
    bool checkout(int commitID);
private:
    std::string repoFolder = ".minigit";
    FileManager fileManager;
    Commit commitManager;
    Hash hashManager;
};

#endif