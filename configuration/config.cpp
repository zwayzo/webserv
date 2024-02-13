#include "../headers/configFile.hpp"

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

void stockServeur(std::string allIn, conf *conf, int indice)
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
    // std::cout << "_____________\n";
    // std::cout << &allIn[i];
    i = 0;
    int j = 0;
    // std::cout << "size:" << conf->ser[indice].size << '\n';
    // exit(1);
    while (i < conf->ser[indice].size)
    {
        if (allIn[j] == '\n')
            i++;
        conf->ser[indice].mySer.push_back(allIn[j]);
        // std::cout << allIn[j] << i;
        j++;
        // std::cout << "i is:" << i<< '\n';
    }
}


void serveurSize(std::string allIn, int indice, conf *conf)
{
    // std::cout << allIn;
    // exit(2);
    // std::cout  <<"______\n";
    // std::cout << "indice:" << indice << '\n';
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
    // std::cout << &allIn[i];
    i++;
    j = 0;
    while (allIn[i] != '\n' || allIn[i - 1] != '\n')
    {
        if (allIn[i] == '\n')
            j++;
        // std::cout <<allIn[i]<<'\n';
        i++;
    }
    // std::cout << "{}{}\n";
    // exit(1);
    // std::cout << &allIn[i];
    conf->ser[indice].size = j;
    // std::cout <<"---"<< j << '\n';
    // return (j);
}

int locationsNumbers(std::string allIn, conf *conf, int x)
{
    // std::cout << "{}" << allIn;
    // exit(1);
    int i = 0, j = 0, n = 0;
    while (allIn[i] && allIn[i] != '\n')
    {
        // std::cout <<"{}{}\n";
        // std::cout << allIn[i] << '\n';
        if (std::strncmp(&allIn[i], "location", 8) == 0)
            j++;
        while (allIn[i] != '\n' && allIn[i])
            i++;
        i++;
        n++;
    }
    conf->ser[x].size = n;
    return j;
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
        // std::cout << conf->ser[j].mySer;
        serveurSize(conf->allIn, j, conf);
        // conf->ser[j].locationsNumber = locationsNumbers(conf->allIn, conf, j);
        // conf->ser[j].loc.reserve(conf->ser[j].locationsNumber);
        // stockServeur(conf->allIn, conf, j);

        // std::cout << conf->allIn;
        std::cout <<"- serveur size - " <<conf->ser[j].size << " -- begin:" << conf->ser[j].begin <<  "\n";
        // exit(1);
    }

    
    // std::cout << "number:" << conf-> serversNumber << '\n';
}