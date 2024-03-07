#include "headers/header.hpp"

int main()
{
    conf *config = new conf;
    try{
        config = fileConfiguration(config, "configFile.conf");
        multuplixing(config);

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
        else if (std::strcmp(x, "params") == 0)
            std::cout << "ERROR...INKOWN PARAMS...!\n";
        else if (std::strcmp(x, "max") == 0)
            std::cout << "ERROR...MAX SYNTAX...!\n";
        else if (std::strcmp(x, "listen") == 0)
            std::cout << "ERROR...LISTEN SYNTAX...!\n";
        else if (std::strcmp(x, "location") == 0)
            std::cout << "ERROR...LOCATION...!\n";
        else if (std::strcmp(x, "comma") == 0)
            std::cout << "ERROR...COMMA\n";
        else if (std::strcmp(x, "auto") == 0)
            std::cout << "ERROR...AUTO\n";
        else if (std::strcmp(x, "numbers") == 0)
            std::cout << "ERROR...DEPLUCATE\n";
        else if (std::strcmp(x, "numberss") == 0)
            std::cout << "ERROR...DEPLUCATE(location)\n";    
        std::cout << x << '\n' << "errno set to " <<  strerror(errno) << '\n';
    }
    catch (...)
    {
        std::cout << "unhandled exception...!\n";
    }
    for (int i = 0;i < config->serversNumber; i++)
        delete config->ser[i].info;
    delete (config);
}