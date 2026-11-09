#include "../include/Campus.h"


//Removes whitespace from the beginning and end of a string
std::string Campus::trimName(std::string name){
    std::string halfTrim = "";
    std::string fullTrim = "";
    //starting trim
    bool start = false;
    for (char c : name){
        if (!start){
            if (!start && c != ' '){
                halfTrim += c;
                start = true;
            }
        }else{
            halfTrim += c;
        }
    }

    //ending trim
    std::string heldSpace = "";
    for (char c : halfTrim){
        if (c == ' '){
            heldSpace += c;
        }
        else {
            fullTrim += heldSpace + c;
            heldSpace = "";
        }
    }
   
    return fullTrim;
    
}

//Converts a string so that all characters are lowercase
std::string Campus::lowercase(std::string upper){
    std::string rebuild = "";
    for (char c : upper){
        rebuild += std::tolower(c);
    }
    return rebuild;
}

//Loads buildings.txt from the folder "path" into the buildings list, filtering out any incorrect lines
bool Campus::loadBuildings(std::string path){
    int rej = 0;
    path += "buildings.txt";
    std::ifstream input(path);

    if (!input.is_open()){
        std::cout << "File " << path << " cannot be opened";
        return false;
    }

    std::string line;
    std::getline(input, line);
    int i = 1;
    while (std::getline(input, line)){
        //Ignore comments in the data files
        if (line.at(0) == '#'){
            rej++;
            continue;
        }

        line = trimName(line);

        //Ignore duplicates
        if (find(buildings.begin(), buildings.end(), line) != buildings.end()){
            std::cout << "Line " << i << " of file " << path << " is a duplicate" << std::endl;
            rej++;
            continue;
        }

        //Ignore empty lines
        if (line.empty()){
            std::cout << "Line " << i << " of file " << path << " is empty" << std::endl;
            rej++;
            continue;
        }

        connections[line];
        buildings.push_back(line);
        i++;
    }

    input.close();

    std::cout << "Finished loading \"" << path << "\" into buildings" << std::endl << "-" << i - rej << " Files accepted, " << rej << " Rejected" << std::endl;
    return true;
}    

//Loads connections.txt from the folder "path" into the connection undirected map to create an adjacency list, filtering out any incorrect lines
bool Campus::loadConnections(std::string path){
    path += "connections.txt";
    std::ifstream input(path);
    int rej = 0;
    if (!input.is_open()){
        std::cout << "File " << path << " cannot be opened";
        return false;
    }

    int lineNum = 1;
    std::string line;
    while (std::getline(input, line)){

        //Ignore comments in the data files
        if (line.at(0) == '#'){
            continue;
        }

        int i = 0;
        std::string data[2];
        bool overflew = false;
        for (char c : line){
            if (c == '|'){
                i++;
                continue;
            }

            data[i] += c;
            if (i > 1){
                overflew = true;
                break;
            }
        }

        //ignore too many arguments
        if (overflew){
            std::cout << "Line " << lineNum << " of file " << path << " has too many arguments" << std::endl;
            rej++;
            continue;
            
        }

        data[0] = trimName(data[0]);
        data[1] = trimName(data[1]);

        //Ignore duplicates
        if (find(connections.at(data[0]).begin(), connections.at(data[0]).end(), data[1]) != connections.at(data[0]).end()){
            std::cout << "Line " << lineNum << " of file " << path << " is a duplicate" << std::endl;
            rej++;
            continue;
        }

        //ignore undefined buildings
        if (find(buildings.begin(), buildings.end(), data[1]) == buildings.end() || find(buildings.begin(), buildings.end(), data[0]) == buildings.end()){
            std::cout << "Line " << lineNum << " of file " << path << " has an argument which has not yet been loaded" << std::endl;
            rej++;
            continue;
        }

        //Ignore empty lines
        if (line.empty()){
            std::cout << "Line " << lineNum << " of file " << path << " is empty" << std::endl;
            rej++;
            continue;
        }

        
        connections[data[1]].push_back(data[0]);
        connections[data[0]].push_back(data[1]);
        paths += 1;

        lineNum += 1;
    }

    input.close();
    std::cout << "Finished loading \"" << path << "\" into buildings" << std::endl << "-" << lineNum - rej << " Files accepted, " << rej << " Rejected" << std::endl;
    return true;
}

//Prints the adjacency list in order of each being added, specifying if there are no connections
void Campus::printAdjacencyList(){
    if (buildings.size() == 0){
        std::cout << "There are no buildings" << std::endl;
    }
    for (std::string x : buildings){
        std::cout << "-" << x << ":" << std::endl;
        if (connections.at(x).size() == 0){
                std::cout << "    (no connections)" << std::endl;
            }
        for (std::string y : connections.at(x)){
            std::cout << "    -" << y << std::endl;
        }
    }
}

//Returns the out-degree of input
int Campus::getDegree(std::string building){
    return connections.at(building).size();
}

//Prints the out-degree of each building
void Campus::printDegrees(){
    for (std::string x : buildings){
        std::cout << "-" << x << ": " << getDegree(x) << std::endl;
    }
}

//Returns the number of paths in connections
int Campus::getPaths(){
    return paths;
}

//Prints the name of each building in buildings
void Campus::printBuildings(){
    for (std::string x : buildings){
        std::cout << "-" << x << std::endl;
    }
}

//Runs a Breadth First Search from the input, printing out every reachable building and its distance form the input, as well as the input (at distance 0)
//Will cancel if the input does not match any element in buildings (case-insensitive, whitespace trimmed)
void Campus::printWalkability(std::string building){
    std::unordered_map<std::string, std::pair<int, bool>> buildings2;
    std::string trimmedBuilding = lowercase(trimName(building));
    bool known = false;
    std::string recognized;
    for (std::string i : buildings){
        if (lowercase(i) == trimmedBuilding){
            buildings2[i] = {0, true};
            known = true;
            recognized = i;
            continue;
        }
        buildings2[i] = {0, false};

    }

    if (!known){
        std::cout << "Starting building not recognized" << std::endl;
        return;
    }

    int distance = 0;

    std::queue<std::string> q;
    std::queue<std::string> total;
    q.push(recognized);
    total.push(recognized);
    while (!q.empty()){
        std::queue<std::string> tracking = q;
        q = std::queue<std::string>();

        while (!tracking.empty()){
            std::string i = tracking.front();
            for (std::string adj : connections.at(i)){
                if (!buildings2.at(adj).second){
                    q.push(adj);
                    buildings2.at(adj) = {distance + 1, true};
                    total.push(adj);
                }
            }
            tracking.pop();
        }
        distance++;
    }
    while (!total.empty()){
        std::cout << "-" << total.front() << ", distance: " << buildings2.at(total.front()).first << std::endl;
        total.pop();
    }

}


//Returns a deep copy of buildings
std::list<std::string> Campus::copyBuildings(){
    std::list<std::string> copy;
    for (std::string x : buildings){
        copy.push_back(x);
    }
    return copy;
}
