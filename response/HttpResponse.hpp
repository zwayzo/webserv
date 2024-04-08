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
#ifndef SUCCESS
# define	SUCCESS 2
#endif

class HttpRequest;
class location;

class HttpResponse {
	private:
		int			_clSocket;
		server		_serv;
		std::string	_body;
		int			_errCode;
		std::string	_statusCode;
		bool		_isCgi;
		std::string	_root;
		std::string	_index;
		std::string	_error_page;
		int			_autoindex;
		std::string	_redirection;
		std::vector<location>	_loc;
		int			_fd;
		std::string _path;

	public:
		// std::string	_root;
		HttpResponse();
		HttpResponse(int clSocket, server &clientServer);
		~HttpResponse();

		int		buildResponse(HttpRequest &req);
		int		get_requested_resource(HttpRequest &req);
		void	_setPropertiesFromLocation(const location &location, const std::string &requestPath, size_t locationIndex);
		std::string	_matchLocationForRelativePath(const std::string &requestPath, const std::string &locationName);
		void	_retrievePath(const std::string &url, std::string &rt, std::string &idx);
		void	_respFile(HttpRequest &req);
};

#endif
