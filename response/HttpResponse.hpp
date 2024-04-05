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
#include "../headers/header.hpp"
#ifndef SUCCESS
# define	SUCCESS 2
#endif

class HttpRequest;

class HttpResponse {
	private:
		int			_clSocket;
		server		_serv;
		std::string	_body;
		int			_err;
		std::string	_statusCode;
		bool		_isCgi;

	public:
		std::string	_root;
		HttpResponse();
		HttpResponse(int clSocket, server &clientServer);
		~HttpResponse();

		int		sendResponse(HttpRequest &req);
		void	_respFile(HttpRequest &req);
		int		_routing(HttpRequest &req);
};

#endif
