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


std::string getExtention(char *buf)
{
    std::string tmp = buf;
    size_t pos = tmp.find("Content-Type:");
    pos += 14;
    printf("||||||||||||||||||||||||||||||||||||\n");
    std::cout << tmp << '\n';
    while (tmp[pos] != '/')
        pos++;
    pos++;
    std::string ret;
    while (tmp[pos] != '\n')
    {
        ret += tmp[pos];
        pos++;
    }
    std::cout << "extention is " << ret << '\n';
    // exit(1);
    return ret;
}

int getRequestLenght(char *buf)
{
    std::string tmp = buf;
    // std::cout << tmp;
    // exit(2);
    size_t pos = tmp.find("Content-Length: ");
    std::string t;
    pos += 16;
    while (tmp[pos] != '\n'){
        t = t + tmp[pos];
        pos++;
    }
    printf("=======>%d\n", std::atoi(t.c_str()));
    // exit(0);
    return (std::atoi(t.c_str()));
}

void creatFile(int fd, char *buf, client *cl)
{
    cl->contentLenght =  getRequestLenght(buf);
    std::string tmp = "file";
    std::stringstream s;
    s << fd;
    printf("fd is %d--->%s\n", fd, s.str().c_str());
    tmp += s.str();
    // std::stringstream ss;
    // ss << cl->index;
    tmp +=  s.str() + '.' +  getExtention(buf);
    // std::cout << "file name is " << tmp << '\n';
    cl->fileIndex = 1;
    // std::ofstream file;
    cl->fileD.open(tmp.c_str(), std::ios::out | std::ios::app);
    if (cl->fileD.is_open())
        std::cout << tmp << " has been created\n";
    else 
        exit(1);
    std::cout << "file name is " << tmp <<'\n';
    cl->file = tmp;
    // exit(1);
    // exit(1);

    // cl->fileD = file;
}


int validSocket(int j, conf *conf)
{
    for (std::vector<int>::iterator it = conf->vec.begin(); it != conf->vec.end(); it++)
    {
        if (*it == j){
            printf("{}{}}}}}}}}}}}}}}}}}}}}\n");
            return 1;
        }
    }
    return 0;
}

int maxFd(conf* conf)
{
    int tmp = 0;
    printf("getting max...\n");
    printf("num:%d\n", conf->serversNumber);
    for (int i = 0;i < conf->serversNumber; i++)
    {
        if (conf->ser[i].sock> tmp)
            tmp = conf->ser[i].sock;
    }
    // std::cout << "tmp is:"<< tmp << std::endl;
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
    std::cout <<"{}"<< conf->serversNumber<< '\n';
    // exit(1);
    // for (int i = 0; i < conf->serversNumber; i++)
    //     std::cout << "port:" << conf->ser[i].listen << " name:"<< conf->ser[i].name << '\n';
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
        // std::cout << "before\n";
        std::cout << ss[i].str().c_str()  << '\n';
        //  std::cout << "after\n";
        if ((conf->ser[i].socketAddr = getaddrinfo(conf->ser[i].name.c_str(),
            ss[i].str().c_str(),
            &hints[i], &result[i])) != 0){
                std::cout <<  "errno set to " <<  strerror(errno) << '\n';
            throw ("error in addr");
            }
        std::cout << "getting the addr..."<< conf->ser[i].socketAddr << "\n";
        if (result[i] == NULL)
            throw ("error in result");
        if ((conf->ser[i].sock = socket(result[i]->ai_family,
                                result[i]->ai_socktype, result[i]->ai_protocol)) == -1){
            // freeaddrinfo(result[i]);
            throw ("creating socket");
        }
        printf("socket for server %d is %d\n", i, conf->ser[i].sock);
        // printf("socket has been created...%d\n",conf->ser[i].sock );
        int b = bind(conf->ser[i].sock, result[i]->ai_addr, result[i]->ai_addrlen);
        if (b  == -1){
            close (conf->ser[i].sock);
            continue;
            // throw ("error in binding");
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
        // exit(1);
}

void multuplixing(conf* conf)
{
    std::vector <client> mycl;
    fd_set master_re;    // master_re file descriptor list
    fd_set master_wr;
    fd_set read_fds;  // temp file descriptor list for select()
    fd_set write_fds;
    char buf[8000];    // buffer for client data
    int newFd;
    int s = 0;

    // exit(1);
    // std::vector <client> cl;
    getSocket(conf);
    int maxfd = maxFd(conf);
    int index = 0;
    // printf("--------------------------\n");
    printf("max is %d\n", maxfd);
    FD_ZERO(&master_re);
    FD_ZERO(&master_wr);
    FD_ZERO(&write_fds);
    FD_ZERO(&read_fds); //clear the set
    int in = 0;
    // conf->vec.
    // client tmp
    signal(SIGTSTP, handleCtrlZ);
    for (int j = 0; j < conf->serversNumber; j++){
        std::cout << j << '\n';
        FD_SET(conf->ser[j].sock, &master_re);
    }
    for (;;)
    {
        read_fds =  master_re;
        write_fds =  master_wr;
        // printf("before select...\n");
        if (select(maxfd + 1, &read_fds, &write_fds, NULL, NULL) == -1)
            throw ("ERROR IN SELECT");
        printf("select...\n");
        for (int i = 0; i <= maxfd; i++){
            // printf("i is %d\n", i);
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
                    // cl.mycl.push_back(tmp);
                    conf->vec.push_back(newFd);
                    FD_SET(newFd, &master_re);
                    if (newFd > maxfd)
                        maxfd = newFd;
                }
                else
                {
                    // printf("not new connection\n");
                    if (FD_ISSET(i, &read_fds)){
                        // printf("not new connection in read\n");
                        // printf("recv try to connect with %d\n", i);
                        int nbytes = recv(i, buf, sizeof(buf), 0);
                        printf("rcv read %d\n",nbytes);
                        // std::cout << "after recv...\n";
                        std::cout << buf << '\n' ;
                        std::cout <<  mycl[in-1].post << '\n';
                        // exit(1);
                        getMethodes(buf, &mycl[in - 1]);
                        std::cout << "after getting what methode..." << mycl[in - 1].post << "\n";
                        if (mycl[in - 1].post == 1){
                            std::cout << "WARNING.............................POST\n";
                            if (index == 0){
                                creatFile(i, buf, &mycl[in - 1]);
                                std::cout << "this is what should be in " << mycl[in-1].file << "\n----------------------\n" << buf << "\n-------------------------\n";
                            }
                            index++;
                            mycl[in - 1].fileD.write(buf, sizeof(buf));
                            s += nbytes;
                            printf("s is %d\n", s);
                            // exit(1);
                        }
                        // int tmp = getRequestLenght(buf);
                        // int s = nbytes;

                        // printf("s is %d\n", s);
                       // s += recv(i, buf, sizeof(buf), 0);
                            
                        if (nbytes == -1)
                            throw ("error in recv");
                        std::cout << "1-------------------------------------\n" << buf <<"\n2----------------------------------\n";
                        std::cout << "s is " << s << " lenght is " << mycl[in-1].contentLenght << '\n';
                        if ( s >= mycl[in - 1].contentLenght){
                            printf("time to clear\n");
                            if (mycl[in - 1].post == 1)
                                mycl[in - 1].fileD.close();
                        FD_CLR(i, &master_re);
                        FD_SET(i, &master_wr);
                        s = 0;
                        index = 0;
                        }
                        //working on request workREquest(buf);
                    }
                    if(FD_ISSET(i, &write_fds)){
                        printf("not new connection in write\n");
                        send(i, "9wd", 4, 0);
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

