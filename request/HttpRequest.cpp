#include "../multuplixing/multuplixing.hpp"
#include "HttpRequest.hpp"

HttpRequest::HttpRequest() :
	_clSocket(-1),
	_confServ(),
	_method(""),
	_uri(""),
	httpVersion(""),
    queryString(""),
	_request(""),
	isChunked(false),
	_body(""), _bodySize(0),
	_err(0) {
}

HttpRequest::HttpRequest(int clSock, server clientServ) :
	_clSocket(clSock),
	_confServ(clientServ),
	_method(""),
	_uri(""),
	httpVersion(""),
    queryString(""),
	_request(""),
	isChunked(false),
	_body(""), _bodySize(0),
	_err(0) {}

HttpRequest::HttpRequest(const HttpRequest& other) :
	_clSocket(other._clSocket),
	_confServ(other._confServ),
	_method(other._method),
	_uri(other._uri),
	httpVersion(other.httpVersion),
    queryString(other.queryString),
	headerFields(other.headerFields),
	_request(other._request),
	isChunked(other.isChunked),
	_body(other._body),
	_bodySize(other._bodySize),
	_err(other._err) {}

HttpRequest& HttpRequest::operator=(const HttpRequest& other) 
{
    if (this != &other) 
    {
        _clSocket = other._clSocket;
        _confServ = other._confServ;
        _method = other._method;
        _uri = other._uri;
        httpVersion = other.httpVersion;
        queryString = other.queryString;
        headerFields = other.headerFields;
        _request = other._request;
        isChunked = other.isChunked;
        _body = other._body;
        _bodySize = other._bodySize;
        _port = other._port;
        _err = other._err;
    }
    return *this;
}

HttpRequest::~HttpRequest() {
	this->headerFields.clear();
}

//Getters
int	HttpRequest::getClSocket() const {
	return this->_clSocket;
}

server HttpRequest::getConfServ() const {
	return this->_confServ;
}

std::string HttpRequest::getMethod() const {
	return this->_method;
}

std::string HttpRequest::getUri() const {
	return this->_uri;
}

std::string HttpRequest::getHttpVersion() const {
	return this->httpVersion;
}

std::string HttpRequest::getQueryString() const {
	return this->queryString;
}

std::map<std::string, std::string> HttpRequest::getHeaderFields() const {
	return this->headerFields;
}

std::string HttpRequest::getRequest() const {
	return this->_request;
}

bool	HttpRequest::getChunkedStatus() const {
	return this->isChunked;
}

std::string	HttpRequest::getBody() const {
	return this->_body;
}

size_t	HttpRequest::getBodySize() const {
	return this->_bodySize;
}

int	HttpRequest::getCodeError() const {
	return this->_err;
}

std::string toLower(const std::string& str)
{
	std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
			static_cast<int(*)(int)>(std::tolower));
    return lowerStr;
}

std::string toUpper(const std::string& str)
{
	std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
			static_cast<int(*)(int)>(std::toupper));
    return lowerStr;
}

void HttpRequest::parseHttpRequest(const char* buf, int nbytes)
{
	std::string	tmp(buf, nbytes);
	this->_request = tmp;
    std::istringstream	requestStream(this->_request);
    std::string 		reqLine;
    std::string	line;
    std::string headersPart;

    std::getline(requestStream, reqLine);
    parseRequestLine(reqLine);
	if (this->_err != 400)
	{
		parseURI();
		if (this->_err != 414)
		{
			while (std::getline(requestStream, line) && !line.empty() && line != "\r")
				headersPart += line + "\n";
			parseHeaders(headersPart);

			std::streampos endHdrPos = requestStream.tellg();
			size_t bodypos = static_cast<size_t>(endHdrPos);
			std::cout << "Pos aprs Header: " << bodypos << std::endl;
			std::cout << "Character in position 281: " << _request[bodypos] << std::endl;
            
			this->_port = this->_confServ.listen;
			parseBody(bodypos);
			//shouldHandleDelete
		}
	}
    
    // std::cout << "Method: " << httpRequest.method << std::endl;
    // std::cout << "URI: " << httpRequest.uri << std::endl;
    // std::cout << "Chaine REQUEST: " << httpRequest.queryString << std::endl;
    // std::cout << "Version HTTP: " << httpRequest.httpVersion << std::endl;
    // httpRequest.printHeaders();
}

void HttpRequest::parseRequestLine(const std::string& reqLine) 
{
    std::istringstream iss(reqLine);
    std::getline(iss, _method, ' ');
    if (_method != "POST" && _method !="GET" && _method != "DELETE")
		this->_err = 400; /*bad Request {malformed request syntax,
		invalid request message framing, or deceptive request routing*/
    _method = toLower(_method);
    std::getline(iss, _uri, ' ');
    std::getline(iss, httpVersion);
}

void HttpRequest::parseURI(void) 
{
    std::size_t questionMarkPos = _uri.find('?');
    if (questionMarkPos != std::string::npos) 
    {
        queryString = _uri.substr(questionMarkPos + 1);
		_uri = _uri.substr(0, questionMarkPos);
    } 
    else
        queryString.clear();
    if (_uri.length() > 2048)
        this->_err = 414; //414 URI Too Long
	// else if (_uri.find("..") != std::string::npos)
	// 	this->_err = 403; //403 Forbidden: Accès interdit. Traversée de répertoire non autorisée.
}

void HttpRequest::parseHeaders(const std::string& headersPart)
{
    std::istringstream headersStream(headersPart);
    std::string line;
    while (std::getline(headersStream, line) && !line.empty()) 
    {
        std::string::size_type colonPos = line.find(':');
        if (colonPos != std::string::npos) 
        {
            std::string headerName = line.substr(0, colonPos);
            std::string headerValue = line.substr(colonPos + 2);
            headerValue.erase(0, headerValue.find_first_not_of(" \t"));
            headerFields[headerName] = headerValue;
        }
    }
}

void HttpRequest::printHeaders() const 
{
    for (std::map<std::string, std::string>::const_iterator it = headerFields.begin(); it != headerFields.end(); ++it)
        std::cout << it->first << ": " << it->second << std::endl;
}
