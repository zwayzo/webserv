#include "HttpResponse.hpp"

HttpResponse::HttpResponse() :
	_clSocket(-1),
	_serv(),
	_body(""),
	_err(0),
	_statusCode(""),
	_isCgi(false) {}

HttpResponse::HttpResponse(int clSocket, server &clientServer) :
	_clSocket(clSocket),
	_serv(clientServer),
	_body(""),
	_err(0),
	_statusCode(""),
	_isCgi(false)
{}

HttpResponse::~HttpResponse() {}

int	HttpResponse::sendResponse(HttpRequest &req) {
	if (_isCgi == false)
		_respFile(req);

}

void	HttpResponse::_respFile(HttpRequest &req) {
	int	route = _routing(req);

}

int	HttpResponse::_routing(HttpRequest &req) {
	//should find the appropriate location block for the request
	//and sets the corresponding response properties
}

