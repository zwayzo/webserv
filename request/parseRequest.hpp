#ifndef PARSEREQUEST_HPP
#define PARSEREQUEST_HPP

// #include "../headers/header.hpp"
// #include "parseRequest.hpp"
#include<string>
#include "../multuplixing/multuplixing.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <iomanip>
#include "chunkedPost.hpp"

class client;

class HttpRequest {

    public:
        std::string method;
        std::string uri;
        std::string httpVersion;
        std::string queryString;
        std::map<std::string, std::string>	headers;
        std::string							_request;

        HttpRequest();
        ~HttpRequest();
        bool is_body(int& contentLength, client *cl);
        void parseHeaders(const std::string& headersPart);
        void printHeaders() const ;
        void request(const std::string& requestLine);
        // void requestRequest();
        void parseRequestLine(const std::string& requestLine);

        //body (chunked)
        void    parseBody(size_t &bodypos, client *cl);
        void    findServer();
        void	_getChunkedBody(size_t &bodypos, client *cl);

};
        void parseHttpRequest(const char* buf, int nbytes, std::map<int, client>::iterator iter);
        void unchunkBody(std::istringstream& requestStream);
        void readFixedLengthBody(std::istringstream& requestStream, int contentLength);

#endif