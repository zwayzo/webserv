#ifndef MULTUPLIXING_HPP
#define MULTUPLIXING_HPP

#include "../headers/header.hpp"
#include "../request/request.hpp"
#include "../request/HttpRequest.hpp"
#include "../multuplixing/client.hpp"

class multuplix{
    public:
        std::map <int, client>		mycl;
		std::map<int, HttpRequest>	_httpRequest;

        multuplix(){};
        multuplix(multuplix &copy){(void)copy;};
        ~multuplix(){};
        void multuplixing(conf* conf);
};


#endif