#include "headers/multuplixing.hpp"

void multuplixing(conf* conf)
{
    // exit(1);

    int serverSocket[conf->serversNumber];
    struct addrinfo hints[conf->serversNumber];
    struct addrinfo *result[conf->serversNumber];
    // struct sockaddr_storage their_addr[conf->serversNumber]; //wher the infos about upcoming connections will go
    int listen_fd[conf->serversNumber];
    // int newFd;
    // socklen_t addr_size;
    struct timeval tv;
    fd_set readfds;

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
                                throw ("addr");

        else 
            std::cout << "getting the addr...\n";
        
        // std::cout << conf->ser[i].listen;
        if (result[i] == NULL)
            throw ("result");
        if ((serverSocket[i] = socket(result[i]->ai_family,
                                result[i]->ai_socktype, result[i]->ai_protocol)) == -1){
            perror("socket");
            freeaddrinfo(result[i]);
            throw ("creating socket");
        }
        if (bind(serverSocket[i], result[i]->ai_addr, result[i]->ai_addrlen) == -1)
            throw ("bind");
        else 
            std::cout << "binding...\n";
        freeaddrinfo(result[i]);
        // connect(serverSocket[i], result[i]->ai_addr, result[i]->ai_addrlen);
        if ((listen_fd[i] = listen(serverSocket[i], 2)) == -1)
            throw ("listen");
        else
            std::cout << "listining...\n";

        fcntl(serverSocket[i], F_SETFL, O_NONBLOCK); //instead of waiting for the data to be avilabale of for write to finish it program execution. Instead of waiting for data to be available or for a write operation to complete, non-blocking sockets allow you to check if the operation can be performed immediately without waiting.
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);

    // don't care about writefds and exceptfds:
        select(0+1, &readfds, NULL, NULL, &tv);

        if (FD_ISSET(0, &readfds))
            printf("A key was pressed!\n");
        else
            printf("Timed out.\n");

        // addr_size = sizeof their_addr[i];
        // newFd = accept(serverSocket[i], (struct sockaddr *)&their_addr[i], &addr_size); // will creat a new fd that is ready to sent and receiv and for the socket one it's been listining
        
        
        
        // while (1);

        // std::cout << serverSocket[i] << " addr:" << conf->ser[i].socketAddr << '\n';
    }
    // for (int i = 0;i < conf->serversNumber; i++)
        // freeaddrinfo(result[i]);

// struct addrinfo hints, *result;
//     memset(&hints, 0, sizeof(struct addrinfo));
//     hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
//     hints.ai_socktype = SOCK_STREAM; // Stream socket (TCP)
}


