#include "headers/multuplixing.hpp"
#include <iostream>
#include <string>
#include <sstream>

int validSocket(int j, conf *conf)
{
    for (int i =0;i  < conf->serversNumber; i++)
    {
        if (j == conf->ser[i].sock)
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
    std::cout << "tmp is:"<< tmp << std::endl;
    return tmp;

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
        printf("socket has been created...%d\n",conf->ser[i].sock );
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
        // int flags = fcntl(0, F_GETFL, 0);
        // fcntl(conf->ser[i].sock, F_SETFL, flags | O_NONBLOCK);
    }
        // exit(1);
}

void multuplixing(conf* conf)
{
    
    // std::cout << conf->ser[0].listen << '\n';
    // exit(1);

    // int serverSocket[conf->serversNumber];
    // struct addrinfo hints[conf->serversNumber];
    // // struct addrinfo *result[conf->serversNumber];
    // struct sockaddr_storage their_addr[conf->serversNumber]; //wher the infos about upcoming connections will go
    // int listen_fd[conf->serversNumber];
    int newFd;
    socklen_t addrlen;
    // socklen_t addr_size;
    struct sockaddr_storage remoteaddr; // client address
    // struct timeval tv;
    fd_set master_re;    // master_re file descriptor list
    fd_set master_wr;
    fd_set read_fds;  // temp file descriptor list for select()
    fd_set write_fds;
    int nbytes;
    char buf[1024];    // buffer for client data
    // buf = (char *)std::calloc(1024, 1);
    // std::cout << conf->serversNumber;
    // exit(1);
    for (int i = 0; i < conf->serversNumber; i++)
    {
        // memset(&hints[i], 0, sizeof(struct addrinfo));
        // hints[i].ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
        // hints[i].ai_socktype = SOCK_STREAM; // Stream socket (TCP)
        // hints[i].ai_flags = AI_PASSIVE;     // fill in my IP for me
        // std::stringstream ss;
        // ss << conf->ser[i].listen;
        // std::cout << "listen on:" << ss.str().c_str() << '\n';
        // if ((conf->ser[i].socketAddr = getaddrinfo(conf->ser[i].name.c_str(),
        //                         ss.str().c_str(),
        //                         &hints[i], &result[i])) != 0)
        //                         throw ("error in addr");

        // else 
        //     std::cout << "getting the addr...\n";
        
        // std::cout << conf->ser[i].listen;
        // if (result[i] == NULL)
        //     throw ("error in result result");
        // if ((serverSocket[i] = socket(result[i]->ai_family,
        //                         result[i]->ai_socktype, result[i]->ai_protocol)) == -1){
        //     perror("socket");
        //     freeaddrinfo(result[i]);
        //     throw ("creating socket");
        // }
        // conf->ser[i].sock = serverSocket[i];
        // if (bind(serverSocket[i], result[i]->ai_addr, result[i]->ai_addrlen) == -1){
        //     close (serverSocket[i]);
        //     throw ("error in binding");
        // }
        // else 
        //     std::cout << "binding...\n";
        // freeaddrinfo(result[i]);
        // if ((listen_fd[i] = listen(serverSocket[i], FD_SETSIZE)) == -1)
        //     throw ("listen");
        // else
        //     std::cout << "listining...\n";

        // fcntl(serverSocket[i], F_SETFL, O_NONBLOCK); //instead of waiting for the data to be avilabale of for write to finish it program execution. Instead of waiting for data to be available or for a write operation to complete, non-blocking sockets allow you to check if the operation can be performed immediately without waiting.
        // int flags = fcntl(0, F_GETFL, 0);
        // fcntl(serverSocket[i], F_SETFL, flags | O_NONBLOCK);

        getSocket(conf);
        printf("->%d\n", conf->ser[i].sock);
        // exit(1);
        FD_ZERO(&master_re);
        FD_ZERO(&master_wr);
        FD_ZERO(&write_fds);
        FD_ZERO(&read_fds); //clear the set
        for (int i = 0 ;i < conf->serversNumber; i++){
            // printf("____>%d\n", conf->ser[i].sock);
            FD_SET(conf->ser[i].sock, &master_re);
            FD_SET(conf->ser[i].sock, &master_wr);
        }
        int maxfd = maxFd(conf);
        printf("max is %d", maxfd);
        signal(SIGTSTP, handleCtrlZ);
        for (;;){
            printf("max is %d\n", maxfd);
            read_fds = master_re;
            write_fds = master_wr;
            if (select(maxfd+1, &read_fds, NULL, NULL, NULL) == -1){
                printf("%d\n", (maxfd+1));
                 throw("select error\n");
            }
            // printf("out\n");
            for (int j = 0;j <= maxfd; j++){
                // std::cout << "j  is:" << j <<'\n';
                if (FD_ISSET(j, &read_fds)) // if the fd is in the set
                {
                    std::cout << "1\n";
                    printf("j is %d socket %d\n", j, conf->ser[i].sock);
                    if (validSocket(j, conf)) //the fd is in the set handel new connection
                    {// handel new connections
                        std::cout << "11\n";
                        addrlen = sizeof(remoteaddr);
                        newFd = accept(conf->ser[i].sock, NULL, NULL);
                        if (newFd == -1)
                            throw ("ERROR IN ACCEPT FUNCTION...\n");
                        FD_SET(newFd, &master_re); //now we have fd that have the request and fd who still waiting
                        if (newFd > maxfd)
                            maxfd = newFd + 1;
                    }
                    else{
                        std::cout << "22\n";
                        std::cout << "j is:" << j << " buf is:" << buf << " size is:"<<sizeof(buf)<< '\n';
                        if ((nbytes = recv(j, buf, sizeof(buf), 0)) <= 0)
                        {
                            printf("2.1-->%d-->%d\n",j,nbytes);
                            // close (j);
                            // FD_CLR(j, &master_re);
                            if (nbytes == 0)
                                printf("selectserver: socket %d port %d hung up\n", conf->ser[i].sock, conf->ser[i].listen);
                            else{
                                // std::cout << "isset:" << FD_ISSET(j, &master_re)<< '\n';
                                throw ("ERROR IN (RECV)\n");
                            }
                            close (j);
                            FD_CLR(j, &master_re);
                            FD_CLR(j, &master_wr);
                            FD_CLR(j, &read_fds);
                            FD_CLR(j, &write_fds);
                        }
                        else{
                            printf("2.2\n");
                            std::cout <<"nbytes:" << nbytes << '\n';
                            std::cout <<"client:" << j << '\n';
                            std::cout << "Received from client " << j << ": " <<  std::endl;
                            buf[nbytes] = '\0';
                            std::cout << "\n-------------------------------------------------\n";
                            // for (int i = 0; i < nbytes; ++i) 
                            std::cout << buf;
                            // exit(1);
                            // 
                            std::cout << "\n-------------------------------------------------\n";
                            // for (int x = 0; x < maxfd; x++){
                            //     printf("1\n");
                            //     if (FD_ISSET(x, &master_re)){
                            //         printf("2\n");
                            //         if (x != conf->ser[i].sock && x != j){
                            //             printf("3\n");
                            //             printf("bytes:%d\n", nbytes);
                            //             int tmp = send(x, buf, nbytes, 0);
                            //             printf("4\n");
                            //             printf("send return:%d", tmp);
                            //             if (tmp == -1)
                            //                 throw ("ERROR IN SENDING...\n");
                            //             else 
                            //                 printf("4\n");
                            //         }
                            //         printf("6\n");
                            //     }
                            //     printf("7\n");
                            // }
                        }
                        std::cout << "out\n";
                    }
                }//handel data from client
            }//got new upcoming connections
        }//looping through fd's
    }//while 1
}

                        
        // if (FD_ISSET(serverSocket[i], &read_fds))
        //     printf("A key was pressed!\n");
        // else
        //     printf("Timed out.\n");

        // addr_size = sizeof their_addr[i];
        // newFd = accept(serverSocket[i], (struct sockaddr *)&their_addr[i], &addr_size); // will creat a new fd that is ready to sent and receiv and for the socket one it's been listining
        
        
        
        // while (1);

        // std::cout << serverSocket[i] << " addr:" << conf->ser[i].socketAddr << '\n';
    // for (int i = 0;i < conf->serversNumber; i++)
        // freeaddrinfo(result[i]);

// struct addrinfo hints, *result;
//     memset(&hints, 0, sizeof(struct addrinfo));
//     hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
//     hints.ai_socktype = SOCK_STREAM; // Stream socket (TCP)



