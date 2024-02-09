#include "../headers/configFile.hpp"

int serveurSize(std::string file, int ligne, serveur *ser)
{
    std::ifstream inputfile(file.c_str());
    std::string line;
    int i = 0;
    int j = 0;
    for (j = 0; j < ligne; j++)
        std::getline(inputfile, line);
    if ()
    

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
    for (int j = 0; j < conf->serversNumber; j++)
    {
        std::cout << j << '\n';
        conf->ser.push_back(conf->ser[j]);
    }
    
    // std::cout << "number:" << conf-> serversNumber << '\n';
}