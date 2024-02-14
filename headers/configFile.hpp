#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include <iostream>
#include <fstream>
#include <vector>

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

void fileConfiguration(conf *conf, std::string file);
int file_size(std::string file);
int checkServersNumber(std::string file);


#endif