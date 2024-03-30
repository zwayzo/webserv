#include "parseRequest.hpp"

std::string toLower(const std::string& str) 
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
                   static_cast<int(*)(int)>(std::tolower));
    return lowerStr;
}
// bach ila kan edna chi body dakh b Maj n7awloh l miniscule bach mnin nbghiw n comparew mal9awch probleme


void parseHttpRequest(int fd, const char* buf, int nbytes, client *cl)
{
    std::string request(buf, nbytes);
    HttpRequest httpRequest;

    std::istringstream requestStream(request);
    std::string requestLine;
    std::string line;
    std::string headersPart;

    // {//print the header request telle quelle est la premiere fois 
    //     std::istringstream req1(request);
    //     std::string line1;
    //     while (std::getline(req1, line1))
    //         std::cout << line1 << std::endl;
    // }

    std::getline(requestStream, requestLine);
    httpRequest.request(requestLine);

    httpRequest.parseRequestLine(requestLine); 

    while (std::getline(requestStream, line) && !line.empty() && line != "\r")
        headersPart += line + "\n";

    httpRequest.parseHeaders(headersPart);

    int contentLength = 0;
    if (headerLength != std::string::npos && !cl->req._firstCheck)
    {
		if (httpRequest.is_body(contentLength, cl))
        if (cl->req.isChunked)
        {
			_getChunkedBody(fd, buf, cl);
           //hna fen hadi nhanlder CHunked;
        } 
        // else if (contentLength > 0)
        // {
        //     std::vector<char> bodyBuffer(contentLength);
        //     requestStream.read(&bodyBuffer[0], contentLength);
        //     std::string body(bodyBuffer.begin(), bodyBuffer.end());
        //     std::cout << "Corps RQ: " << body << std::endl;
        // }
    }
    else
        std::cout << "NO BODY FOUND*******" << std::endl;

    
    // std::cout << "Method: " << httpRequest.method << std::endl;
    // std::cout << "URI: " << httpRequest.uri << std::endl;
    // std::cout << "Chaine REQUEST: " << httpRequest.queryString << std::endl;
    // std::cout << "Version HTTP: " << httpRequest.httpVersion << std::endl;
    // httpRequest.printHeaders();
}

void HttpRequest::request(const std::string& requestLine) 
{
    std::istringstream iss(requestLine);
    std::getline(iss, method, ' ');
    method = toLower(method);
    std::getline(iss, uri, ' ');
    std::getline(iss, httpVersion);
}


void HttpRequest::parseRequestLine(const std::string& requestLine) 
{
    (void)requestLine;
    std::size_t questionMarkPos = uri.find('?');
    if (questionMarkPos != std::string::npos) 
    {
        queryString = uri.substr(questionMarkPos + 1);
        uri = uri.substr(0, questionMarkPos);
    } 
    else
        queryString.clear();
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

bool HttpRequest::is_body(int& contentLength, client *cl)
{
    contentLength = 0;

    //find contenu dial content-lenght
    std::map<std::string, std::string>::const_iterator it = headers.find("Content-Length");
    if (it != headers.end())
    {
        contentLength = atoi(it->second.c_str());
        return true; // true l9inaah
    }
    std::string transfer_encod("Transfer-Encoding");
        //kan9lab ela encoding norceau b morceau 
    if (headers.find("Transfer-Encoding") != headers.end() && headers[transfer_encod].find("chunked") != std::string::npos) 
    {
        cl->req.isChunked = true;
        return true; // hnaa hayl9aah apres w han9ado liha chnuked dialhaa
    }
    
    if (toLower(method) == "post")
        return true;

    return false; //ilaaa mal9inaaa walooo false 
}