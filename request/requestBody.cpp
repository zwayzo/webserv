#include "parseRequest.hpp"

void	HttpRequest::findServer(client *cl) {
	if (headers.find("Host") != headers.end()) {
		std::string host = _headers["Host"];
		for (std::vector<server>::iterator it = _servers.begin(); it != _servers.end(); it++) {
			if (it->name == host || it->name+":"+std::to_string(cl->port) == host) {
				this->_serv = *it;
				return ;
			}
		}
	}
	this->_serv = this->_servers[0];
}

void	HttpRequest::parseBody(size_t &bodypos, client *cl) {
	findServer(cl);
	int contentLength = 0;
	if (is_body(contentLength, cl)) {
        if (this->isChunked) {
			_getChunkedBody(bodypos, &iter->second);
			this->_bodySize = this->_body.size();
			if ((this->_method == "POST") && this->_uri.find(".py") == std::string::npos
				&& this->_uri.find(".rb") == std::string::npos) {
					if (methodExist()) {

					}
					else
						this->_statusCode = 405;
				//should check if the _method is within the allowed method in the conf file
				//
			}
        }
	}
	else
		std::cout << "NO BODY FOUND*******" << std::endl;
    // else if (contentLength > 0)
        // {
        //     std::vector<char> bodyBuffer(contentLength);
        //     requestStream.read(&bodyBuffer[0], contentLength);
        //     std::string body(bodyBuffer.begin(), bodyBuffer.end());
        //     std::cout << "Corps RQ: " << body << std::endl;
        // }
}

bool HttpRequest::is_body(int& contentLength, client *cl)
{
    contentLength = 0;
    std::string transfer_encod("Transfer-Encoding");

        //kan9lab ela encoding morceau b morceau 
    if (headers.find("Transfer-Encoding") != headers.end() \
		&& headers[transfer_encod].find("chunked") != std::string::npos) {
        this->isChunked = true;
        return true;
    }
    if (toLower(this->_method) == "post")
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
	std::string	tmp = this->_request.substr(bodypos + 2);
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
		this->_body += tmp.substr(i, chunkedSize);
		i += chunkedSize + 1;
	}
}

int hextoint(const std::string str) {
	int	intValue;
	std::istringstream(str) >> std::hex >> intValue;
	return intValue;
}
