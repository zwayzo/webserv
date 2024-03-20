#ifndef PARSEREQUEST_HPP
#define PARSEREQUEST_HPP

#include <map>
#include "parseRequest.hpp"
#include "header.hpp"
#include"configFile.hpp"
#include "multuplixing.hpp"
#include "header.hpp"
#include"configFile.hpp"
#include "header.hpp"
#include "configFile.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netdb.h>
#include <cstdlib>
#include <string>
#include <csignal>
#include <signal.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>

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