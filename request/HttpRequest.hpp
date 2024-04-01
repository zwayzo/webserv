#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

// #include "../headers/header.hpp"
#include "../multuplixing/multuplixing.hpp"
#include "../configFile/configFile.hpp"
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>
#include <iterator>

class server;
class conf;
class client;

int     hextoint(const std::string str);
std::string toLower(const std::string& str);

template <typename T>
std::string toString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

class HttpRequest {

    public:
        std::string _method;
        std::string _uri;
        std::string httpVersion;
        std::string queryString;

        std::map<std::string, std::string>	headers;

        std::string			_request;
        bool				isChunked;
		std::string 		_body;
		size_t				_bodySize;
		std::string			_servName;
		int					_port;
		int					_err;
		// bool            _firstCheck;

        HttpRequest();
        ~HttpRequest();
        bool is_body(int& contentLength, client *cl);
        void parseHeaders(const std::string& headersPart);
        void printHeaders() const ;

        void parseRequestLine(const std::string& reqLine);
        void parseURI(void);
        // void requestRequest();
        void parseHttpRequest(const char* buf, int nbytes, client *cl);

        //body (chunked)
        void    parseBody(size_t &bodypos, client *cl);
        void    findServer(client *cl);
        void	_getChunkedBody(size_t &bodypos, client *cl);

		//Allowed methods and randName
		bool		_methodExist(void);
		std::string	_randomName(void);
		std::string	_findUploadPath(client *cl);
		void		_creatFile(std::string name, std::string reqBody);
};

void unchunkBody(std::istringstream& requestStream);
void readFixedLengthBody(std::istringstream& requestStream, int contentLength);

#endif