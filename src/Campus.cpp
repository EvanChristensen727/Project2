#include "../include/Campus.h"


bool Campus::loadBuildings(std::string path){
    std::ifstream input(path);

    if (!input.is_open()){
        return false;
    }

    std::string line;
    std::getline(input, line);
    while (std::getline(input, line)){
        connections[line];
    }

    input.close();

    return true;
}    

bool Campus::loadConnections(std::string path){
    std::ifstream input(path);

    if (!input.is_open()){
        return false;
    }

    std::string line;
    std::getline(input, line);
    while (std::getline(input, line)){
        int i = 0;
        std::string data[2];
        for (char c : line){
            if (c == '|'){
                i++;
                continue;
            }
                data[i] += c;
            }
        connections[data[0]].push_back(data[1]);
    }

    input.close();

    return true;
}

void Campus::printAdjacencyList(){
    
    for (auto x = connections.begin(); x != connections.end(); x++){
        std::cout << "*" << x->first << ":" << std::endl;
        if (x->second.size() == 0){
                std::cout << "    -No paths " << std::endl;
            }
        for (std::string y : x -> second){
            std::cout << "    -" << y << std::endl;
        }
    }
}


