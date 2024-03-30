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
			if (this->_serv.info->maxBody.second >= _bodySize) {//should check the max body in the conf file >= _bodySize
				if ((this->_method == "POST") && this->_uri.find(".py") == std::string::npos
					&& this->_uri.find(".rb") == std::string::npos) {
						if (_methodExist()) {
							std::string	file = _randomName();
							std::string	uploadPath = _findUploadPath();
							_creatFile(uploadPath + file, this->_body)
							//should check if the _method is within the allowed method in the conf file
							//should check the uri and location
							//should generate a random file name and find the uploadPath
							//should create the file
						}
						else
							this->_statusCode = 405; //Method Not Allowed
				}
			}
			else
				this->_statusCode = 413; /*Content Too Large response status code indicates that
			the request entity is larger than limits defined by server*/
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

bool	HttpRequest::_methodExist(void) {
	//check if the method exist in the server in conf file
	return true;
}

std::string	HttpRequest::_findUploadPath(void) {
	size_t	len = this->_serv.loc.size();
	std::string	upload = this->_serv.uploads; // get the uploadPath in the conf File if there is a section named upload

	for(size_t i = 0; i < len; i++) {
		if (this->_uri.find(this->_serv.loc[i].) != std::string::npos) //find the location Name in the uri
			upload = this->_serv.loc[i].uploads; //get the upload Path
	}
	return upload;
}

void	HttpRequest::_creatFile(std::string name, std::string reqBody) {
	std::ofstream	file(name.c_str());

	if (!file)
		this->_statusCode = 500; //500 Internal Server Error
	else {
		file << reqBody;
		file.close();
		this->_statusCode = 201; /*201 Created success status response code indicates
		that the request has succeeded and has led to the creation of a resource*/
	}
}

std::string	HttpRequest::_randomName(void) {
	const std::string	alphanum = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-&^$@(#)";
	std::string			randName = "";
	std::srand(static_cast<unsigned int>(time(NULL)));
	for(int i = 0; i < 15; i++) {
		int _rand = std::rand() % alphanum.length();
		randName += alphanum[_rand];
	}
	return randName;
}

int hextoint(const std::string str) {
	int	intValue;
	std::istringstream(str) >> std::hex >> intValue;
	return intValue;
}
