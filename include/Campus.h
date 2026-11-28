#ifndef CAMPUS_H

#define CAMPUS_H

#include <string>
#include <unordered_map>
#include <list>
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>
#include <stack>

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
        void printShortestPath(std::string start, std::string end);
        void printConnectivityReport();
        int componentCount(std::unordered_map<std::string, bool> current);
        static std::string trimName(std::string name);
        std::string lowercase(std::string upper);
        std::list<std::string> copyBuildings();
        static std::list<std::string> lineSplit(std::string initial);
        Campus();
        

    private:
        int paths;
        std::unordered_map<std::string, std::list<std::string>> connections;
        std::list<std::string> buildings;


};



#endif
