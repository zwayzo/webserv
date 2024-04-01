#include "client.hpp"

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

client attachClientServer(int i, conf *conf, client tmp, int in, int newFd)
{
    for (int j = 0;j < conf->serversNumber; j++)
    {
        if (i == conf->ser[j].sock)
            tmp.clientServer = conf->ser[j];
    }
    tmp.req.index = in;
    tmp.req.track = 0;
    tmp.req.contentLenght = 0;
    tmp.req.fd = newFd;
    return tmp;
}