#include "multuplixing.hpp"
#include "multuplixing.hpp"
#include "client.hpp"

multuplix::multuplix(){}

multuplix::multuplix(multuplix &copy) {
	(void)copy;
}

multuplix::~multuplix(){}

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

void	multuplix::multuplixing(conf* conf)
{
    fd_set master_re, master_wr, read_fds, write_fds;    // master_re file descriptor list
    int maxfd, clSocket, in = 0;
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
                    printf("fd: i: %d\n", i);
                    if ((clSocket = accept(i, NULL, NULL)) == -1)
                        throw ("ERROR IN ACCEPTING\n");
                    printf("fd: clSocket: %d\n", clSocket);
                    std::cout << "new connection\n";
                    printf("accept...\n");
                    client tmp;
                    tmp = attachClientServer(i, conf, tmp, in, clSocket);
                    tmp.req.first = 0;
                    in++;
                    mycl.insert(std::pair<int, client>(clSocket, tmp));
                    conf->vec.push_back(clSocket);
                    FD_SET(clSocket, &master_re);
					_httpRequest[clSocket] = HttpRequest(clSocket, mycl[clSocket].clientServer);
					// _httpResponse[clSocket] = HttpResponse(clSocket, mycl[clSocket].clientServer);
                    if (clSocket > maxfd)
                        maxfd = clSocket;
                }
                else
                {
                    std::map<int, client>::iterator iter = mycl.lower_bound(i); //iter to the client with the same socket as the server
					int _clSock = iter->first;
                    if (FD_ISSET(i, &read_fds)){
                        client cl = iter->second;
                        int nbytes = recv(i, cl.req.buff, sizeof(cl.req.buff), 0);
                        if (nbytes == -1)
                            throw ("Error: recv failed\n");
						cl.req.buff[nbytes] = '\0';
						if (nbytes == 0) {
							std::cout << "\rConnection was closed by client.\n" << std::endl;
							_httpRequest.erase(_clSock);
							// _httpResponse.erase(_clSock);
							close(_clSock); //should close the client connection
                        }
						_httpRequest[_clSock].parseHttpRequest(cl.req.buff, nbytes);
                        std::cout << _httpRequest[_clSock].getRequest();
                        std::cout << "\nFinREQUEST\n";
						//should check th first time body
                        // post_contentLenght(iter, i, nbytes);
                        if (nbytes > 0){
                            if (iter->second.req.track >= iter->second.req.contentLenght){
                        //         // printf("time to clear\n");
                                clearSets(&iter->second, i, &iter->second.req.track, &iter->second.req.first, &master_re, &master_wr);
                            }
                        }

                    }
                    if(FD_ISSET(i, &write_fds)){
						int response = 0;
						// if (_httpRequest[_clSock].getCodeError()) == 0) {
						// 	//CGI handler
						// 	//cgi Done
						// 	//send resp
						// response = _httpResponse[_clSock].sendResponse(_httpRequest[_clSock], _cgi);
						// }
						// else {
						// 	//send response
							// response = _httpResponse[_clSock].buildResponse(_httpRequest[_clSock]);//NULL MEANS NO CGI
                            // send(_clSock, "HTTP/1.1 200 OK\r\nContent-Type: text/html;\r\nContent-Length: 5;\r\n\r\nHELLO", 78, 0);
                            // close(_clSock);
                        // }

                        // printf("not new connection in write\n");
                        // send(i, "slma", 5, 0);
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