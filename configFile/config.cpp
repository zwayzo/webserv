#include "configFile.hpp"

server::server() {}

server::server(int n) : number(n){}

server::server(const server& copy) {
        this->post = copy.post;
		this->get = copy.get;
        this->deletee = copy.deletee;
        this->methodes_number = copy.methodes_number;
        this->locationsNumber = copy.locationsNumber;

		this->name = copy.name;
        this->listen = copy.listen;
        this->autoindex = copy.autoindex;
        this->max_size = copy.max_size;
		this->root = copy.root;
        this->uploads = copy.uploads;
        this->error_page = copy.error_page;
        this->index = copy.index;
		this->redirection = copy.redirection;
            // Copy the location objects
		this->loc.resize(copy.loc.size()); // Ensure the same size
		for (size_t i = 0; i < copy.loc.size(); ++i) {
        	this->loc[i] = copy.loc[i]; // Assuming location has a proper copy constructor
    }
}

server& server::operator=(const server& copy) {
    if (this != &copy) {
		this->post = copy.post;
		this->get = copy.get;
        this->deletee = copy.deletee;
        this->methodes_number = copy.methodes_number;
        this->locationsNumber = copy.locationsNumber;

		this->name = copy.name;
        this->listen = copy.listen;
        this->autoindex = copy.autoindex;
        this->max_size = copy.max_size;
		this->root = copy.root;
        this->uploads = copy.uploads;
        this->error_page = copy.error_page;
        this->index = copy.index;
		this->redirection = copy.redirection;
            // Copy the location objects
		this->loc.resize(copy.loc.size()); // Ensure the same size
		for (size_t i = 0; i < copy.loc.size(); ++i) {
        	this->loc[i] = copy.loc[i]; // Assuming location has a proper copy constructor
    	}
    }
	*this = copy;
}

server::~server() {}

void stockLocation(conf *conf, int indice)
{
    int i = 0, j = 0;

    while (conf->ser[indice].mySer[i])
    {
        if (std::strncmp(&conf->ser[indice].mySer[i], "location", 8) == 0)
        {
            location newLocation; // Create a new location object

            while (conf->ser[indice].mySer[i] != '}')
            {
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

conf* fileConfiguration(conf *conf, std::string file)
{
    conf->size = file_size(file);
    conf->serversNumber = checkServersNumber(file);
    conf->ser.reserve(conf->serversNumber);
    conf->allIn = getTheFileInOneString(file);
    for (int j = 0; j < conf->serversNumber; j++)
    {
        server tmp(j);
        conf->ser.push_back(tmp);
        serverSize(conf->allIn, j, conf);
        stockserver(conf->allIn, conf, j);
        checkAcollade(conf->ser[j]);
        init_variables(conf->ser[j]);
        conf->ser[j].locationsNumber = locationsNumbers(conf->ser[j].mySer);
        conf->ser[j].loc.reserve(conf->ser[j].locationsNumber);
        stockLocation(conf, j);
        checkPrototype(conf->ser[j]);
        wordCounter(conf->ser[j]);
        conf->ser[j].info = new infos;
        conf->ser[j].info = checkValue(conf->ser[j].mySer, conf->ser[j].info, conf->ser[j]);
        checkConfigFileRules(conf->ser[j]);
        printArguments(conf->ser[j].info, conf->ser[j].locationsNumber, conf->ser[j]);
        printf("\n-------------------------------------------------------------------\n");
    }
    // exit(1);
    return (conf);
}