#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "../multuplixing/multuplixing.hpp"
#include "../configFile/configFile.hpp"
#include "../request/parseRequest.hpp"
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
		void	_respFile(Request &req);
};

#endif
