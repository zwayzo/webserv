#include "../headers/multuplixing.hpp"

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
    FD_ZERO(&read_fds); //clear the sets
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

