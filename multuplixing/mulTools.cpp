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

void attachClientServer(int i, conf *conf, client *tmp)
{
    for (int j = 0;j < conf->serversNumber; j++)
    {
        if (i == conf->ser[j].sock)
        {
            tmp->port = conf->ser[j].listen;
            tmp->post = conf->ser[j].post;
            tmp->get = conf->ser[j].get;
            tmp->del = conf->ser[j].deletee;
            tmp->upload = conf->ser[j].uploads;
        }
    }
}
