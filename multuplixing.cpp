#include "headers/multuplixing.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <unistd.h>
#include <ctime>
#include <cstring>
#include <cstdlib>


int randomNum()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Generate a random number between 1 and 1000
    return ((std::rand() % 1000) + 1);
    
}

void getMethodes(std::string buf, client *cl)
{
    cl->method = 1;
    
    // printf("%d\n", buf[0]);
    // if (buf[0])
        // exit(1);
    // printf("\n\n\n\n\n%c\n", buf[0]);
    if (std::strncmp(buf.c_str(), "POST", 4) == 0)
        cl->post = 1;
}

void clearSets(client *mycl, int i, long long *s, int *index, fd_set *master_re, fd_set *master_wr)
{
    if (mycl->post == 1)
            mycl->fileD.close();
    FD_CLR(i, master_re);
    FD_SET(i, master_wr);
    *s = 0;
    *index = 0;
    mycl->post = 0;
    mycl->method = 0;
}

std::string getExtention(char *buf)
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
    for (; tmp[j] != '\n'; j++)
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

void getRequestLenght(char *buf, client *cl)
{
    std::string tmp = buf;
    size_t pos = tmp.find("Content-Length: ");
    std::string t;
    pos += 16;
    // std::cout << "tmp is " << tmp <<'\n';
    while (tmp[pos] != '\n'){
        t = t + tmp[pos];
        pos++;
    }
    // printf("{%lu}\n", std::strlen(t.c_str()));
    printf("content-lenght:%s\n%lld\n", t.c_str(),strtoll(t.c_str(), NULL, std::strlen(t.c_str()) - 1));
    // exit(1);
    cl->contentLenght = strtoll(t.c_str(), NULL, std::strlen(t.c_str()));
    // return (strtoll(t.c_str(), NULL, std::strlen(t.c_str()) - 1));
}

int getBody(char *buf)
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

int creatFile(int fd, char *buf, client *cl)
{
    (void)fd;
    // cl->contentLenght =  getRequestLenght(buf);
    getRequestLenght(buf, cl);
    printf("in cre:%lld\n",  cl->contentLenght);
    std::string tmp = "file";
    std::stringstream s;
    s << randomNum();
    tmp += s.str();
    tmp +=  s.str() + '.' +  getExtention(buf);
    cl->fileIndex = 1;
    cl->fileD.open(tmp.c_str(), std::ios::out);
    if (cl->fileD.is_open())
        std::cout << tmp << " has been created\n";
    else 
        throw ("file can't be open\n");
    // std::cout << "file name is " << tmp <<'\n';
    cl->file = tmp;
    return (getBody(buf));
}


int validSocket(int j, conf *conf)
{
    for (std::vector<int>::iterator it = conf->vec.begin(); it != conf->vec.end(); it++)
    {
        if (*it == j)
            return 1;
    }
    return 0;
}

int maxFd(conf* conf)
{
    int tmp = 0;
    for (int i = 0;i < conf->serversNumber; i++)
    {
        if (conf->ser[i].sock> tmp)
            tmp = conf->ser[i].sock;
    }
    return tmp;

}

void addSocket(conf *conf)
{
    for (int i = 0; i < conf->serversNumber; i++)
        conf->vec.push_back(conf->ser[i].sock);
}
void handleCtrlZ(int signum) {
    (void )signum;
    // std::cout << "Ctrl+Z signal received (SIGTSTP)." << std::endl;

    // Raise the SIGINT signal to terminate the program
    std::raise(SIGINT);
}

void getSocket(conf* conf)
{
        // exit(1);
    struct addrinfo hints[conf->serversNumber];
    struct addrinfo *result[conf->serversNumber];
    std::stringstream ss[conf->serversNumber];

    for (int i = 0; i < conf->serversNumber; i++)
    {
        memset(&hints[i], 0, sizeof(struct addrinfo));
        hints[i].ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
        hints[i].ai_socktype = SOCK_STREAM; // Stream socket (TCP)
        hints[i].ai_flags = AI_PASSIVE;     // fill in my IP for me

        ss[i] << conf->ser[i].listen;
        if ((conf->ser[i].socketAddr = getaddrinfo(conf->ser[i].name.c_str(),
            ss[i].str().c_str(),
            &hints[i], &result[i])) != 0)
            throw ("error in addr");
        // std::cout << "getting the addr..."<< conf->ser[i].socketAddr << "\n";
        if (result[i] == NULL)
            throw ("error in result");
        if ((conf->ser[i].sock = socket(result[i]->ai_family,
                                result[i]->ai_socktype, result[i]->ai_protocol)) == -1){
            throw ("creating socket");
        }
        // printf("socket for server %d is %d\n", i, conf->ser[i].sock);
        int b = bind(conf->ser[i].sock, result[i]->ai_addr, result[i]->ai_addrlen);
        if (b  == -1){
            close (conf->ser[i].sock);
            continue;
        }
        // std::cout << "binding..." << b << "\n";
        freeaddrinfo(result[i]);
        if ((conf->ser[i].listen_fd = listen(conf->ser[i].sock, FD_SETSIZE)) == -1){
            close(conf->ser[i].sock);
            continue;
            // throw ("listen");
        }
        // else
        //     std::cout << "listining..." << conf->ser[i].listen_fd <<"\n";
        int flags = fcntl(0, F_GETFL, 0);
        fcntl(conf->ser[i].sock, F_SETFL, flags | O_NONBLOCK);
    }
}

void multuplixing(conf* conf)
{
    // exit(1);
    std::vector <client> mycl;
    fd_set master_re, master_wr, read_fds, write_fds;    // master_re file descriptor list
    char buf[8000];    // buffer for client data
    int maxfd, index = 0, newFd, in = 0;
    long long s = 0;
    getSocket(conf);
    maxfd = maxFd(conf);

    FD_ZERO(&master_re);
    FD_ZERO(&master_wr);
    FD_ZERO(&write_fds);
    FD_ZERO(&read_fds); //clear the set
    signal(SIGTSTP, handleCtrlZ);
    for (int j = 0; j < conf->serversNumber; j++)
        FD_SET(conf->ser[j].sock, &master_re);
    for (;;)
    {
        read_fds =  master_re;
        write_fds =  master_wr;
        printf("waiting...\n");
        if (select(maxfd + 1, &read_fds, &write_fds, NULL, NULL) == -1)
            throw ("ERROR IN SELECT");
        for (int i = 0; i <= maxfd; i++){
            if(FD_ISSET(i, &read_fds) || FD_ISSET(i, &write_fds))
            {
                if (!validSocket(i, conf))
                {
                    // printf("new connection\n");
                    if ((newFd = accept(i, NULL, NULL)) == -1)
                        throw ("ERROR IN ACCEPTING\n");
                    // printf("accept...\n");
                    client tmp(newFd);
                    tmp.index = in;
                    in++;
                    mycl.push_back(tmp);
                    conf->vec.push_back(newFd);
                    FD_SET(newFd, &master_re);
                    if (newFd > maxfd)
                        maxfd = newFd;
                }
                else
                {
                    if (FD_ISSET(i, &read_fds)){
                        int nbytes = recv(i, buf, sizeof(buf), 0);
                        // printf("rcv read %d\n",nbytes);
                        // std::cout <<  mycl[in-1].post << '\n';
                        // printf("getting methodes %d\n", mycl[in -1].method);
                        if (nbytes != 0 && mycl[in -1].method <= 0)
                            getMethodes(buf, &mycl[in - 1]);
                        else if (nbytes == -1)
                            throw ("error in recv\n");
                        // std::cout << "after getting what methode..." << mycl[in - 1].post << "\n";
                        if (mycl[in - 1].post == 1){
                            std::cout << "WARNING.............................POST\n";
                            int z = 0;
                            if (index == 0){
                                z = creatFile(i, buf, &mycl[in - 1]);
                                mycl[in - 1].fileD.write(&buf[z], nbytes - z);
                                s += nbytes - z;
                            }
                            else{
                                mycl[in - 1].fileD.write(buf, nbytes);
                                s += nbytes;
                            }
                            index++;
                        }   
                        if (nbytes > 0){
                            // throw ("error in recv");
                        
                        std::cout << "1-------------------------------------\n" << buf <<"\n2----------------------------------\n";
                        std::cout << "s is " << s << " lenght is " << mycl[in-1].contentLenght << '\n';
                        if ( s >= mycl[in - 1].contentLenght){
                            printf("time to clear\n");
                            clearSets(&mycl[in - 1], i, &s, &index, &master_re, &master_wr);
                            }
                        }
                        //working on request workRequest(buf);
                    }
                    if(FD_ISSET(i, &write_fds)){
                        // exit(1);
                        // printf("not new connection in write\n");
                        send(i, "slma", 5, 0);
                        //send response
                        FD_CLR(i, &master_wr);
                        close (i);
                        conf->vec.erase(std::remove(conf->vec.begin(), conf->vec.end(), i));
                    }
                }
            }
        }
    }
}



//51154

