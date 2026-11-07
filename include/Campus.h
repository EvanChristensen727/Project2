#ifndef CAMPUS_H

#define CAMPUS_H

#include <string>
#include <unordered_map>
#include <list>
#include <fstream>
#include <iostream>

class Campus{
    public:
        bool loadBuildings(std::string path = "../data/buildings.txt");
        bool loadConnections(std::string path = "../data/connections.txt");
        void printAdjacencyList();

    private:
        std::unordered_map<std::string, std::list<std::string>> connections;


};



#endif