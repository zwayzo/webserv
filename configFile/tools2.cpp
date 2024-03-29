#include "configFile.hpp"

void serverSize(std::string allIn, int indice, conf *conf)
{
    getBegin(indice, conf, allIn);
    int i = 0, j = 0;
    while (allIn[i] && j != indice)
    {
        if (allIn[i] == '\n' && allIn[i - 1] == '\n')
            j++;
        if (j == indice)
            break;
        i++;
    }
    i++;
    j = 0;
    while (allIn[i] != '\n' || allIn[i - 1] != '\n')
    {
        if (allIn[i] == '\n')
            j++;
        i++;
    }
    conf->ser[indice].size = j;
}


int locationsNumbers(std::string mySer)
{
    int i = 0, n = 0;
    while (mySer[i])
    {
        if (std::strncmp(&mySer[i], "location", 8) == 0)
            n++;
        i++;
    }
    return n;
}


int checkServersNumber(std::string file)
{     
    std::ifstream inputfile(file.c_str());
    std::string line;
    int j = 0;
    while (std::getline(inputfile, line))
    {
        if (std::strncmp(line.c_str(), "server", 6) == 0)
            j++;
    }
    return j;
}


int file_size(std::string file)
{
    std::ifstream inputfile(file.c_str());
    std::string line;
    std::getline(inputfile, line);
    int i = 1;
    while (std::getline(inputfile, line))
        i++;
    return i;
}


void checkAcollade(server &ser)
{
    int i = 0, j = 0, n = 0;
    while (ser.mySer[n])
    {
        if (ser.mySer[n] == '{')
            i++;
        else if (ser.mySer[n] == '}')
            j++;
        n++;
    }
    if (i != j)
        throw ("error in allocade(config file)");
    ser.close = i;
    i = 0;
    if (std::strncmp(&ser.mySer[0], "server{", i) != 0 && std::strncmp(&ser.mySer[0], "server {", i) != 0
    && std::strncmp(&ser.mySer[0], "server\n{", i) != 0
    && std::strncmp(&ser.mySer[0], "server{\n", i) != 0 && std::strncmp(&ser.mySer[0], "server {\n", i) != 0)
        throw ("error in config file syntax");
}


infos *checkValue(std::string mySer, infos *info, server &ser) 
{
    int i = 0;
    int n = 0, l = 0, m=0, r=0, in=0, e=0, me=0 , a=0, nn=0, u=0;
    for (;mySer[i] != '\n'; i++);
    i++;
    while(mySer[i])
    {
        if (std::strncmp(&mySer[i], "location", 8) == 0){
            i = storeLocationValue(ser, i, n);
            n++;
        }
        else if (std::strncmp(&mySer[i], "listen", 6) == 0)
        {
            ser.listen_number++;
            std::string tmp1;
            i = i + 7;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp1.push_back(mySer[i]);
                if ((mySer[i] < '0' || mySer[i] > '9') && mySer[i] != ';')
                {
                    throw ("listen");
                }
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    l++;
                    ser.listen = std::atoi(tmp1.c_str());
                    info->listenMap[0] = "listen";
                    info->listenMap[1] = tmp1;
                    break;
                }

            }
        }
        else if (std::strncmp(&mySer[i], "name", 4) == 0)
        {
            ser.name_number++;
            std::string tmp2;
            // tmp = NULL;
            i = i + 5;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp2.push_back(mySer[i]);
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    ser.name = tmp2;
                    nn++;
                    info->serverName["0"] = "name";
                    info->serverName["1"] = tmp2;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "max_body", 8) == 0)
        {
            ser.max_size_number++;
            std::string tmp3;
            i = i + 9;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp3.push_back(mySer[i]);
                if (mySer[i] < '0' || mySer[i] > '9')
                    throw ("max");
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    ser.max_size = std::atoi(tmp3.c_str());
                    m++;
                    info->maxBody[0] = "max";
                    info->maxBody[1] = tmp3;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "root", 4) == 0)
        {
            ser.root_number++;
            std::string tmp8;
            i = i + 5;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp8.push_back(mySer[i]);
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    ser.root = tmp8;
                    r++;
                    info->root["0"] = "root";
                    info->root["1"] = tmp8;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "index", 5) == 0)
        {
            ser.index_number++;
            std::map<std::string, std::string> Index2;
            std::string tmp4;
            i = i + 6;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp4.push_back(mySer[i]);
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    ser.index = tmp4;
                    in++;
                    info->Index["0"] = "index";
                    info->Index["1"] = tmp4;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "error_page", 10) == 0)
        {
            ser.error_page_number++;
            std::string tmp5;
            i = i + 11;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp5.push_back(mySer[i]);
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    e++;
                    ser.error_page = tmp5;
                    info->errorPage["0"] = "error_page";
                    info->errorPage["1"] = tmp5;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "methodes", 8) == 0)
        {
            ser.methodes_number++;
            std::string tmp6;
            i = i + 9;
            while (mySer[i] != ';' && mySer[i])
            {
                if (!std::strncmp(&mySer[i], "GET", 3))
                    ser.get = 1;
                if (!std::strncmp(&mySer[i], "DELETE", 6))
                    ser.deletee = 1;
                if (!std::strncmp(&mySer[i], "POST", 4))
                    ser.post = 1;
                tmp6.push_back(mySer[i]);
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    me++;
                    info->methodes["0"] = "methodes";
                    info->methodes["1"] = tmp6;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "redirection", 11) == 0)
        {
            ser.redirection_number++;
            std::string tmp7;
            i = i + 12;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp7.push_back(mySer[i]);
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    r++;
                    ser.redirection = tmp7;
                    info->redirection["0"] = "redirection";
                    info->redirection["1"] = tmp7;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "uploads", 7) == 0)
        {
            ser.uploads_number++;
            std::string tmp00;
            i = i + 8;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp00.push_back(mySer[i]);
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    u++;
                    ser.uploads = tmp00;
                    info->uploads["0"] = "uploads";
                    info->uploads["1"] = tmp00;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "autoindex", 9) == 0)
        {
            ser.autoindex_number++;
            std::string tmp99;
            i += 10;
            if (!std::strncmp(&mySer[i], "on;", 3))
            {
                ser.autoindex = 1;
                info->autoindex[0] = "autoindex";
                info->autoindex[1] = "1";
                i+= 2;
            }
            else if (!std::strncmp(&mySer[i], "off;", 3))
            {
                ser.autoindex = 1;
                info->autoindex[0] = "autoindex";
                info->autoindex[1] = "0";
                i += 3 ;
            }
            else
            {
                throw ("auto");
                a++;
            }
        }
            i++;
    }
    // printf("%d|%d|%d|%d|%d|%d|%d|%d",nn,l,m,r,in,e,me,a);
    if (nn != 1 || l != 1 )
        throw ("error in numbers of element in config file\n");
    return info; 
}
