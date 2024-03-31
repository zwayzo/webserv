#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
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
        std::map<std::string, std::string> uploads;
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
        std::string uploads;
};

class server{
    public:
        server(int n) : number(n){};
        // server(u)
        int socketAddr;
        int sock;
        int listen_fd;

        int listen;
        int listen_number;

        int post;
        int get;
        int deletee;

        int autoindex;
        int autoindex_number;

        int max_size;
        int max_size_number;

        int number;
        int size;
        int wor;

        int locationsNumber;
        int methodes_number;
        
        int begin;
        int close;

        // std::string ip;
        std::string index;
        int index_number;
        std::string error_page;
        int error_page_number;
        std::string name;
        int name_number;
        std::string mySer;
        std::string redirection;
        int redirection_number;
        std::string root;
        int root_number;
        std::string uploads;
        int uploads_number;

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
        std::vector<int> vec;
};


conf *fileConfiguration(conf *conf, std::string file);
int checkServersNumber(std::string file);
void checkComma(std::string mySer);
void initLocation(server &ser, int n);
void wordCounter(server &ser);
void printArguments(infos *info, int n, server &ser);
int storeLocationValue(server &ser, int n, int number);
infos *checkValue(std::string mySer, infos *info, server &ser); 
void checkPrototype(server &ser);
void checkAcollade(server &ser);
void stockLocation(conf *conf, int indice);
void getBegin(int indice, conf *conf, std::string allIn);
void stockserver(std::string allIn, conf *conf, int indice);
void serverSize(std::string allIn, int indice, conf *conf);
int locationsNumbers(std::string mySer);
std::string getTheFileInOneString(std::string file);
int file_size(std::string file);
void checkConfigFileRules(server &ser);
void init_variables(server &ser);

#endif