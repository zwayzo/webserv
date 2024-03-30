#include "Response.hpp"

Response::Response() : _err(0), _statusCode(""),
	_isCgi(false) {}

Response::~Response() {}

int	Response::sendResponse(HttpRequest &req) {
	_findServer(req);
	if (_isCgi == false)
		_respFile(req);

}

void	Response::_respFile(Request &req) {
	int	route = _routing(req);

}

int	Response::_routing(Request &req) {
	//should find the appropriate location block for the request and sets the corresponding response properties
}

