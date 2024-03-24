#ifndef MULTUPLIXING_HPP
#define MULTUPLIXING_HPP

#include "../headers/header.hpp"
#include "../request/request.hpp"

class client{
    public:
        request req;
    public:
        int     creatFile(int fd, char *buf);
        void    getMethodes(std::string buf);
        // deujks


};

// std::vector <client> mycl;




class request;
class conf;
void multuplixing (conf *conf);
void getMethodes(std::string buf, client *cl); //check if the method is post to work with
void handleCtrlZ(int signum);
int maxFd(conf* conf);

#endif