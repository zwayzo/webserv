#include "../multuplixing/multuplixing.hpp"
#include "parseRequest.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

HttpRequest::HttpRequest() : status(ParsingHeaders), contentMode(NoContent), contentLength(0) {}

HttpRequest::HttpRequest(const HttpRequest& other) :
    Http(other.Http),
    protocol(other.protocol),
    path(other.path),
    headerFields(other.headerFields),
    bodyPath(other.bodyPath),
    queryString(other.queryString),
    status(other.status),
    contentMode(other.contentMode),
    buffer(other.buffer),
    contentLength(other.contentLength) {}

HttpRequest& HttpRequest::operator=(const HttpRequest& other) 
{
    if (this != &other) 
    {
        Http = other.Http;
        protocol = other.protocol;
        path = other.path;
        headerFields = other.headerFields;
        bodyPath = other.bodyPath;
        queryString = other.queryString;
        status = other.status;
        contentMode = other.contentMode;
        buffer = other.buffer;
        contentLength = other.contentLength;
    }
    return *this;
}

HttpRequest::~HttpRequest() {}

void HttpRequest::parseHttpRequest(const char* buf, int nbytes) 
{
    std::string request(buf, nbytes);
    std::istringstream requestStream(request);
    std::string requestLine, line, headersPart;

    std::getline(requestStream, requestLine);
    parseRequestLine(requestLine);

    while (std::getline(requestStream, line) && line != "\r" && !line.empty())
        headersPart += line + "\n";

    parseHeaders(headersPart);

    int contentLength = 0;
    bool isChunked = false;
    if (is_body(contentLength, isChunked)) 
    {
        std::string body;
        if (isChunked) 
            handleChunkedBody(requestStream, body);
        else 
        {
            char* buffer = new char[contentLength + 1];
            requestStream.read(buffer, contentLength);
            body.assign(buffer, contentLength);
            delete[] buffer;
        }
        std::cout << "Body RQ: " << body << std::endl;
    }
    std::cout << "Method: " << this->Http << std::endl;
    std::cout << "URI: " << this->path << std::endl;
    std::cout << "Query String: " << this->queryString << std::endl;
    std::cout << "HTTP Version: " << this->protocol << std::endl;

    for (std::map<std::string, std::string>::const_iterator it = this->headerFields.begin(); it != this->headerFields.end(); ++it)
        std::cout << it->first << ": " << it->second << std::endl;

}

bool HttpRequest::isSupportedMethod(const std::string& method) const 
{
    const std::string supportedMethods[] = {"GET", "POST", "DELETE", "PUT"};
    for (size_t i = 0; i < sizeof(supportedMethods) / sizeof(supportedMethods[0]); ++i) 
    {
        if (toLower(method) == toLower(supportedMethods[i])) 
            return true;
    }
    return false;
}

std::string HttpRequest::generateTempFileName() 
{
    static int fileCounter = 0;
    std::ostringstream fileNameStream;

    std::time_t currentTime = std::time(NULL);
    
    fileNameStream << "/tmp/http_request_" << currentTime << "_" << fileCounter++ << ".tmp";

    return fileNameStream.str();
}

void HttpRequest::parseRequestLine(const std::string& requestLine) 
{
    std::istringstream iss(requestLine);
    iss >> this->Http >> this->path >> this->protocol;
    
    size_t pos = this->path.find("?");
    if (pos != std::string::npos) 
    {
        this->queryString = this->path.substr(pos + 1);
        this->path = this->path.substr(0, pos);
    }
}

void HttpRequest::parseHeaders(const std::string& headersPart) 
{
    std::istringstream headersStream(headersPart);
    std::string line;
    std::map<std::string, std::string> tempHeaders;
    while (std::getline(headersStream, line) && !line.empty()) 
    {
        std::string::size_type colonPos = line.find(':');
        if (colonPos != std::string::npos) 
        {
            std::string headerName = toLower(line.substr(0, colonPos));
            std::string headerValue = line.substr(colonPos + 2);
            headerValue.erase(0, headerValue.find_first_not_of(" \t"));
            tempHeaders[headerName] = headerValue;
        }
    }
    setHeaderFields(tempHeaders);
}

bool HttpRequest::needBodyFile() const 
{
    if (getHttp() == "post" || getHttp() == "put") 
        return true;

    std::map<std::string, std::string>::const_iterator it;
    
    it = headerFields.find("content-length");
    if (it != headerFields.end()) 
    {
        int contentLength = std::atoi(it->second.c_str());
        if (contentLength > 0)
            return true;
    }
    
    it = headerFields.find("transfer-encoding");
    if (it != headerFields.end() && it->second == "chunked")
        return true;
    return false;
}


void HttpRequest::request(const std::string& requestLine) 
{
    std::istringstream iss(requestLine);
    std::string method, uri, httpVersion;
    std::getline(iss, method, ' ');
    if (!isSupportedMethod(method)) 
    {
        std::cerr << "Unsupported HTTP method: " << method << std::endl;
        return;
    }
    setHttp(method);
    std::getline(iss, uri, ' ');
    setPath(uri);
    std::getline(iss, httpVersion);
    setProtocol(httpVersion);

    if (needBodyFile())
        setBodyPath(generateTempFileName());
}


void HttpRequest::printHeaders() const 
{
    for (std::map<std::string, std::string>::const_iterator it = headerFields.begin(); it != headerFields.end(); ++it)
        std::cout << it->first << ": " << it->second << std::endl;
}

bool HttpRequest::is_body(int& contentLength, bool& isChunked) const 
{
    contentLength = 0;
    isChunked = false;

    std::map<std::string, std::string>::const_iterator it = headerFields.find("content-length");
    if (it != headerFields.end() && !it->second.empty()) 
        contentLength = std::atoi(it->second.c_str());

    it = headerFields.find("transfer-encoding");
    if (it != headerFields.end() && it->second.find("chunked") != std::string::npos)
        isChunked = true;

    return contentLength > 0 || isChunked;
}

void HttpRequest::handleChunkedBody(std::istringstream& stream, std::string& body) 
{
    std::string line;
    while (std::getline(stream, line) && !line.empty()) 
    {
        int chunkSize = std::strtol(line.c_str(), NULL, 16);
        if (chunkSize == 0) 
            break;
        
        std::vector<char> chunkData(chunkSize);
        stream.read(&chunkData[0], chunkSize);
        body.append(&chunkData[0], chunkSize);
        
        std::getline(stream, line);
        std::getline(stream, line);
    }
}

std::string HttpRequest::toLower(const std::string& str) 
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Getters
std::string HttpRequest::getHttp() const 
{ 
    return Http; 
}

std::string HttpRequest::getProtocol() const 
{ 
    return protocol; 

}

std::string HttpRequest::getPath() const 
{ 
    return path; 

}
std::map<std::string, std::string> HttpRequest::getHeaderFields() const 
{ 
    return headerFields; 
}

std::string HttpRequest::getBodyPath() const 
{ 
    return bodyPath; 
}

std::string HttpRequest::getQueryString() const 
{ 
    return queryString; 
}

HttpRequest::RequestStatus HttpRequest::getStatus() const 
{ 
    return status; 
}

HttpRequest::ContentDisposition HttpRequest::getContentMode() const 
{ 
    return contentMode; 
}

std::string HttpRequest::getBuffer() const 
{ 
    return buffer; 
}

size_t HttpRequest::getContentLength() const 
{ 
    return contentLength; 
}

// Setters
void HttpRequest::setHttp(const std::string& val) 
{ 
    Http = val; 
}

void HttpRequest::setProtocol(const std::string& val) 
{ 
    protocol = val; 
}

void HttpRequest::setPath(const std::string& val) 
{ 
    path = val; 
}

void HttpRequest::setHeaderFields(const std::map<std::string, std::string>& val) 
{ 
    headerFields = val; 
}

void HttpRequest::setBodyPath(const std::string& val) 
{ 
    bodyPath = val; 
}

void HttpRequest::setQueryString(const std::string& val) 
{ 
    queryString = val; 
}

void HttpRequest::setStatus(RequestStatus val) 
{ 
    status = val; 
}

void HttpRequest::setContentMode(ContentDisposition val) 
{ 
    contentMode = val; 
}

void HttpRequest::setBuffer(const std::string& val) 
{ 
    buffer = val; 
}

void HttpRequest::setContentLength(size_t val) 
{ 
    contentLength = val; 
}