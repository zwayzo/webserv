#ifndef MULTUPLIXING_HPP
#define MULTUPLIXING_HPP

#include "configFile.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netdb.h>
#include <cstdlib>
#include <string>
#include <csignal>
#include <signal.h>
#include <unistd.h>


void multuplixing (conf *conf);

#endif