#include "headers/header.hpp"

int main(int ac, char **av)
{
    if (ac > 2) {
        std::cerr << "Error: wrong nbr of arguments!" << std::endl;
        return 1;
    }
    std::string conFile;
    if (ac == 2)
        conFile = av[1];
    else
        conFile = "configFile.conf";

    
    conf *config = new conf;
    multuplix *multup = new multuplix;
    try{
        config = fileConfiguration(config, "configFile.conf");
        multup->multuplixing(config);

    }
    catch (const char *x)
    {
        // std::cout << "enter\n";
        std::cout << x << '\n' << "errno set to " <<  strerror(errno) << '\n';
        exit(1);
    }
    catch (...)
    {
        std::cout << "unhandled exception...!\n";
    }
    for (int i = 0;i < config->serversNumber; i++)
        delete config->ser[i].info;
    delete (config);
    delete multup;

    return 0;
}