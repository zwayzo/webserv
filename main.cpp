#include "headers/header.hpp"

int main()
{
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
}