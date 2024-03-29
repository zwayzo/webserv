#include "multuplixing.hpp"
client&	returnClient(std::map<int, client> mycl, int i)
{
	std::map<int, client>::iterator iter = mycl.lower_bound(i);
    // std::cout << "i is : | " << i << " | \n";
    // std::cout << "client fd : | " << iter->second.req.fd << " | \n";
	// iter->second.clientFd = this->currentFdToWorkWith;
	// std::cout << "second fd : " << iter->second.clientFd << "\n";
	// std::cout << "HELLLO : " << iter->second.stageForClient << std::endl;
	return (iter->second);
}

void multuplixing(conf* conf)
{
    std::map <int, client> mycl;
    fd_set master_re, master_wr, read_fds, write_fds;    // master_re file descriptor list
    int maxfd, newFd, in = 0;
    getSocket(conf);
    maxfd = maxFd(conf);

    FD_ZERO(&master_re);
    FD_ZERO(&master_wr);
    FD_ZERO(&write_fds);
    FD_ZERO(&read_fds); //clear the sets
    signal(SIGTSTP, handleCtrlZ);
    std::cout << "multuplixing...start\n";
    for (int j = 0; j < conf->serversNumber; j++)
        FD_SET(conf->ser[j].sock, &master_re);
    for (;;)
    {
        read_fds =  master_re;
        write_fds =  master_wr;
        // printf("waiting...\n");
        if (select(maxfd + 1, &read_fds, &write_fds, NULL, NULL) == -1)
            throw ("ERROR IN SELECT");
        for (int i = 0; i <= maxfd; i++){
            if(FD_ISSET(i, &read_fds) || FD_ISSET(i, &write_fds))
            {
                if (!validSocket(i, conf))
                {
                    if ((newFd = accept(i, NULL, NULL)) == -1)
                        throw ("ERROR IN ACCEPTING\n");
                    std::cout << "new connection\n";
                    // printf("accept...\n");
                    client tmp;
                    attachClientServer(i, conf, &tmp);
                    tmp.req.index = in;
                    tmp.req.track = 0;
                    tmp.req.first = 0;
                    tmp.req.contentLenght = 0;
                    tmp.req.fd = newFd;
                    // std::cout << "fd: " << tmp.req.fd << "\n";
                    in++;
                    mycl.insert(std::pair<int, client>(newFd, tmp));
                    conf->vec.push_back(newFd);
                    FD_SET(newFd, &master_re);
                    if (newFd > maxfd)
                        maxfd = newFd;
                }
                else
                {
                    if (FD_ISSET(i, &read_fds)){
                        // client client = returnClient(mycl, i);
                        std::map<int, client>::iterator iter = mycl.lower_bound(i);
                        // std::cout << "----------- : fd: | " << iter->second.req.fd << " |\n";
                        client client = iter->second;

                        // std::cout << "----------------| " << i << " |---------------\n";
                        // std::cout << "client fd is : ----------------| " << iter->second.req.fd << " |---------------\n";
                        // std::cout << "client length is : ----------------| " << iter->second.req.contentLenght << " |---------------\n";

                        int nbytes = recv(i, iter->second.req.buff, sizeof(iter->second.req.buff), 0);
                        //  if (nbytes > 0)
                        //     parseHttpRequest(iter->second.req.buff, nbytes);
                        
    

                        if (nbytes != 0 && iter->second.req.method <= 0)
                            getMethodes(iter->second.req.buff, &iter->second);
                        else if (nbytes == -1)
                            throw ("error in recv\n");
                            
                        // std::cout << "after getting what methode..." << iter->second.req.post << "\n";
                        if (iter->second.req.post == 1)
                            post(iter, i, nbytes);
                        // printf("2\n");
                        // std::cout << iter->second.req.track << '\n';
                        // std::cout << iter->second.req.contentLenght << '\n';
                        // std::cout << nbytes << '\n';
                        
                        // usleep(100000);
                        if (nbytes > 0){
                            if (iter->second.req.track >= iter->second.req.contentLenght){
                                printf("time to clear\n");
                                clearSets(&iter->second, i, &iter->second.req.track, &iter->second.req.first, &master_re, &master_wr);
                            }
                        }
                        //working on request workRequest(buf);
                    }
                    if(FD_ISSET(i, &write_fds)){
                        // std::map<int, client>::iterator iter = mycl.lower_bound(i);
                        // std::cout << "----------- : fd: | " << iter->second.fd << " |\n";
                        // client client = iter->second;
                        // std::cout << "in write : ----------------| " << i << " |---------------\n";
                        printf("not new connection in write\n");

                        // std::map<int, client>::iterator it;
                        // for (it = mycl.begin(); it != mycl.end(); ++it) {
                        //     std::cout << "loop ----------------- : " << it->first << ": " << it->second.req.fd << std::endl;
                        // }

                        send(i, "slma", 5, 0);
                        //send response
                        FD_CLR(i, &master_wr);
                        close (i);
                        mycl.erase(i);

                        // std::map<int, client>::iterator iter;
                        // for (iter = mycl.begin(); iter != mycl.end(); ++iter) {
                        //     std::cout << "loop ----------------- : " << iter->first << ": " << iter->second.req.fd << std::endl;
                        // }

                        conf->vec.erase(std::remove(conf->vec.begin(), conf->vec.end(), i));
                    }
                }
            }
        }
    }
}



//51154

