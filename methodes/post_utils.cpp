#include "../multuplixing/multuplixing.hpp"
#include "post.hpp"

int creatFile(int fd, char *buf, client *cl) //creat the file (file+'random number' +.'extention)
{
    (void)fd;
    getRequestLenght(buf, cl);
    // printf("in cre:%lld\n",  cl->req.contentLenght);
    std::string tmp = "file";
    std::stringstream s;
    s << randomNum();
    tmp += s.str();
    tmp = cl->upload + '/' + tmp + '.' +  getExtention(buf);

    cl->req.fileIndex = 1;
    cl->req.fileD.open(tmp.c_str(), std::ios::out);
    if (cl->req.fileD.is_open())
        std::cout << tmp << " has been created\n";
    else{
        std::cout << cl->upload; 
        throw (" no such directory\n");
    }
    // std::cout << "file name is " << tmp <<'\n';
    cl->req.file = tmp;
    return (getBody(buf));
}


std::string getExtention(char *buf) //get the extention of what i receive (post)
{
    std::string tmp = buf;
    size_t pos = tmp.find("Content-Type:");
    int i = 0;
    pos += 14;
    while (tmp[pos] != '/')
        pos++;
    pos++;
    char *ret;
    int j = pos;
    for (; tmp[j] && tmp[j] != '\n'; j++)
        j++;
    ret = new char[j - pos];
    while (tmp[pos] != '\n')
    {
        ret[i] = tmp[pos];
        i++;
        pos++;
    }
    ret[i - 1] = '\0';
    // std::cout << "extention is '" << ret << "'\n";
    return ret;
}

int getBody(char *buf) //get the only the body to put it in file to get the (image video or whatever the client want to post) (post method)
{
    int i = 0;
    for (i = 0; buf[i] != '\r' && buf[i + 1] != '\n' && buf[i + 2] != '\r' && buf[i + 3] != '\n'; i++);
    while (buf[i])
    {
        if (buf[i] == '\r' && buf[i + 1] == '\n' && buf[i + 2] == '\r' && buf[i + 3] == '\n')
            return (i+4);
        i++;
    }
    return 0;

}