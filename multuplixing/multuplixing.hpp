#ifndef MULTUPLIXING_HPP
#define MULTUPLIXING_HPP

#include "../headers/header.hpp"
#include "../request/request.hpp"
#include "../request/parseRequest.hpp"
#include "../multuplixing/client.hpp"

class multuplix{
    public:
        multuplix(){};
        multuplix(multuplix &copy){(void)copy;};
        ~multuplix(){};
        std::map <int, client> mycl;
        void multuplixing(conf* conf);


};


#endif