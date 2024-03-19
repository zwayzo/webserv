#ifndef MULTUPLIXING_HPP
#define MULTUPLIXING_HPP

#include "parseRequest.hpp"
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
#include <algorithm>
#include <random>
#include <ctime>


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
        long long contentLenght;
        std::ofstream fileD;
        int method;
};

// std::vector <client> mycl;




class conf;
void multuplixing (conf *conf);
int randomNum(); //get rendom number to add it in file[number].extention (post method)
void getMethodes(std::string buf, client *cl); //check if the method is post to work with
int creatFile(int fd, char *buf, client *cl); //creat the file (file+'random number' +.'extention)
void getRequestLenght(char *buf, client *cl); //get the request lenght of post so to know how many time i nead to read(post)
std::string getExtention(char *buf); //get the extention of what i receive (post)
int getBody(char *buf);//get the only the body to put it in file to get the (image video or whatever the client want to post) (post method)
void handleCtrlZ(int signum);
int maxFd(conf* conf);
void clearSets(client *mycl, int i, long long *s, int *index, fd_set *master_re, fd_set *master_wr); //clear the sets and initialze some variables(select)
int validSocket(int j, conf *conf); //check if the j is a socket (need to be socket if want to work with methodes)
void addSocket(conf *conf);
void getSocket(conf* conf);

#endif