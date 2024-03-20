#include "multuplixing.hpp"

int maxFd(conf* conf)
{
    int tmp = 0;
    for (int i = 0;i < conf->serversNumber; i++)
    {
        if (conf->ser[i].sock> tmp)
            tmp = conf->ser[i].sock;
    }
    return tmp;

}

void handleCtrlZ(int signum)
{
    (void )signum;

    // Raise the SIGINT signal to terminate the program
    std::raise(SIGINT);
}