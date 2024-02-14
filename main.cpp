#include "headers/header.hpp"

int main()
{
    conf *config = new conf;
    try{
        fileConfiguration(config, "configFile.conf");
    }
    catch (const char *x)
    {
        // std::cout << "enter\n";
        if (std::strcmp(x , "syntax") == 0)
            std::cout << "SYNTAX ERROR...!\n";
        else if (std::strcmp(x, "server syntax") == 0)
            std::cout << "SERVER SYNTAX ERROR...!\n";
        else if (std::strcmp(x, "check") == 0)
            std::cout << "ERROR...RE-CHECK THE SYNATX...!\n";
        exit(1);
    }
    catch (...)
    {
        std::cout << "unhandled exception...!\n";
    }
}