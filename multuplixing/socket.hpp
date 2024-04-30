#ifndef SOCKET_HPP
#define SOCKET_HPP

#include<string>

#include "../headers/header.hpp"

class conf;
class client;
void clearSets(client *mycl, int i, long long *s, int *index, fd_set *master_re, fd_set *master_wr); //clear the sets and initialze some variables(select)
int validSocket(int j, conf *conf); //check if the j is a socket (need to be socket if want to work with methodes)
void addSocket(conf *conf);
void getSocket(conf* conf);

#endif