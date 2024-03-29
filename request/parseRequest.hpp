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
#include "chunkedPost.hpp"

class HttpRequest {

    public:
        std::string method;
        std::string uri;
        std::string httpVersion;
        std::string queryString;
        std::map<std::string, std::string> headers;

        bool is_body(int& contentLength, client *cl);
        void parseHeaders(const std::string& headersPart);
        void printHeaders() const ;
        void request(const std::string& requestLine);
        // void requestRequest();
        void parseRequestLine(const std::string& requestLine);



        

};
        void parseHttpRequest(int fd, const char* buf, int nbytes, client *cl);
        void unchunkBody(std::istringstream& requestStream);
        void readFixedLengthBody(std::istringstream& requestStream, int contentLength);

#endif