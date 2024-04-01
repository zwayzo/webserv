#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../headers/header.hpp"
#include "../request/request.hpp"
#include "../request/parseRequest.hpp"

class client{
    public:
        server clientServer;
        HttpRequest httpRequest;
        request req;
        int port;
        int post;
        int get;
        int del;
        std::string upload;
        int max_size;
        server ser;
        // std::vector<location> loc;
        std::string name;
        // std::vector <lo
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