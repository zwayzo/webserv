#ifndef MULTUPLIXING_HPP
#define MULTUPLIXING_HPP

#include "../headers/header.hpp"
#include "../request/request.hpp"
// #include "../request/HttpRequest.hpp"
// #include "../response/HttpResponse.hpp"
#include "../multuplixing/client.hpp"
class HttpResponse;
class client;

class multuplix{
    private:
		// std::map<int, HttpRequest>	_httpRequest;
        // std::map<int, HttpResponse>	_httpResponse;

    public:
        std::map <int, client>		mycl;

        multuplix();
        multuplix(multuplix &copy);
        ~multuplix();
        void multuplixing(conf* conf);
};

#endif