#ifndef CHUNKEDPOST_HPP
# define CHUNKEDPOST_HPP

#include "../multuplixing/multuplixing.hpp"
#include "parseRequest.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
class client;

void	_getChunkedBody(int fd, const char* buf, client *cl);

#endif
