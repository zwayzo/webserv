#include "headers/multuplixing.hpp"
#include <iostream>
#include <string>
#include <sstream>


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

void multuplixing(conf* conf)
{
    
    
    // exit(1);

    int serverSocket[conf->serversNumber];
    struct addrinfo hints[conf->serversNumber];
    struct addrinfo *result[conf->serversNumber];
    // struct sockaddr_storage their_addr[conf->serversNumber]; //wher the infos about upcoming connections will go
    int listen_fd[conf->serversNumber];
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
    // std::cout << conf->serversNumber;
    // exit(1);
    for (int i = 0; i < conf->serversNumber; i++)
    {
        memset(&hints[i], 0, sizeof(struct addrinfo));
        hints[i].ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
        hints[i].ai_socktype = SOCK_STREAM; // Stream socket (TCP)
        hints[i].ai_flags = AI_PASSIVE;     // fill in my IP for me
        std::stringstream ss;
        ss << conf->ser[i].listen;
        if ((conf->ser[i].socketAddr = getaddrinfo(conf->ser[i].name.c_str(),
                                ss.str().c_str(),
                                &hints[i], &result[i])) != 0)
                                throw ("error in addr");

        else 
            std::cout << "getting the addr...\n";
        
        // std::cout << conf->ser[i].listen;
        if (result[i] == NULL)
            throw ("error in result result");
        if ((serverSocket[i] = socket(result[i]->ai_family,
                                result[i]->ai_socktype, result[i]->ai_protocol)) == -1){
            perror("socket");
            freeaddrinfo(result[i]);
            throw ("creating socket");
        }
        conf->ser[i].sock = serverSocket[i];
        if (bind(serverSocket[i], result[i]->ai_addr, result[i]->ai_addrlen) == -1){
            close (serverSocket[i]);
            throw ("error in binding");
        }
        else 
            std::cout << "binding...\n";
        freeaddrinfo(result[i]);
        if ((listen_fd[i] = listen(serverSocket[i], FD_SETSIZE)) == -1)
            throw ("listen");
        else
            std::cout << "listining...\n";

        // fcntl(serverSocket[i], F_SETFL, O_NONBLOCK); //instead of waiting for the data to be avilabale of for write to finish it program execution. Instead of waiting for data to be available or for a write operation to complete, non-blocking sockets allow you to check if the operation can be performed immediately without waiting.
        int flags = fcntl(0, F_GETFL, 0);
        fcntl(serverSocket[i], F_SETFL, flags | O_NONBLOCK);
        FD_ZERO(&master_re);
        FD_ZERO(&master_wr);
        FD_ZERO(&write_fds);
        FD_ZERO(&read_fds); //clear the set
        FD_SET(serverSocket[i], &master_re);
        FD_SET(serverSocket[i], &master_wr);
        // std::cout << "her\n";
        // std::cout << accept(serverSocket[i], (struct sockaddr *)&remoteaddr, &addrlen)<<'\n';
        // std::cout << "her2\n";
        // std::cout << "errno:" << errno;
        // exit(1);
        int maxfd = maxFd(conf);
        signal(SIGTSTP, handleCtrlZ);
        for (;;){
            read_fds = master_re;
            write_fds = master_wr;
            if (select(maxfd+1, &read_fds, NULL, NULL, NULL) == -1)
                 throw ("ERROR IN SELECT...!\n");
            // printf("out\n");
            for (int j = 0;j <= maxfd; j++){
                // std::cout << "j  is:" << j <<'\n';
                if (FD_ISSET(j, &read_fds)) // if the fd is in the set
                {
                    // std::cout << "her\n";
                    if (j == serverSocket[i]) //the fd is in the set handel new connection
                    {// handel new connections
                        std::cout << "11\n";
                        addrlen = sizeof(remoteaddr);
                        newFd = accept(serverSocket[i], (struct sockaddr *)&remoteaddr, &addrlen);
                        if (newFd == -1)
                            throw ("ERROR IN ACCEPT FUNCTION...\n");
                        FD_SET(newFd, &master_re); //now we have fd that have the request and fd who still waiting
                        if (newFd > maxfd)
                            maxfd = newFd;
                    }
                    else{
                        // std::cout << "22\n";
                        if ((nbytes = recv(j, buf, sizeof(buf), 0)) <= 0)
                        {
                            printf("2.1\n");
                            // close (j);
                            FD_CLR(j, &master_re);
                            if (nbytes == 0)
                                throw ("SOCKT IS HANGING...(RECV)\n");
                            else
                                throw ("ERROR IN (RECV)\n");
                        }
                        else{
                            printf("2.2\n");
                            // std::cout <<"nbytes:" << nbytes << '\n';
                            // std::cout <<"client:" << j << '\n';
                            std::cout << "\n-------------------------------------------------\n";
                            for (int i = 0; i < nbytes; ++i) 
                                std::cout << (char)buf[i];
                            std::cout << "\n-------------------------------------------------\n";
                            // exit(1);
                            // buf[nbytes] = '\0';
                            // std::cout << "Received from client " << j << ": " << buf << std::endl;
                            for (int x = 0; x < maxfd; x++){
                                if (FD_ISSET(x, &master_re)){
                                    if (x != serverSocket[i] && x != j){
                                        if (send(x, buf, nbytes, 0) == -1)
                                            throw ("ERROR IN SENDING...\n");
                                    }
                                }
                            }
                        }
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



