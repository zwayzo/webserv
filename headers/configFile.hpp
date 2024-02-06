#include <iostream>

class location{
    public:
        int listen;
        int post;
        int get;
        int deletee;

        std::string index;
        std::string error_page;
        std::string name;
};

class serveur{
    public:
        int listen;
        int post;
        int get;
        int deletee;
        int max_size;

        std::string index;
        std::string error_page;
        std::string name;

        location *loca;

};

class conf{
    public:
        serveur *ser;
};