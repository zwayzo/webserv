#include "parseRequest.hpp"

HttpRequest::HttpRequest() :
	_request(""),
	_method(""),
	_uri(""),
	httpVersion("");
	isChunked(false), _body(""), _bodySize(0),
	_err(0);
	_serv(),
	_servers() {
}

HttpRequest::~HttpRequest() {
	this->headers.clear();
}

std::string toLower(const std::string& str) 
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
                   static_cast<int(*)(int)>(std::tolower));
    return lowerStr;
}

void HttpRequest::parseHttpRequest(const char* buf, int nbytes, client *cl)
{
    // HttpRequest 		httpRequest;
	this->_request(buf, nbytes);
    std::istringstream	requestStream(this->_request);
    std::string 		reqLine;
    std::string	line;
    std::string headersPart;

    // {//print the header request telle quelle est la premiere fois 
    //     std::istringstream req1(this->_request);
    //     std::string line1;
    //     while (std::getline(req1, line1))
    //         std::cout << line1 << std::endl;
    // }

    std::getline(requestStream, reqLine);
    parseRequestLine(reqLine);
	if (this->_err != 400)
	{
		parseURI();
		if (this->_err != 403)
		{
			while (std::getline(requestStream, line) && !line.empty() && line != "\r")
				headersPart += line + "\n";
			parseHeaders(headersPart);

			std::streampos endHdrPos = requestStream.tellg();
			size_t bodypos = static_cast<size_t>(endHdrPos);
			std::cout << "Pos aprs Header: " << bodypos << std::endl;

			// this->_port = cl->port;
			parseBody(bodypos, cl);
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
	if (_uri.find("..") != std::string::npos)
		this->_err = 403; //403 Forbidden: Accès interdit. Traversée de répertoire non autorisée.
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
            headers[headerName] = headerValue;
        }
    }
}

void HttpRequest::printHeaders() const 
{
    for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it)
        std::cout << it->first << ": " << it->second << std::endl;
}
