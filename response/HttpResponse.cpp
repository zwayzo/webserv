#include "HttpResponse.hpp"

HttpResponse::HttpResponse() :
	_clSocket(-1),
	_serv(),
	_body(""),
	_errCode(0),
	_statusCode(""),
	_isCgi(false),
	_root(""),
	_fd(0) {}

HttpResponse::HttpResponse(int clSocket, server &clientServer) :
	_clSocket(clSocket),
	_serv(clientServer),
	_body(""),
	_errCode(0),
	_statusCode(""),
	_isCgi(false),
	_root(""),
	_index(""),
	_fd(0),
	_path("") {}

HttpResponse::~HttpResponse() {}

int	HttpResponse::buildResponse(HttpRequest &req) {
	// if (_isCgi == false)
	// 	_respFile(req);
	int re = get_requested_resource(req);
	return re;
}

int		HttpResponse::get_requested_resource(HttpRequest &req) {
	std::string _resource = req.getUri();
	std::cout << "URL:" << _resource << std::endl;
	const std::vector<location> &locations = req.getConfServ().loc;

	//Matching location
    for (size_t i = 0; i < locations.size(); ++i) {
        const location &location = locations[i];
        const std::string &locationName = location.name;
        const std::string &requestPath = req.getUri();
 		size_t foundPos = requestPath.find(locationName);
		std::cout << "FoundPos: "<< foundPos << "\n";
        if (foundPos == 0) {
            _setPropertiesFromLocation(location, requestPath, i);
            return 0;
        }
    }

	this->_root = this->_serv.root;
	this->_index = this->_serv.index;
	this->_error_page = this->_serv.error_page;
	this->_autoindex = this->_serv.autoindex;
	_retrievePath(req.getUri(), this->_root, this->_index);

	return 0;
}

std::string	HttpResponse::_matchLocationForRelativePath(const std::string &requestPath, const std::string &locationName) {
	size_t	pos = requestPath.find(locationName);
	std::cout << pos << "\n";

	if (requestPath.find_first_of(locationName) == 1){
		std::cout << "===LocationName: " << locationName << std::endl;
		std::cout << "length: " << locationName.length() << std::endl;
		return requestPath.substr(locationName.length() + 1);
	}
	else if (pos != std::string::npos)
		return requestPath.substr(0, pos);
	return requestPath;
}

void	HttpResponse::_setPropertiesFromLocation(const location &location, const std::string &requestPath, size_t locationIndex) {
	_root = location.root;
	_index = location.index;
	_autoindex = location.autoindex;
	_redirection = location.redirection;
	// _error_page = location.
	std::string _pa = _matchLocationForRelativePath(requestPath, location.name);
	std::cout << "Relative path: "<< _pa << std::endl;
	std::string idx = "";
	_retrievePath(_pa, _root, idx);
	std::cout << "path: "<< this->_path << std::endl;
}

void	HttpResponse::_retrievePath(const std::string &url, std::string &rt, std::string &idx) {
	std::string	_validPath = url;

	if (url.empty() || url[0] != '/')
		_validPath = '/' + url;
	else if (!url.empty() && url[url.length() - 1] == '/')
		_validPath += idx;

	this->_path = rt + _validPath;
}


// void	HttpResponse::_respFile(HttpRequest &req) {
// 	// int	route = _routing(req)


// }

// 	//should find the appropriate location block for the request
// 	//and sets the corresponding respo