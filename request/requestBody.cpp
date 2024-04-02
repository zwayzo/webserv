#include "../multuplixing/multuplixing.hpp"
#include "HttpRequest.hpp"

// void	HttpRequest::findServer() {

	// if (headerFields.find("Host") != headerFields.end()) {
	// 	std::string host = headerFields["Host"];
	// 	if (this->_confServ.name == host) {
	// 			= cl->name;
	// 			return ;
	// 	}
	// }
// }

void	HttpRequest::parseBody(size_t &bodypos) {
	// std::cout << "Server for our request is: " << this->_confServ.listen << std::endl;
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
							std::string	file = _generateTempFileName();
							std::string	uploadPath = _findUploadPath();
							_creatFile(uploadPath + file, this->_body);
							//should check the uri and location
							//should generate a random file name and find the uploadPath
							//should create the file
						}
						else
							this->_errCode = 405; //Method Not Allowed
				}
			}
			else
				this->_errCode = 413; /*Content Too Large response status code indicates that
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
    //find contenu dial content-lenght
	std::map<std::string, std::string>::iterator iter = headerFields.find("Content-Length");
    if (iter != headerFields.end()) {
        contentLength = atoi(iter->second.c_str());
        return true; // true l9inaah
    }
	std::string transfer_encod("Transfer-Encoding");
	if (headerFields.find("Transfer-Encoding") != headerFields.end() \
		&& headerFields[transfer_encod].find("chunked") != std::string::npos) {
		this->isChunked = true;
		return true;
	}
	else if (headerFields.find("Transfer-Encoding") != headerFields.end() \
		&& headerFields[transfer_encod].find("chunked") == std::string::npos) {
		this->_errCode = 501; //Not implemented
		return false;
	}
	else if (this->_method == "post" && headerFields.find("Content-Length") == headerFields.end()
		&& headerFields.find("Transfer-Encoding") == headerFields.end()) {
		this->_errCode = 400; //Bad Request
		return false;
	}
	return false; /*ayaetina makaynch body but we should first check l function li qade loujdi 
	so we need to call it inside our parseBody function */
}
//29\r\nmoi nouhaila\r\nje suis etudiante\r\na l'um6p\r\n0\r\n\r\n

void	HttpRequest::_getChunkedBody(size_t &bodypos) {
	std::string	tmp = this->_request.substr(bodypos);
	// std::cout << "----BODY---    "<< tmp;
	// std::cout << "----Body fin---\n";
	size_t	bodySize = tmp.size();
	// printf("%lu\n", bodySize);

	for (size_t i = 0; i < bodySize; i++) {
		std::string	chunk = "";
		size_t	j = i;
		for (; tmp[j] != '\r'; j++) {
			chunk += tmp[j];
		}
		// std::cout << "the length in HExa: "<< chunk << "\n";
		i = j + 2;
		int	chunkedSize = hextoint(chunk);
		if (chunkedSize == 0)
			break ;
		// printf("i: %lu, chunkedSize: %d\n", i, chunkedSize);
		this->_body += tmp.substr(i, chunkedSize);
		// std::cout << "own body: " << "'" << this->_body << "'";
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
    return (std::find(_isAllowedMeth.begin(), _isAllowedMeth.end(), toUpper(this->_method)) != _isAllowedMeth.end());
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
		this->_errCode = 500; //500 Internal Server errCodeor
	else {
		file << reqBody;
		file.close();
		this->_errCode = 201; /*201 Created success status response code indicates
		that the request has succeeded and has led to the creation of a resource*/
	}
}

std::string	HttpRequest::_generateTempFileName(void) {
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
