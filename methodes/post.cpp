#include "../multuplixing/multuplixing.hpp"
#include "post.hpp"

int randomNum() //get rendom number to add it in file[number].extention (post method)
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    
    // Generate a random number between 1 and 1000
    return ((std::rand() % 1000) + 1);
    
} 

void getMethodes(std::string buf, client *cl) //check if the method is post to work with
{
    // printf("her\n");
    cl->req.method = 1;
    // printf("%s\n", buf.c_str());
    // exit(1);
    if (std::strncmp(buf.c_str(), "POST", 4) == 0)
        cl->req.post = 1;
}
 
void getRequestLenght(char *buf, client *cl) //get the request lenght of post so to know how many time i nead to read(post)
{
    std::string tmp = buf;
    size_t pos = tmp.find("Content-Length: ");
    std::string t;
    pos += 16;
    if (pos != 15){
    while (tmp[pos] != '\n'){
        t = t + tmp[pos];
        pos++;
    }
    if (std::atoi(t.c_str()) < 0)
        cl->req.contentLenght = strtoll(t.c_str(), NULL, std::strlen(t.c_str()));
    else
        cl->req.contentLenght = std::atoi(t.c_str());
    }
    std::cout << "contentLenght: ----------------| " << cl->req.contentLenght << " |\n";
}

std::map<int, client>::iterator post(std::map<int, client>::iterator iter, int i, int nbytes)
{
    int z = 0;
    /*
    if (iter->second.req.first)
        ifChucked()
    if (iter->second.req.chuncked)
        postIsChucked()
    else {*/
    if (iter->second.req.first == 0){
        // std::cout << "in create file\n";
        // std::cout << "1-------------------------------------\n" << iter->second.req.buff <<"\n2----------------------------------\n";
        z = creatFile(i, iter->second.req.buff, &iter->second);
        /*if (iter->second.req.chuncked = 1)
        {

        }
        else{*/
        iter->second.req.fileD.write(&iter->second.req.buff[z], nbytes - z);
        iter->second.req.track += nbytes;
        // }
        // std::cout << "track is " << iter->second.req.track << " lenght is " << iter->second.req.contentLenght << "\n-------------out-------------\n";
    }
    // else if (iter->second.req.chuncked = 1)
    // {
    //     //
    // }
    else{
        // std::cout << "in write to file\n";
        iter->second.req.fileD.write(iter->second.req.buff, nbytes);
        iter->second.req.track += nbytes;
    }
    // }
    iter->second.req.first++;
    return (iter);
}