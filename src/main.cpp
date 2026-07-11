#include "Repository.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    Repository repo;

    if (argc < 2)
    {
        std::cout << "Usage: ./minigit <command>" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "init")
    {
        repo.init();
    }
    else if (command == "add")
    {
        if (argc < 3)
        {
            std::cout << "Usage: ./minigit add <filename>" << std::endl;
            return 1;
        }

        repo.add(argv[2]);
    }
    else if (command == "commit")
    {
        if (argc < 4 || std::string(argv[2]) != "-m")
        {
            std::cout << "Usage: ./minigit commit -m \"message\"" << std::endl;
            return 1;
        }

        repo.commit(argv[3]);
    }
    else if (command == "log")
    {
        repo.log();
    }
    else if (command == "status")
{
    repo.status();
}
else if (command == "checkout")
{
    if (argc < 3)
    {
        std::cout << "Usage: ./minigit checkout <commit_id>" << std::endl;
        return 1;
    }

    repo.checkout(std::stoi(argv[2]));
}
    else
    {
        std::cout << "Unknown command!" << std::endl;
    }

    return 0;
}