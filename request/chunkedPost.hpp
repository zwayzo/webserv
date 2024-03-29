#ifndef CHUNKEDPOST_HPP
# define CHUNKEDPOST_HPP

#include "parseRequest.hpp"
#include<string>
#include "../multuplixing/multuplixing.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

void	_getChunkedBody(int fd, const char* buf, client *cl);

#endif
