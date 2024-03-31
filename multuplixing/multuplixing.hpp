#ifndef MULTUPLIXING_HPP
#define MULTUPLIXING_HPP

#include "../headers/header.hpp"
#include "../request/request.hpp"
#include "../request/parseRequest.hpp"
// #include "../response/Response.hpp"

class request;
// class HttpRequest;

class client{
    public:
        request req;
        HttpRequest httpRequest;
        // Response    httpResponse;
        int port;
        int post;
        int get;
        int del;
        std::string upload;
    public:
        int     creatFile(int fd, char *buf);
        void    getMethodes(std::string buf);
        // deujks
};

// std::vector <client> mycl;

class conf;
void multuplixing (conf *conf);
void getMethodes(std::string buf, client *cl); //check if the method is post to work with
void handleCtrlZ(int signum);
int maxFd(conf* conf);
client attachClientServer(int i, conf *conf, client tmp, int in, int newFd);

#endif