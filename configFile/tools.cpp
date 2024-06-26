#include "configFile.hpp"

void checkComma(std::string mySer)
{
    int i = 0;
    while (mySer[i] != '\n')
        i++;
    i++;
    while (mySer[i])
    {
        while (mySer[i] != '\n')
            i++;

        if (mySer[i - 1] != ';' && mySer[i-1] != '}' && mySer[i-1] != '{' && mySer[i-1] != 10 && mySer[i - 1] != '\t'){
            throw ("error need comma...\n");}
        i++;
    }
}

void initLocation(server &ser, int n)
{
    location newLocation;
    newLocation.listen = 0;
    newLocation.post = 0;
    newLocation.get = 0;
    newLocation.deletee = 0;
    newLocation.index[0] = '\0';
    newLocation.root[0] = '\0';
    newLocation.redirection[0] = '\0';
    newLocation.theLoc[0] = '\0';
    ser.loc[n] = newLocation;

}

void wordCounter(server &ser)
{
    int i = 0;
    for (; ser.mySer[i]; i++);
    ser.wor = i;
}

void printArguments(infos *info, int n, server &ser)
{
    // (void &) ser;
    // int i = 0;
    // std::map<std::string, std::string>::iterator it = info->errorPage.begin();
    // printf("location number:%d\n", ser.locationsNumber);
    for (std::map<std::string, std::string>::iterator it = info->errorPage.begin(); it != info->errorPage.end(); ++it)
        std::cout <<"Key: " << it->first << ", Value: " << it->second << std::endl;

    for (std::map<int, std::string>::iterator it = info->listenMap.begin(); it != info->listenMap.end(); ++it)
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;

    for (std::map<int, std::string>::iterator it = info->maxBody.begin(); it != info->maxBody.end(); ++it)
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;

    for (std::map<std::string, std::string>::iterator it = info->serverName.begin(); it != info->serverName.end(); ++it)
        std::cout <<" Key: " << it->first << ", Value: " << it->second << std::endl;

    for (std::map<std::string, std::string>::iterator it = info->root.begin(); it != info->root.end(); ++it)
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;

    for (std::map<std::string, std::string>::iterator it = info->uploads.begin(); it != info->uploads.end(); ++it)
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    
    for (std::map<std::string, std::string>::iterator it = info->Index.begin(); it != info->Index.end(); ++it)
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;

    for (std::map<std::string, std::string>::iterator it = info->methodes.begin(); it != info->methodes.end(); ++it)
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;

    for (std::map<std::string, std::string>::iterator it = info->redirection.begin(); it != info->redirection.end(); ++it)
        std::cout <<  "Key: " << it->first << ", Value: " << it->second << std::endl;
    
    for (std::map<int, std::string>::iterator it = info->autoindex.begin(); it != info->autoindex.end(); ++it)
        std::cout <<  "Key: " << it->first << ", Value: " << it->second << std::endl;
    
    std::cout << "\n\n";
    std::cout << "methodes:\n" << "get:" << ser.get << '\n' << "delete:" << ser.deletee << '\n' << "post:" << ser.post << '\n';
    std::cout << "Allowed Methods:";
    for(std::vector<std::string>::iterator it= ser._methods.begin(); it != ser._methods.end(); it++)
       std::cout << *it << " ";
    std::cout << "\n";
    std::cout << "root:" << ser.root << '\n';
    std::cout << "index:" << ser.index << '\n';
    std::cout << "error_page:" << ser.error_page << '\n';
    std::cout << "redirection:" << ser.redirection << '\n';
    std::cout << "name:" << ser.name << '\n';
    std::cout << "auto:" << ser.autoindex << '\n';
    std::cout << "uploads:" << ser.uploads << '\n';
    std::cout << "max:" << ser.max_size << '\n';
    std::cout << "thi server has " << ser.locationsNumber << " locations\n";


    for (int j = 0;j < n; j++)
    {
        std::cout << "\n\nlocation number:" << j << '\n';
        std::cout << "name:" << ser.loc[j].name << '\n';
        std::cout << "index:" << ser.loc[j].index << '\n';
        // std::cout "index:" << << ser.loc[j].listen << '\n';
        // std::cout "index:" << << ser.loc[j].post << '\n';
        std::vector<std::string>::iterator it = ser.loc[j]._methods.begin();
        for (; it != ser.loc[j]._methods.end(); it++)
            std::cout << "Location Methods: " << *it << '\n';
        std::cout << "redirection:" << ser.loc[j].redirection << '\n';
        std::cout << "autoindex:" << ser.loc[j].autoindex << '\n';
        std::cout << "root:" << ser.loc[j].root << '\n';
        // std::cout << ser->loc[j].error_page << '\n';
    }

}

void getBegin(int indice, conf *conf, std::string allIn)
{
    int i = 1, j = 0, n = 0;
    while (j != indice)
    {
        if (allIn[i] =='\n' && allIn[i + 1] == '\n')
            j++;
        if (allIn[i] == '\n')
            n++;
        i++;
    }
    if (indice == 0)
        conf->ser[indice].begin = n;
    else
        conf->ser[indice].begin = n + 1;
}

void init_variables(server &ser)
{
    ser.autoindex_number = 0;
    ser.error_page_number = 0;
    ser.index_number = 0;
    ser.listen_number = 0;
    ser.max_size_number = 0;
    ser.methodes_number = 0;
    ser.name_number = 0;
    ser.redirection_number = 0;
    ser.root_number = 0;
    ser.uploads_number = 0;
    ser.get = 0;
    ser.deletee = 0;
    ser.post = 0;
    ser.autoindex = 2;
    
}