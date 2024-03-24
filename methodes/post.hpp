#ifndef POST_HPP
#define POST_HPP

#include "../headers/header.hpp"

class client;

int randomNum(); //get rendom number to add it in file[number].extention (post method)
void getMethodes(std::string buf, client *cl);
int creatFile(int fd, char *buf, client *cl); //creat the file (file+'random number' +.'extention)
void getRequestLenght(char *buf, client *cl); //get the request lenght of post so to know how many time i nead to read(post)
std::string getExtention(char *buf); //get the extention of what i receive (post)
int getBody(char *buf);//get the only the body to put it in file to get the (image video or whatever the client want to post) (post method)
std::map<int, client>::iterator post(std::map<int, client>::iterator iter, int i, int nbytes);


#endif