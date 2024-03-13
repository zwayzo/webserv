#ifndef MULTUPLIXING_HPP
#define MULTUPLIXING_HPP

#include "header.hpp"
#include"configFile.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netdb.h>
#include <cstdlib>
#include <string>
#include <csignal>
#include <signal.h>
#include <unistd.h>
#include <vector>


class client{
    public:
        client(int n) : fd(n) , fileIndex(0), post(0), contentLenght(0){};
        client (){};
        client (const client &copy)
        {
            // this->fd = copy.fd;
            this->index = copy.index;
            this->post = copy.post;
            this->contentLenght = copy.contentLenght;
        }
        int fd;
        std::string file;
        int fileIndex;
        int index;
        int post;
        int contentLenght;
        std::ofstream fileD;
};

// std::vector <client> mycl;




class conf;
void multuplixing (conf *conf);

#endif