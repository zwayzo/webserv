#ifndef REQUEST_HPP
#define REQUEST_HPP

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
#include<string>
#include <ctime>

class request
{
    public:
        int fd;
        std::string file;
        int fileIndex;
        int index;
        int post;
        int first;
        long long contentLenght;
        char buff[1024];
        std::ofstream fileD;
        int method;
        long long track;

        int port;
        int post_indice;
        int get;
        int del;

        std::string upload;

    public:
        request();
        request (const request &copy);
        request& operator=(const request &copy);
};

#endif
