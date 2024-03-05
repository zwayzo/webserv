#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
// #include <thread>
// #include <chrono>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netdb.h>
#include <string>

class infos{
    public:
        std::map<int, std::string> autoindex;
        std::map<int, std::string> listenMap;
        std::map<int, std::string> maxBody;
        std::map<std::string, std::string> serverName;
        std::map<std::string, std::string> root;
        std::map<std::string, std::string> Index;
        std::map<std::string, std::string> errorPage;
        std::map<std::string, std::string> methodes;
        std::map<std::string, std::string> redirection;
};

class location{
    public:
    location& operator=(const location& other) {
        if (this != &other) {
            // Ensure that all members are assigned properly
            this->listen = other.listen;
            this->get = other.get;
            this->post = other.post;
            this->deletee = other.deletee;

            this->autoindex = other.autoindex;
            this->root = other.root;
            this->redirection = other.redirection;
            // ... (assign other members)

            // Make sure that strings are handled properly (e.g., using assignment or copying methodes)
            this->index = other.index;
            // ... (assign other string members)
        }
        return *this;
    }
        int listen;
        int post;
        int get;
        int deletee;
        int autoindex;

        std::string index;
        std::string theLoc;
        std::string root;
        std::string redirection;
};

class server{
    public:
        server(int n) : number(n){};
        // server(u)
        int socketAddr;
        int listen;
        int post;
        int get;
        int deletee;
        int autoindex;
        int max_size;
        int number;
        int size;
        int wor;
        int locationsNumber;
        
        int begin;
        int close;

        // std::string ip;
        std::string index;
        std::string error_page;
        std::string name;
        std::string mySer;
        std::string redirection;
        std::string root;

        std::vector<location> loc;
        infos *info;
        // location *loc;

};

class conf{
    public:
        std::vector<server> ser;
        int size;
        int serversNumber;
        std::string allIn;
};



conf *fileConfiguration(conf *conf, std::string file);
int file_size(std::string file);
int checkServersNumber(std::string file);



#endif