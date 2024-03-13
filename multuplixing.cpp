#include "headers/multuplixing.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unistd.h>

void getMethodes(std::string buf, client *cl)
{
    if (std::strncmp(buf.c_str(), "POST", 4) == 0)
        cl->post = 1;
}

void clearSets(client *mycl, int i, int *s, int *index, fd_set *master_re, fd_set *master_wr)
{
    if (mycl->post == 1)
            mycl->fileD.close();
    FD_CLR(i, master_re);
    FD_SET(i, master_wr);
    *s = 0;
    *index = 0;
    mycl->post = 0;
}

std::string getExtention(char *buf)
{
    std::string tmp = buf;

    size_t pos = tmp.find("Content-Type:");
    int i = 0;
    pos += 14;
    // std::cout << tmp << '\n';
    while (tmp[pos] != '/')
        pos++;
    pos++;
    char *ret;
    // ret = static_cast<char *>(calloc(20, 1));
    ret = new (20);
    while (tmp[pos] != '\n')
    {
        ret[i] += tmp[pos];
        i++;
        pos++;
    }
    ret[i - 1] = '\0';
    std::cout << "extention is '" << ret << "'\n";
    return ret;
}

int getRequestLenght(char *buf)
{
    std::string tmp = buf;
    size_t pos = tmp.find("Content-Length: ");
    std::string t;
    pos += 16;
    std::cout << "tmp is " << tmp <<'\n';
    while (tmp[pos] != '\n'){
        t = t + tmp[pos];
        pos++;
    }
    printf("content-lenght:%d\n", std::atoi(t.c_str()));
    return (std::atoi(t.c_str()));
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
    cl->contentLenght =  getRequestLenght(buf);
    std::string tmp = "file";
    std::stringstream s;
    s << fd;
    tmp += s.str();
    tmp +=  s.str() + '.' +  getExtention(buf);
    cl->fileIndex = 1;
    cl->fileD.open(tmp.c_str(), std::ios::out | std::ios::trunc);
    if (cl->fileD.is_open())
        std::cout << tmp << " has been created\n";
    else 
        throw ("file can't be open\n");
    std::cout << "file name is " << tmp <<'\n';
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
        std::cout << ss[i].str().c_str()  << '\n';
        if ((conf->ser[i].socketAddr = getaddrinfo(conf->ser[i].name.c_str(),
            ss[i].str().c_str(),
            &hints[i], &result[i])) != 0)
            throw ("error in addr");
        std::cout << "getting the addr..."<< conf->ser[i].socketAddr << "\n";
        if (result[i] == NULL)
            throw ("error in result");
        if ((conf->ser[i].sock = socket(result[i]->ai_family,
                                result[i]->ai_socktype, result[i]->ai_protocol)) == -1){
            throw ("creating socket");
        }
        printf("socket for server %d is %d\n", i, conf->ser[i].sock);
        int b = bind(conf->ser[i].sock, result[i]->ai_addr, result[i]->ai_addrlen);
        if (b  == -1){
            close (conf->ser[i].sock);
            continue;
        }
        std::cout << "binding..." << b << "\n";
        freeaddrinfo(result[i]);
        if ((conf->ser[i].listen_fd = listen(conf->ser[i].sock, FD_SETSIZE)) == -1){
            close(conf->ser[i].sock);
            continue;
            // throw ("listen");
        }
        else
            std::cout << "listining..." << conf->ser[i].listen_fd <<"\n";
        int flags = fcntl(0, F_GETFL, 0);
        fcntl(conf->ser[i].sock, F_SETFL, flags | O_NONBLOCK);
    }
}

void multuplixing(conf* conf)
{
    std::vector <client> mycl;
    fd_set master_re, master_wr, read_fds, write_fds;    // master_re file descriptor list
    char buf[8000];    // buffer for client data
    int maxfd, index = 0, s = 0, newFd, in = 0;
    getSocket(conf);
    maxfd = maxFd(conf);
    FD_ZERO(&master_re);
    FD_ZERO(&master_wr);
    FD_ZERO(&write_fds);
    FD_ZERO(&read_fds); //clear the set
    signal(SIGTSTP, handleCtrlZ);
    for (int j = 0; j < conf->serversNumber; j++){
        std::cout << j << '\n';
        FD_SET(conf->ser[j].sock, &master_re);
    }
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
                    printf("new connection\n");
                    if ((newFd = accept(i, NULL, NULL)) == -1)
                        throw ("ERROR IN ACCEPTING\n");
                    printf("accept...\n");
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
                        printf("rcv read %d\n",nbytes);
                        // std::cout <<  mycl[in-1].post << '\n';
                        if (nbytes != 0)
                            getMethodes(buf, &mycl[in - 1]);
                        else if (nbytes == -1)
                            throw ("error in recv\n");
                        std::cout << "after getting what methode..." << mycl[in - 1].post << "\n";
                        if (mycl[in - 1].post == 1){
                            std::cout << "WARNING.............................POST\n";
                            int z = 0;
                            if (index == 0){
                                z = creatFile(i, buf, &mycl[in - 1]);
                                // std::cout << "this is what should be in " << mycl[in-1].file << "\n----------------------\n" << buf << "\n-------------------------\n";
                                // printf("header length is %d\n", z);
                                mycl[in - 1].fileD.write(&buf[z], nbytes - z);
                                s += nbytes - z;
                            }
                            else{
                                mycl[in - 1].fileD.write(buf, nbytes);
                                s += nbytes;
                            }
                            // printf("s is %d\n", s);
                            index++;
                        }   
                        if (nbytes > 0){
                            // throw ("error in recv");
                        std::cout << "1-------------------------------------\n" << buf <<"\n2----------------------------------\n";
                        std::cout << "s is " << s << " lenght is " << mycl[in-1].contentLenght << '\n';
                        if ( s >= mycl[in - 1].contentLenght){
                            printf("time to clear\n");
                            clearSets(&mycl[in - 1], i, &s, &index, &master_re, &master_wr);
                            printf("post is %d\n", mycl[in - 1].post);
                            // FD_SET(i, &write_fds);
                        }
                        //     if (mycl[in - 1]ug.post == 1)
                        //         mycl[in - 1].fileD.close();
                        // FD_CLR(i, &master_re);
                        // FD_SET(i, &master_wr);
                        // s = 0;
                        // index = 0;
                        }
                        //working on request workREquest(buf);
                    }
                    if(FD_ISSET(i, &write_fds)){
                        // exit(1);
                        printf("not new connection in write\n");
                        send(i, "slm", 4, 0);
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

