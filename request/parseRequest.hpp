#ifndef PARSEREQUEST_HPP
#define PARSEREQUEST_HPP

// #include "../headers/header.hpp"
#include "parseRequest.hpp"
#include<string>
#include "../multuplixing/multuplixing.hpp"
#include "parseRequest.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
// #include <map>
class HttpRequest {

    public:
        std::string method;
        std::string uri;
        std::string httpVersion;
        std::string queryString;
        std::map<std::string, std::string> headers;

        bool is_body(int& contentLength, bool& isChunked) const ;
        void parseHeaders(const std::string& headersPart);
        void printHeaders() const ;
        void request(const std::string& requestLine);
        // void requestRequest();
        void parseRequestLine(const std::string& requestLine);



        

};
        void parseHttpRequest(const char* buf, int nbytes);
        void unchunkBody(std::istringstream& requestStream);
        void readFixedLengthBody(std::istringstream& requestStream, int contentLength);

#endif