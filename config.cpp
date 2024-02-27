#include "headers/configFile.hpp"
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

    // std::cout << "------\n" << &mySer[i-1];
        if (mySer[i - 1] != ';' && mySer[i-1] != '}' && mySer[i-1] != '{' && mySer[i-1] != 10 && mySer[i - 1] != '\t'){
            // std::cout << static_cast<int>(mySer[i-1]);
            throw ("comma");}
        i++;
    }
}

void initLocation(server &ser, int n)
{
    location newLocation;
    newLocation.listen = 0;
    // newLocation.listen = 0;
    newLocation.post = 0;
    newLocation.get = 0;
    newLocation.deletee = 0;
    newLocation.index[0] = '\0';
    newLocation.root[0] = '\0';
    newLocation.redirection[0] = '\0';
    newLocation.theLoc[0] = '\0';
    // exit(1);
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
    std::cout << "root:" << ser.root << '\n';
    std::cout << "index:" << ser.index << '\n';
    std::cout << "error_page:" << ser.error_page << '\n';
    std::cout << "redirection:" << ser.redirection << '\n';
    std::cout << "name:" << ser.name << '\n';
    std::cout << "auto:" << ser.autoindex << '\n';


    for (int j = 0;j < n; j++)
    {
        std::cout << "\n\nlocation number:" << j << '\n';
        std::cout << "index:" << ser.loc[j].index << '\n';
        // std::cout "index:" << << ser.loc[j].listen << '\n';
        // std::cout "index:" << << ser.loc[j].post << '\n';
        // std::cout "index:" << << ser.loc[j].get << '\n';
        std::cout << "redirection:" << ser.loc[j].redirection << '\n';
        std::cout << "autoindex:" << ser.loc[j].autoindex << '\n';
        std::cout << "root:" << ser.loc[j].root << '\n';
        // std::cout << ser->loc[j].error_page << '\n';
    }

}

int storeLocationValue(server &ser, int n, int number)
{
    ser.loc[number].autoindex = 2;
    ser.loc[number].root = ser.root;
    ser.loc[number].index = ser.index;
    // std::cout << "in\n";
    int i = n + 9;
    // std::cout << "i is:" << i << '\n';
    while (ser.mySer[i] != '{')
        i++;
    i += 2;
    int in=0, ro=0, red=0, au=0;
    while (ser.mySer[i] != '}')
    {
        if (std::strncmp(&ser.mySer[i], "index", 5) == 0)
        {
            in++;
            i = i + 6;
            for (;ser.mySer[i] != ';'; i++)
                ser.loc[number].index.push_back(ser.mySer[i]);
            i++;
        }
        else if (std::strncmp(&ser.mySer[i], "root", 4) == 0)
        {
            ro++;
            // std::cout << "rwwoot\n";
            i = i + 5;
            for (;ser.mySer[i] != ';'; i++)
                ser.loc[number].root.push_back(ser.mySer[i]);
            i ++;
            // std::cout <<"==="<< i << '\n';
            // exit(1);
        }
        else if (std::strncmp((&ser.mySer)->c_str(), "methodes", 8) == 0)
        {
            i = i + 9;
            while (ser.mySer[i] != ';'){
            if (std::strncmp((&ser.mySer)->c_str(), "GET", 3) == 0)
            {
                ser.loc[number].get = 1;
                i += 4;
            }
            if (std::strncmp((&ser.mySer)->c_str(), "DELETE", 6) == 0)
            {
                ser.loc[number].deletee = 1;
                i += 7;
            }
            if (std::strncmp((&ser.mySer)->c_str(), "POST", 3) == 0)
            {
                ser.loc[number].post = 1;
                i += 5;
            }
            else 
                throw("location");
            }
        }
        else if (std::strncmp((&ser.mySer)->c_str(), "redirection", 11) == 0)
        {
            red++;
            i += 12;
            for (; ser.mySer[i]; i++)
                ser.loc[number].redirection.push_back(ser.mySer[i]);
        }
        else if (std::strncmp((&ser.mySer)->c_str(), "autoindex", 9) == 0)
        {
            au++;
            std::string tmp99;
            i += 10;
            if (!std::strncmp(&ser.mySer[i], "on;", 3))
            {
                ser.loc[number].autoindex = 1;
                i+= 2;
            }
            else if (!std::strncmp(&ser.mySer[i], "off;", 3))
            {
                ser.loc[number].autoindex = 0;
                i += 3 ;
            }
            else
                throw ("auto");
            
        }
        else 
            throw ("location");
        i++;
    }
    if (in == 0)
        ser.loc[number].index[0] = '\0';
    if (ro == 0)
        ser.loc[number].root[0] = '\0';
    if (red == 0)
        ser.loc[number].redirection[0] = '\0';
    if (in == 0)
        ser.loc[number].index[0] = '\0';
    if (in > 1 || ro > 1 || red > 1)
        throw ("numberss");
    // std::cout << "--\n" << &ser.mySer[i]<< "---\n";
    // std::cout << "safiii" << i << "\n";
    return i;
}


infos *checkValue(std::string mySer, infos *info, server &ser) 
{
    int i = 0;
    // std::cout << ser.mySer;
    // exit(1);
    int n = 0, l = 0, m=0, r=0, in=0, e=0, me=0 , a=0, nn=0;
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
            std::string tmp2;
            // tmp = NULL;
            i = i + 5;
            while (mySer[i] != ';' && mySer[i])
            {
                // std::cout << "-----" << mySer[i+1] << "-------\n";
                tmp2.push_back(mySer[i]);
                // if (mySer[i] < '0' || mySer[i] > '9')
                //     throw ("listen");
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    // std::cout << "ent2r\n";
                    // exit(2);
                    ser.name = tmp2;
                    nn++;
                    info->serverName["0"] = "name";
                    info->serverName["1"] = tmp2;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "max_body", 8) == 0)
        {
            // std::cout << "ent3r\n";
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
                    ser.max_size = std::atoi(tmp3.c_str());
                    m++;
                    info->maxBody[0] = "max";
                    info->maxBody[1] = tmp3;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "root", 4) == 0)
        {
            std::string tmp8;
            // std::cout << "ent4r\n";
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
                    ser.root = tmp8;
                    r++;
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
            std::map<std::string, std::string> Index2;
            std::string tmp4;
            // tmp = NULL;
            i = i + 6;
            // std::cout << &mySer[i];
            // exit(1);
            while (mySer[i] != ';' && mySer[i])
            {
                // std::cout << "w\n";
                tmp4.push_back(mySer[i]);
                // if (mySer[i] < '0' || mySer[i] > '9')
                //     throw ("listen");
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    ser.index = tmp4;
                    in++;
                    info->Index["0"] = "index";
                    info->Index["1"] = tmp4;
                    // std::cout << "l\n";
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
                    e++;
                    ser.error_page = tmp5;
                    info->errorPage["0"] = "error_page";
                    info->errorPage["1"] = tmp5;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "methodes", 8) == 0)
        {
            std::string tmp6;
            // std::cout <<"|||||||||||||\n";
            // exit(1);
            // tmp = NULL;
            i = i + 9;
            while (mySer[i] != ';' && mySer[i])
            {
                // std::cout << '"' <<  mySer[i] << "'\n";
                // std::cout << std::strncmp(&mySer[i], "GET", 3) << '\n';
                // std::cout << "ent9r\n";
                // exit(1);
                if (!std::strncmp(&mySer[i], "GET", 3))
                    ser.get = 1;
                if (!std::strncmp(&mySer[i], "DELETE", 6))
                    ser.deletee = 1;
                if (!std::strncmp(&mySer[i], "POST", 4))
                    ser.post = 1;
                tmp6.push_back(mySer[i]);
                // if (mySer[i] < '0' || mySer[i] > '9')
                //     throw ("listen");
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
            std::string tmp7;
            // std::cout << "ent22r\n";
            // tmp = NULL;
            i = i + 12;
            while (mySer[i] != ';' && mySer[i])
            {
                tmp7.push_back(mySer[i]);
                // if (mySer[i] < '0' || mySer[i] > '9')
                //     throw ("listen");
                i++;
                if (mySer[i] == ';' || mySer[i] == '\0'){
                    r++;
                    ser.redirection = tmp7;
                    info->redirection["0"] = "redirection";
                    info->redirection["1"] = tmp7;
                }
            }
        }
        else if (std::strncmp(&mySer[i], "autoindex", 9) == 0)
        {
            std::string tmp99;
            i += 10;
            if (!std::strncmp(&mySer[i], "on;", 3))
            {
                // exit(1);
                ser.autoindex = 1;
                info->autoindex[0] = "autoindex";
                info->autoindex[1] = "1";
                i+= 2;
            }
            else if (!std::strncmp(&mySer[i], "off;", 3))
            {
                a++;
                ser.autoindex = 1;
                info->autoindex[0] = "autoindex";
                info->autoindex[1] = "0";
                i += 3 ;
            }
            else
                throw ("auto");
            
        }
            i++;
        // std::cout << "{" << &mySer[i] << "-------------------\n";

    }
    // std::cout << "-->" << in << nn <<l<<m<<r<<e<<me<<a ;
    if (nn > 1 || l > 1 || m > 1 || r != 1 || in != 1 || e > 1 || me > 1 || a > 1 )
        throw ("numbers");
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
        && std::strncmp("index", &ser.mySer[i], n) && std::strncmp("methodes", &ser.mySer[i], n) && std::strncmp("redirection", &ser.mySer[i], n)
        && std::strncmp("server", &ser.mySer[i], n) && std::strncmp("}", &ser.mySer[i], n) && std::strncmp("autoindex", &ser.mySer[i], n))
            throw ("check");
        while (ser.mySer[j] != '\n' &&  ser.mySer[j])
            j++;
        j++;
    }
    checkComma(ser.mySer);
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
    ser.close = i;
    i = 0;

    // std::cout << "|||\n";
    // for(; ser.mySer[i] != '\n'; i++);
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
    // exit(1);
    // std::cout << conf->ser[indice].mySer;
}


void serverSize(std::string allIn, int indice, conf *conf)
{
    // std::cout << allIn;
    // exit(1);
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
    // std::cout << "---" << i;
    // std::cout << "{}" << allIn << "\n";
    i++;
    j = 0;
    // exit(1);
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
    // std::cout << "file:" << file;
    std::ifstream inputfile(file.c_str());
    std::string line;
    std::string allIn;
    int i = 0, j = 0, n = 0, x = 0;
    while (std::getline(inputfile, line))
    {
        x = 0;
        // std::cout << "her "<< line << "\n";
        while (line[i] == 32 || line[i] == '\t')
            i++;
        while (line[i] == '#'){
            x = 1;
            break;}
        // std::cout << "out\n";
        if (!x){if (std::strncmp(&line[i], "server", 6) == 0 && n != 0)
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
            allIn.push_back('\n');}
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
conf* fileConfiguration(conf *conf, std::string file)
{
    // std::string line;
    // int i = 0;
    // std::ifstream inputfile(file.c_str());
    conf->size = file_size(file);
    conf->serversNumber = checkServersNumber(file);
    conf->ser.reserve(conf->serversNumber);
    conf->allIn = getTheFileInOneString(file);
    // std::cout << "--\n";
    // std::cout << conf->allIn << '\n';
    // exit(2);
    for (int j = 0; j < conf->serversNumber; j++)
    {
        // std::cout << "j is:" << j << '\n';
        // conf->ser.reserve(1);
        server tmp(j);
        conf->ser.push_back(tmp);
        // exit(1);
        // std::cout << "1\n";
        serverSize(conf->allIn, j, conf);
        // std::cout << "2\n";
        stockserver(conf->allIn, conf, j);
        // std::cout << "3\n";
        // std::cout << conf->ser[j].mySer;
        checkAcollade(conf->ser[j]);
        conf->ser[j].get = 0;
        conf->ser[j].deletee = 0;
        conf->ser[j].post = 0;
        conf->ser[j].autoindex = 2;
        // std::cout << "4\n";
        conf->ser[j].locationsNumber = locationsNumbers(conf->ser[j].mySer);
        // std::cout << "5\n";
        conf->ser[j].loc.reserve(conf->ser[j].locationsNumber);
        // for (int n = 0;n < conf->ser[j].locationsNumber; n++)
        // {
        //     // conf->ser[j].loc.reserve(9);
        //     std::cout << "n:" << conf->ser[j].locationsNumber << '\n';
        //     initLocation(conf->ser[j], n);
        // }
        // std::cout << "6\n";
        stockLocation(conf, j);
        // std::cout << "7\n";
        checkPrototype(conf->ser[j]);
        wordCounter(conf->ser[j]);
        // std::cout << "8\n";
        conf->ser[j].info = new infos;
        // std::cout << "9\n";
        // exit(1);
        conf->ser[j].info = checkValue(conf->ser[j].mySer, conf->ser[j].info, conf->ser[j]);
        // std::cout << "out\n";
        // printArguments(info);
        
        // exit(1);
        // printArguments(conf->ser[j].info, conf->ser[j].locationsNumber, conf->ser[j]);
        // std::cout << conf->ser[j].loc[0].root;
        // for (int x = 0; x < conf->ser[j].locationsNumber; x++)
        //     std::cout << conf->ser[j].loc[x].theLoc<<"---------------\n";
        

        // std::cout <<"- server size - " <<conf->ser[j].size << " -- begin:" << conf->ser[j].begin << "  location num:"<<conf->ser[j].locationsNumber <<  "\n";
        // std::cout << "\n---------------------------\n";
        // exit(1);
    }
    return (conf);

    
    // std::cout << "number:" << conf-> serversNumber << '\n';
}