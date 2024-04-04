#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

#include "../multuplixing/multuplixing.hpp"
#include "../configFile/configFile.hpp"
#include "../request/HttpRequest.hpp"
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>

class server;
class conf;
class client;
class HttpRequest;

class Response {
	private:
		std::string	_body;
		int			_err;
		std::string	_statusCode;
		bool		_isCgi;

	public:
		std::string	_root;
		Response();
		~Response();

		int		sendResponse(HttpRequest &req);
		void	_respFile(HttpRequest &req);
		int		_routing(HttpRequest &req);
};

#endif
