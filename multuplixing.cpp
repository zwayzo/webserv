#include "headers/multuplixing.hpp"

void multuplixing(conf* conf)
{
    // exit(1);

    int serverSoket[conf->serversNumber];
    // struct addrinfo[conf->serversNumber];
    struct addrinfo hints[conf->serversNumber];
    struct addrinfo *result[conf->serversNumber];
    for (int i = 0; i < conf->serversNumber; i++)
    {
        memset(&hints, 0, sizeof(struct addrinfo));
        hints[i].ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
        hints[i].ai_socktype = SOCK_STREAM; // Stream socket (TCP)

        if ((serverSoket[i] = socket(AF_INET6, SOCK_STREAM, 0)) == -1)
            throw ("creating socket");
        
        conf->ser[i].socketAddr = getaddrinfo(conf->ser[i].name.c_str(),
                                (std::to_string(conf->ser[i].listen)).c_str(),
                                &hints[i], &result[i]);
        std::cout << serverSoket[i];
    }

// struct addrinfo hints, *result;
//     memset(&hints, 0, sizeof(struct addrinfo));
//     hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
//     hints.ai_socktype = SOCK_STREAM; // Stream socket (TCP)
}