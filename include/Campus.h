#ifndef CAMPUS_H

#define CAMPUS_H

#include <string>
#include <unordered_map>
#include <list>
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>

class Campus{
    public:
        bool loadBuildings(std::string path);
        bool loadConnections(std::string path);
        void printAdjacencyList();
        void printDegrees();
        int getDegree(std::string building);
        int getPaths();
        void printBuildings();
        void printWalkability(std::string building);
        std::string trimName(std::string name);
        std::string lowercase(std::string upper);

    private:
        int paths;
        std::unordered_map<std::string, std::list<std::string>> connections;
        std::list<std::string> buildings;


};



#endif