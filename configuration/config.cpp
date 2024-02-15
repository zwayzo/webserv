#include "../headers/configFile.hpp"

infos *checkValue(std::string mySer, infos *info)
{
    // infos *info = new infos;
    int i = 0;
    for (;mySer[i] != '\n'; i++);
    i++;
    // std::cout << &mySer[i];
    while(mySer[i])
    {
        // if (std::strncmp÷)
        // std::cout << std::strncmp(&mySer[i], "listen", 6);
        // exit(1);
        // std::cout <<"1---------\n"<< &mySer[i] << "2_______________________\n";
        if (std::strncmp(&mySer[i], "listen", 6) == 0)
        {
            // std::cout << "enter\n";
            std::string tmp1;
            // tmp = NULL;
            i = i + 7;
            while (mySer[i] != ';' && mySer[i])
            {
                // std::cout << "------ " << &mySer[i] << "--------";
                tmp1.push_back(mySer[i]);
                if ((mySer[i] < '0' || mySer[i] > '9') && mySer[i] != ';')
                {
                    throw ("listen");
                }
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    // std::cout << "{}\n";
                    info->listenMap[0] = "listen";
                    info->listenMap[1] = tmp1;
                    // std::cout << "oppp\n";
                    break;
                }

            }
        }

        else if (std::strncmp(&mySer[i], "name", 4) == 0)
        {
            // std::cout << "entr\n";
            std::string tmp2;
            // tmp = NULL;
            i = i + 5;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp2.push_back(mySer[i]);
                // if (mySer[i] < '0' || mySer[i] > '9')
                //     throw ("listen");
                if (mySer[i] == '\n' || mySer[i] == '\0'){
                    info->serverName[0] = "name";
                    info->serverName["1"] = tmp2;
                }
                i++;
            }
        }
        else if (std::strncmp(&mySer[i], "max_body", 8) == 0)
        {
            // exit(1);
            std::string tmp3;
            // tmp = NULL;
            i = i + 9;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp3.push_back(mySer[i]);
                if (mySer[i] < '0' || mySer[i] > '9')
                    throw ("max");
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    info->maxBody[0] = "max";
                    info->maxBody[1] = tmp3;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "root", 4) == 0)
        {
            std::string tmp8;
            // tmp = NULL;
            i = i + 5;
            // std::cout <<"|||"<< &mySer[i];
            // exit(1);
            while (mySer[i] != ';' && mySer[i])
            {
                tmp8.push_back(mySer[i]);
                // if (mySer[i] < '0' || mySer[i] > '9')
                //     throw ("listen");
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    // std::cout << "in\n";
                    info->root["0"] = "root";
                    // exit(1);
                    info->root["1"] = tmp8;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "index", 5) == 0)
        {
            // std::cout << "[[[[]]]]";
            // exit(1);
            std::map<std::string, std::string> Index2;
            std::string tmp4;
            // tmp = NULL;
            i = i + 6;
            // std::cout << &mySer[i];
            // exit(1);
            while (mySer[i] != ';' && mySer[i])
            {
                tmp4.push_back(mySer[i]);
                // if (mySer[i] < '0' || mySer[i] > '9')
                //     throw ("listen");
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    info->Index["0"] = "index";
                    info->Index["1"] = tmp4;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "error_page", 10) == 0)
        {
            // std::cout << "fede\n";
            std::string tmp5;
            // tmp = NULL;
            i = i + 11;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp5.push_back(mySer[i]);
                // if (mySer[i] < '0' || mySer[i] > '9')
                //     throw ("listen");
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    info->errorPage["0"] = "error_page";
                    info->errorPage["1"] = tmp5;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "methodes", 8) == 0)
        {
            std::string tmp6;
            // tmp = NULL;
            i = i + 9;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp6.push_back(mySer[i]);
                // if (mySer[i] < '0' || mySer[i] > '9')
                //     throw ("listen");
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    info->methodes["0"] = "methodes";
                    info->methodes["1"] = tmp6;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "redirection", 11) == 0)
        {
            std::string tmp7;
            // tmp = NULL;
            i = i + 12;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp7.push_back(mySer[i]);
                // if (mySer[i] < '0' || mySer[i] > '9')
                //     throw ("listen");
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    info->redirection["0"] = "redirection";
                    info->redirection["1"] = tmp7;
                }
            }
        }
        // else
            i++;
        // std::cout << "{" << &mySer[i] << "-------------------\n";

    }
    return info;
}


void checkPrototype(server &ser)
{
    int i = 0 ,j = 0, n = 0;
    // int z = 0;
    // while (ser.mySer[i] != '\n')
    //     i++;
    // i++;
    int x = 0;
    while (ser.mySer[i])
    {
        i = j;
        n = 0;
        // for ( z=j;ser.mySer[z] != '\n';z++)
        //     std::cout << ser.mySer[z];
        // std::cout<<"'";
        while (ser.mySer[j] != 32 && ser.mySer[j] != '\t' && ser.mySer[j] != '\n' && x < ser.size){
            j++;
            n++;
        }
        if (n == 0)
            break;
        x++;
        if (ser.mySer[j] == '\0')
            break;
        // std::cout << "+_________________\n" << &ser.mySer[i];
        // std::cout << n << "}\n";
        if (std::strncmp("name", &ser.mySer[i],  n) && std::strncmp("listen", &ser.mySer[i], n) && std::strncmp("root", &ser.mySer[i], n)
        && std::strncmp("error_page", &ser.mySer[i], n) && std::strncmp("max_body", &ser.mySer[i], n) && std::strncmp("location", &ser.mySer[i], n)
        && std::strncmp("index", &ser.mySer[i], n) && std::strncmp("methods", &ser.mySer[i], n) && std::strncmp("redirection", &ser.mySer[i], n)
        && std::strncmp("server", &ser.mySer[i], n) && std::strncmp("}", &ser.mySer[i], n))
            throw ("check");
        while (ser.mySer[j] != '\n' &&  ser.mySer[j])
            j++;
        j++;
    }
}

void checkAcollade(server &ser)
{
    // std::cout << ser.mySer << '\n';
    // std::cout << "enter\n";
    int i = 0, j = 0, n = 0;
    while (ser.mySer[n])
    {
        if (ser.mySer[n] == '{'){
            // std::cout << "__________\n";
            // std::cout << &ser.mySer[n];
            i++;
            }
        else if (ser.mySer[n] == '}'){
            // std::cout << "__________\n";
            // std::cout << &ser.mySer[n];
            j++;
            }
        n++;
    }
    // std::cout << i << '|' << j << '\n';
    if (i != j)
        throw ("syntax");
    i = 0;

    for(;ser.mySer[i] != '\n'; i++);
    // std::cout << std::strncmp(&ser.mySer[0], "server{\n", i) << '|' << std::strncmp(&ser.mySer[0], "server {", i) << '|' << std::strncmp(&ser.mySer[0], "server\n{", i) << '|' << std::strncmp(&ser.mySer[0], "server{\n", i) << '|' << std::strncmp(&ser.mySer[0], "server {\n", i) <<'\n';
    if (std::strncmp(&ser.mySer[0], "server{", i) != 0 && std::strncmp(&ser.mySer[0], "server {", i) != 0
    && std::strncmp(&ser.mySer[0], "server\n{", i) != 0
    && std::strncmp(&ser.mySer[0], "server{\n", i) != 0 && std::strncmp(&ser.mySer[0], "server {\n", i) != 0)
        throw ("server syntax");
}

void stockLocation(conf *conf, int indice)
{
    int i = 0, j = 0;

    while (conf->ser[indice].mySer[i])
    {
        if (std::strncmp(&conf->ser[indice].mySer[i], "location", 8) == 0)
        {
            // Assuming loc is a vector of location objects
            location newLocation; // Create a new location object

            while (conf->ser[indice].mySer[i] != '}')
            {
                // std::cout << conf->ser[indice].mySer[i];
                newLocation.theLoc.push_back(conf->ser[indice].mySer[i]);
                i++;

                if (conf->ser[indice].mySer[i] == '}')
                {
                    j++;
                    break; // Exit the inner loop
                }
            }
            newLocation.theLoc.push_back('}');
            newLocation.theLoc.push_back('\n');
            // Assuming loc is a vector of location objects
            conf->ser[indice].loc.push_back(newLocation); // Add the newLocation to the loc vector
            // std::cout << "enter2\n";
        }
        i++;
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

void stockserver(std::string allIn, conf *conf, int indice)
{
    int n = 0;
    int i = 0;
    while (n != indice)
    {
        while (n != indice && allIn[i])
        {
            if (allIn[i] == '\n' && allIn[i - 1] == '\n')
                n++;
            i++;
        }
    }
    n = 0;
    while (n <= conf->ser[indice].size)
    {
        if (allIn[i] == '\n')
            n++;
        conf->ser[indice].mySer.push_back(allIn[i]);
        i++;
    }
    conf->ser[indice].mySer.push_back('\0');
}


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

std::string getTheFileInOneString(std::string file)
{
    std::ifstream inputfile(file.c_str());
    std::string line;
    std::string allIn;
    int i = 0, j = 0, n = 0;
    while (std::getline(inputfile, line))
    {
        while (line[i] == 32 || line[i] == '\t')
            i++;
        if (line[i] == '#')
            break;
        if (std::strncmp(&line[i], "server", 6) == 0 && n != 0)
            allIn.push_back('\n');
        for (; line[i]; i++)
        {
            if ((line[i] == 32 || line[i] == '\t') && j == 0){
                allIn.push_back(line[i]);
                j++;}
            else if (line[i] != 32 && line[i] != '\t')
                allIn.push_back(line[i]);
        }
        if (i != 0)
            allIn.push_back('\n');
        i = 0;
        j = 0;
        n++;
    }
    allIn.push_back('\n');
    return allIn;
    
}


int checkServersNumber(std::string file)
{     
    std::ifstream inputfile(file.c_str());
    std::string line;
    // int i = 0;
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
void fileConfiguration(conf *conf, std::string file)
{
    // std::string line;
    // int i = 0;
    // std::ifstream inputfile(file.c_str());
    conf->size = file_size(file);
    conf->serversNumber = checkServersNumber(file);
    conf->ser.reserve(conf->serversNumber);
    conf->allIn = getTheFileInOneString(file);
    // std::cout << conf->allIn << '\n';
    for (int j = 0; j < conf->serversNumber; j++)
    {
        // std::cout << "j is:" << j << '\n';
        conf->ser.push_back(conf->ser[j]);
        serverSize(conf->allIn, j, conf);
        stockserver(conf->allIn, conf, j);
        checkAcollade(conf->ser[j]);
        conf->ser[j].locationsNumber = locationsNumbers(conf->ser[j].mySer);
        conf->ser[j].loc.reserve(conf->ser[j].locationsNumber);
        stockLocation(conf, j);
        checkPrototype(conf->ser[j]);
        infos *info = new infos;
        // exit(1);
        info = checkValue(conf->ser[j].mySer, info);
        // std::cout << "out\n";
        std::map<std::string, std::string>::iterator it = info->errorPage.begin();
        for (it = info->errorPage.begin(); it != info->errorPage.end(); ++it) {
            // std::cout << "in\n";
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }
        exit(1);

        /*
        for (int x = 0; x < conf->ser[j].locationsNumber; x++)
            std::cout << conf->ser[j].loc[x].theLoc<<"---------------\n";
        */

        // std::cout <<"- server size - " <<conf->ser[j].size << " -- begin:" << conf->ser[j].begin << "  location num:"<<conf->ser[j].locationsNumber <<  "\n";
        // std::cout << "---------------------------\n";
        // exit(1);
    }

    
    // std::cout << "number:" << conf-> serversNumber << '\n';
}