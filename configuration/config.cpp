#include "../headers/configFile.hpp"

// void stockServeur(std::string allIn, conf *conf, int indice)
// {
//     int i = 0;
//     int j = 0;
//     while (j != conf->)
//     {

//     }
// }


int serveurSize(std::string allIn)
{
    int i = 0;
    while (allIn[i] && allIn[i] != '\n')
        i++;
    return (i);
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
    std::cout << "n is " << n << '\n';
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
        // std::cout << j << '\n';
        conf->ser.push_back(conf->ser[j]);
        conf->ser[j].locationsNumber = locationsNumbers(conf->allIn, conf, j);
        // conf->ser[j].size = serveurSize(conf->allIn);
        conf->ser[j].loc.reserve(conf->ser[j].locationsNumber);

        std::cout << conf->ser[j].locationsNumber << "--" <<conf->ser[j].size << "\n";
    }

    
    // std::cout << "number:" << conf-> serversNumber << '\n';
}