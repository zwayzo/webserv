
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

        // same as the server just if we don't have like the root in
        //the location it will set to the server root par default
        std::string index;
        std::string name; //name of location (profile/ name/)
        std::string theLoc;
        std::string root;
        std::string redirection;
        std::string uploads;
};

class server{
    public:
        server();
        server(int n) : number(n){};
        server(const server& copy)
        {
            this->autoindex = copy.autoindex;
            this->listen = copy.listen;
            this->post = copy.post;
            this->get = copy.get;
            this->deletee = copy.deletee;
            this->max_size = copy.max_size;
            this->methodes_number = copy.methodes_number;
            this->locationsNumber = copy.locationsNumber;
            this->index = copy.index;
            this->error_page = copy.error_page;
            this->redirection = copy.redirection;
            this->root = copy.root;
            this->uploads = copy.uploads;
            // Copy the location objects
            this->loc.resize(copy.loc.size()); // Ensure the same size
            for (size_t i = 0; i < copy.loc.size(); ++i) {
                this->loc[i] = copy.loc[i]; // Assuming location has a proper copy constructor
    }
        }
        //--------
        //this are for multuplixing
        int socketAddr;
        int sock;
        int listen_fd;
        int listen;
        int listen_number;
        //---------
        int post; //if it's allowed will be 1 else it 0
        int get; //if it's allowed will be 1 else it 0
        int deletee; //if it's allowed will be 1 else it 0
        int autoindex; //if we don't have it's 2 , if it's on it's 1 , off 0
        int autoindex_number;
        int max_size; //max bosy size
        int max_size_number;
        int number;
        int size;
        int wor;
        int locationsNumber; //locations number in the server
        int methodes_number;
        
        int begin;
        int close;

        // std::string ip;
        std::string	root; //directory path wher should get the images or whatever should appear when i connect the client with server
        int			root_number;
        std::string index; //specific which index(file) from the root(directory)
        int			index_number;
        std::string error_page; //error pages path 404 403 etc mazal mamriglin 100%
        int			error_page_number;
        std::string name; //name of server (localhost)
        int			name_number;
        std::string mySer;
        std::string redirection; //the redirection path
        int			redirection_number;
        std::string uploads; //wher should the post be uploaded
        int uploads_number;

        std::vector<location> loc; //verctors of location we reserve x if we have x locations in the server
        infos *info;
        //NOTE BIEN: everything with number like root_number index_number... just to
        //protect our config file like if we don't have roort it should not work so i check 
        //thet root number

};

class conf{
    public:
        std::vector<server> ser; //vectors of servers if we have 5 servers w reserve 5
        int size;
        int serversNumber; //servers number in the config file
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
int skipLocation(server &ser, int i);

#endif
