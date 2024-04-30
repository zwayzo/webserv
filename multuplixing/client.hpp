#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../headers/header.hpp"
#include "../request/request.hpp"
#include "../request/HttpRequest.hpp"

class client{
    public:
        server clientServer;
        request req;

    public:
        int     creatFile(int fd, char *buf);
        void    getMethodes(std::string buf);
        // deujks
};
// std::vector <client> mycl;

class request;
class conf;
void getMethodes(std::string buf, client *cl); //check if the method is post to work with
void handleCtrlZ(int signum);
int maxFd(conf* conf);
client attachClientServer(int i, conf *conf, client tmp, int in, int newFd);

#endif