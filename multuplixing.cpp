#include "headers/multuplixing.hpp"

void multuplixing(conf* conf)
{
    // exit(1);

    int serverSocket[conf->serversNumber];
    struct addrinfo hints[conf->serversNumber];
    struct addrinfo *result[conf->serversNumber];
    struct sockaddr_storage their_addr[conf->serversNumber]; //wher the infos about upcoming connections will go
    int listen_fd;
    int newFd;
    socklen_t addr_size;

    for (int i = 0; i < conf->serversNumber; i++)
    {
        memset(&hints[i], 0, sizeof(struct addrinfo));
        hints[i].ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
        hints[i].ai_socktype = SOCK_STREAM; // Stream socket (TCP)
        hints[i].ai_flags = AI_PASSIVE;     // fill in my IP for me

        conf->ser[i].socketAddr = getaddrinfo(conf->ser[i].name.c_str(),
                                (std::to_string(conf->ser[i].listen)).c_str(),
                                &hints[i], &result[i]);

        
        // std::cout << conf->ser[i].listen;
        if (result[i] == NULL){
            fprintf(stderr, "getaddrinfo failed for %s:%d - %s\n",
            conf->ser[i].name.c_str(), conf->ser[i].listen, gai_strerror(conf->ser[i].socketAddr));
            exit(1);
        }
        if ((serverSocket[i] = socket(result[i]->ai_family,
                                result[i]->ai_socktype, result[i]->ai_protocol)) == -1){
            perror("socket");
            freeaddrinfo(result[i]);
            throw ("creating socket");
        }
        bind(serverSocket[i], result[i]->ai_addr, result[i]->ai_addrlen);
        // connect(serverSocket[i], result[i]->ai_addr, result[i]->ai_addrlen);
        listen_fd = listen(serverSocket[i], 2);
        addr_size = sizeof their_addr[i];
        newFd = accept(serverSocket[i], (struct sockaddr *)&their_addr[i], &addr_size); // will creat a new fd that is ready to sent and receiv and for the socket one it's been listining
        
        
        
        while (1);

        std::cout << serverSocket[i] << " addr:" << conf->ser[i].socketAddr << '\n';
    }

// struct addrinfo hints, *result;
//     memset(&hints, 0, sizeof(struct addrinfo));
//     hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
//     hints.ai_socktype = SOCK_STREAM; // Stream socket (TCP)
}