#include "configFile.hpp"


int storeLocationValue(server &ser, int n, int number)
{
    ser.loc[number].autoindex = 2;
    // ser.loc[number].root = ser.root;
    // ser.loc[number].index = ser.index;
    // std::cout << "in\n";
    int i = n;
    // printf("%s\n", &ser.mySer[i]);
    // printf("%d\n", std::strncmp(&ser.mySer[i], "location", 8));
    // exit(1);
    ser.loc[number].root.clear();
    // std::cout << "i is:" << i << '\n';
    ser.loc[number].redirection.clear();
    ser.loc[number].index.clear();
    // while (ser.mySer[i] != '{')
    //     i++;
    // i += 2;
    int in=0, ro=0, red=0, au=0, na=0;
    while (ser.mySer[i] != '}')
    {
        if (std::strncmp(&ser.mySer[i], "location", 8) == 0)
        {
            na++;
            i += 9;
            for (;ser.mySer[i] != '{'; i++){
                ser.loc[number].name.push_back(ser.mySer[i]);
            }
            i += 1;
            //     printf("%s\n", &ser.mySer[i]);
            // exit(1);
        } 
        else if (std::strncmp(&ser.mySer[i], "index", 5) == 0)
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
            i = i + 5;
            for (;ser.mySer[i] != ';'; i++){
            // std::cout <<ser.mySer[i] << "-\n";
                ser.loc[number].root.push_back(ser.mySer[i]);
            }
            // std::cout << ser.loc[number].root << "\n\n";
            // exit(1);
            i ++;
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
            else{
                throw("location");
            }
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
                throw ("error in auto index\n");
            
        }
        else {
                printf("{%s}\n", &ser.mySer[i]);
            throw ("locatio0n");
        }
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
    if (na == 0)
        ser.loc[number].name[0] = '\0';
        // printf("%d|%d|%d\n",in,ro,red);
    // if (in != 1 || ro != 1 || red > 1)
    //     throw ("error depulacte in (index, root, or redirection)");
    return i;
}


void checkPrototype(server &ser)
{
    int i = 0 ,j = 0, n = 0;
    int x = 0;
    while (ser.mySer[i])
    {
        i = j;
        n = 0;
        while (ser.mySer[j] != 32 && ser.mySer[j] != '\t' && ser.mySer[j] != '\n' && x < ser.size){
            j++;
            n++;
        }
        if (n == 0)
            break;
        x++;
        if (ser.mySer[j] == '\0')
            break;
        if (std::strncmp("name", &ser.mySer[i],  n) && std::strncmp("listen", &ser.mySer[i], n) && std::strncmp("root", &ser.mySer[i], n)
        && std::strncmp("error_page", &ser.mySer[i], n) && std::strncmp("max_body", &ser.mySer[i], n) && std::strncmp("location", &ser.mySer[i], n)
        && std::strncmp("index", &ser.mySer[i], n) && std::strncmp("methodes", &ser.mySer[i], n) && std::strncmp("redirection", &ser.mySer[i], n)
        && std::strncmp("server", &ser.mySer[i], n) && std::strncmp("}", &ser.mySer[i], n) && std::strncmp("autoindex", &ser.mySer[i], n)
        && std::strncmp("uploads", &ser.mySer[i], n))
            throw ("error in prototype\n");
        while (ser.mySer[j] != '\n' &&  ser.mySer[j])
            j++;
        j++;
    }
    checkComma(ser.mySer);
}


std::string getTheFileInOneString(std::string file)
{
    std::ifstream inputfile(file.c_str());
    std::string line;
    std::string allIn;
    int i = 0, j = 0, n = 0, x = 0;
    while (std::getline(inputfile, line))
    {
        x = 0;
        while (line[i] == 32 || line[i] == '\t')
            i++;
        while (line[i] == '#'){
            x = 1;
            break;}
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

void checkConfigFileRules(server &ser)
{
    printf("%d\n", ser.index_number);
    if (ser.index_number != 1)
        throw ("eroor in index number");
    if (!ser.error_page_number)
        throw ("eroor in eroor_page numbers");
    if (ser.name_number != 1)
        throw ("eroor in server name");
    if (ser.redirection_number != 1)
        throw ("eroor in redirection number");
    if (ser.root_number != 1)
        throw ("eroor in root number");
    if (ser.uploads_number != 1)
        throw ("eroor in uploads_number number");
    if (ser.listen_number != 1)
        throw ("eroor in listen number");
    if (ser.autoindex_number != 1)
        throw ("eroor in autoindex_number");
    if (ser.max_size_number != 1)
        throw ("eroor in max_size number");
    if (ser.methodes_number != 1)
        throw ("eroor in methodes number");
}
