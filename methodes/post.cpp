#include "../multuplixing/multuplixing.hpp"
#include "post.hpp"

int randomNum() //get rendom number to add it in file[number].extention (post method)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Generate a random number between 1 and 1000
    return ((std::rand() % 1000) + 1);
    
}

void getMethodes(std::string buf, client *cl) //check if the method is post to work with
{
    cl->req.method = 1;
    if (std::strncmp(buf.c_str(), "POST", 4) == 0)
        cl->req.post = 1;
}

void getRequestLenght(char *buf, client *cl) //get the request lenght of post so to know how many time i nead to read(post)
{
    std::string tmp = buf;
    size_t pos = tmp.find("Content-Length: ");
    std::string t;
    pos += 16;
    while (tmp[pos] != '\n'){
        t = t + tmp[pos];
        pos++;
    }
    if (std::atoi(t.c_str()) < 0)
        cl->req.contentLenght = strtoll(t.c_str(), NULL, std::strlen(t.c_str()));
    else
        cl->req.contentLenght = std::atoi(t.c_str());
    // std::cout << "contentLenght: ----------------| " << cl->req.contentLenght << " |\n";
}

int creatFile(int fd, char *buf, client *cl) //creat the file (file+'random number' +.'extention)
{
    (void)fd;
    getRequestLenght(buf, cl);
    printf("in cre:%lld\n",  cl->req.contentLenght);
    std::string tmp = "file";
    std::stringstream s;
    s << randomNum();
    tmp += s.str();
    tmp +=  s.str() + '.' +  getExtention(buf);
    cl->req.fileIndex = 1;
    cl->req.fileD.open(tmp.c_str(), std::ios::out);
    if (cl->req.fileD.is_open())
        std::cout << tmp << " has been created\n";
    else 
        throw ("file can't be open\n");
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