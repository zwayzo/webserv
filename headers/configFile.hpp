#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

class location{
    public:
        int listen;
        int post;
        int get;
        int deletee;

        std::string index;
        std::string error_page;
        std::string name;
        std::string theLoc;
};

class server{
    public:
        server(int n) : number(n){};
        int listen;
        int post;
        int get;
        int deletee;
        int max_size;
        int number;
        int size;
        int locationsNumber;
        
        int begin;

        std::string index;
        std::string error_page;
        std::string name;
        std::string mySer;

        std::vector<location> loc;
        // location *loca;

};

class conf{
    public:
        std::vector<server> ser;
        int size;
        int serversNumber;
        std::string allIn;
};


class infos{
    public:
        std::map<int, std::string> listenMap;
        std::map<int, std::string> maxBody;
        std::map<std::string, std::string> serverName;
        std::map<std::string, std::string> root;
        std::map<std::string, std::string> Index;
        std::map<std::string, std::string> errorPage;
        std::map<std::string, std::string> methodes;
        std::map<std::string, std::string> redirection;
};

void fileConfiguration(conf *conf, std::string file);
int file_size(std::string file);
int checkServersNumber(std::string file);



#endif