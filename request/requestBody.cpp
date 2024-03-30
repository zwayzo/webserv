#include "parseRequest.hpp"

void	HttpRequest::findServer() {
	if (headers.find("Host") != headers.end()) {
		std::string host = _headers["Host"];
	}
}

void	HttpRequest::parseBody(size_t &bodypos, client *cl) {
	findServer();
	 // if (headerLength != std::string::npos && !cl->req._firstCheck)
    // {
	int contentLength = 0;
	if (httpRequest.is_body(contentLength, cl))
		
        if (cl->req.isChunked) {
			_getChunkedBody(bodypos, &iter->second);
        } 
        // else if (contentLength > 0)
        // {
        //     std::vector<char> bodyBuffer(contentLength);
        //     requestStream.read(&bodyBuffer[0], contentLength);
        //     std::string body(bodyBuffer.begin(), bodyBuffer.end());
        //     std::cout << "Corps RQ: " << body << std::endl;
        // }
    // }
    else
        std::cout << "NO BODY FOUND*******" << std::endl;

}

bool HttpRequest::is_body(int& contentLength, client *cl)
{
    contentLength = 0;
    std::string transfer_encod("Transfer-Encoding");

        //kan9lab ela encoding morceau b morceau 
    if (headers.find("Transfer-Encoding") != headers.end() \
		&& headers[transfer_encod].find("chunked") != std::string::npos) {
        cl->req.isChunked = true;
        return true;
    }
    if (toLower(method) == "post")
        return true;

    //find contenu dial content-lenght
    // std::map<std::string, std::string>::const_iterator it = headers.find("Content-Length");
    // if (it != headers.end())
    // {
    //     contentLength = atoi(it->second.c_str());
    //     return true; // true l9inaah
    // }
    return false; //ayaetina makaynch body but we should first check l function li qade loujdi hit howa li mqade contentlenght
}

void	HttpRequest::_getChunkedBody(size_t &bodypos, client *cl) {
	std::string	tmp = _request.substr(bodypos + 2);
	size_t	bodySize = tmp.size();

	for (size_t i = 0; i < bodySize; i++) {
		std::string	chunk = "";
		size_t	j = i;
		for (; tmp[j] != '\r'; j++) {
			chunk += tmp[j];
		}
		i = j + 2;
		int	chunkedSize = hextoint(chunk);
		if (chunkedSize == 0)
			break ;
		cl->req._body += tmp.substr(i, chunkedSize);
		i += chunkedSize + 1;
	}
}
