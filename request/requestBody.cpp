#include "../multuplixing/multuplixing.hpp"
#include "HttpRequest.hpp"

// void	HttpRequest::findServer() {

	// if (headers.find("Host") != headers.end()) {
	// 	std::string host = headers["Host"];
	// 	if (this->_confServ.name == host) {
	// 			= cl->name;
	// 			return ;
	// 	}
	// }
// }

void	HttpRequest::parseBody(size_t &bodypos) {
	// findServer(); //which server if there is multiple ones
	int contentLength = 0;
	if (is_body(contentLength)) {
		if (this->isChunked) {
			_getChunkedBody(bodypos);
			this->_bodySize = this->_body.size();
			if (this->_confServ.max_size >= this->_bodySize) {//should check the max body in the conf file >= _bodySize
				if ((this->_method == "post") && this->_uri.find(".py") == std::string::npos
					&& this->_uri.find(".rb") == std::string::npos) {
						if (_methodExist()) //isMethodAllowed
						{
							std::string	file = _randomName();
							std::string	uploadPath = _findUploadPath();
							_creatFile(uploadPath + file, this->_body);
							//should check the uri and location
							//should generate a random file name and find the uploadPath
							//should create the file
						}
						else
							this->_err = 405; //Method Not Allowed
				}
			}
			else
				this->_err = 413; /*Content Too Large response status code indicates that
			the request entity is larger than limits defined by server*/
		}
		// else if (contentLength > 0)
			// {
			//     std::vector<char> bodyBuffer(contentLength);
			//     requestStream.read(&bodyBuffer[0], contentLength);
			//     std::string body(bodyBuffer.begin(), bodyBuffer.end());
			//     std::cout << "Corps RQ: " << body << std::endl;
			// }
	}
	else {
		std::cout << "NO BODY FOUND*******" << std::endl; //3andna GET wla DELETE
	}
}

bool HttpRequest::is_body(int& contentLength)
{
	// contentLength = 0;

    //find contenu dial content-lenght
	std::map<std::string, std::string>::iterator iter = headers.find("Content-Length");
    if (iter != headers.end()) {
        contentLength = atoi(iter->second.c_str());
        return true; // true l9inaah
    }
	std::string transfer_encod("Transfer-Encoding");
	if (headers.find("Transfer-Encoding") != headers.end() \
		&& headers[transfer_encod].find("chunked") != std::string::npos) {
		this->isChunked = true;
		return true;
	}
	else if (headers.find("Transfer-Encoding") != headers.end() \
		&& headers[transfer_encod].find("chunked") == std::string::npos) {
		this->_err = 501; //Not implemented
		return false;
	}
	else if (this->_method == "post" && headers.find("Content-Length") == headers.end()
		&& headers.find("Transfer-Encoding") == headers.end()) {
		this->_err = 400; //Bad Request
		return false;
	}
	// if (toLower(this->_method) == "post")
	// 	return true;
	return false; //ayaetina makaynch body but we should first check l function li qade loujdi hit howa li mqade contentlenght
}

void	HttpRequest::_getChunkedBody(size_t &bodypos) {
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
	std::vector<std::string> _isAllowedMeth = this->_confServ._methods;
	size_t	len = this->_confServ.loc.size();

	for(size_t i = 0; i < len; i++) {
		if (this->_uri.find(this->_confServ.loc[i].name) != std::string::npos) {//find the location Name in the uri
			_isAllowedMeth = this->_confServ.loc[i]._methods;
			break ;
		} //update the method vector
	}
		// Check if the request method is found in the vect of allowed methods
    return (std::find(_isAllowedMeth.begin(), _isAllowedMeth.end(), this->_method) != _isAllowedMeth.end());
}

std::string	HttpRequest::_findUploadPath(void) {
	size_t	len = this->_confServ.loc.size();
	std::string	download = this->_confServ.uploads; // get the uploadPath in the conf File if there is a section named upload

	for(size_t i = 0; i < len; i++) {
		if (this->_uri.find(this->_confServ.loc[i].name) != std::string::npos) //find the location Name in the uri
			download = this->_confServ.loc[i].uploads; //get the upload Path
	}
	return download;
}

void	HttpRequest::_creatFile(std::string name, std::string reqBody) {
	std::ofstream	file(name.c_str());

	if (!file)
		this->_err = 500; //500 Internal Server Error
	else {
		file << reqBody;
		file.close();
		this->_err = 201; /*201 Created success status response code indicates
		that the request has succeeded and has led to the creation of a resource*/
	}
}

std::string	HttpRequest::_randomName(void) {
	const std::string	alphanum = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-&$@(#)";
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
