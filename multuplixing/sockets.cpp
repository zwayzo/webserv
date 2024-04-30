#include "client.hpp"
#include "socket.hpp"

void clearSets(client *mycl, int i, long long *s, int *index, fd_set *master_re, fd_set *master_wr) //clear the sets and initialze some variables(select)
{
    if (mycl->req.post == 1)
            mycl->req.fileD.close();
    FD_CLR(i, master_re);
    FD_SET(i, master_wr);
    *s = 0;
    *index = 0;
    mycl->req.post = 0;
    mycl->req.method = 0;
}


int validSocket(int j, conf *conf) //check if the j is a socket (need to be socket if want to work with methodes)
{
    for (std::vector<int>::iterator it = conf->vec.begin(); it != conf->vec.end(); it++)
    {
        if (*it == j)
            return 1;
    }
    return 0;
}


void addSocket(conf *conf)
{
    for (int i = 0; i < conf->serversNumber; i++)
        conf->vec.push_back(conf->ser[i].sock);
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