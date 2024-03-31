#include "request.hpp"

request::request() : fileIndex(0), post(0){
};

request::request (const request &copy)
{
    // std::cout << "------- 1111111 in copy constructor\n";
    this->fd = copy.fd;
    this->index = copy.index;
    this->post = copy.post;
    this->contentLenght = copy.contentLenght;
    this->track = copy.track;
    this->fd = copy.fd;
    this->first = copy.first;
};

request& request::operator=(const request &copy)
{
    // std::cout << "--------- 22222222 in copy assignement operator\n";
    this->fd = copy.fd;
    this->index = copy.index;
    this->post = copy.post;
    this->contentLenght = copy.contentLenght;
    this->track = copy.track;
    this->fd = copy.fd;
    return *this;
}