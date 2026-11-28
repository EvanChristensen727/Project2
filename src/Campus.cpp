#include "../include/Campus.h"

Campus::Campus(){
    paths = 0;
}

//Removes whitespace from the beginning and end of a string
std::string Campus::trimName(std::string name){
    std::string halfTrim = "";
    std::string fullTrim = "";
    std::string finalTrim = "";
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
    bool flag = false;
    for (char c : fullTrim){
        if (c == '\\'){
            flag = true;
            continue;
        }
        if (flag){
            flag = false;
            if (c=='r'){
                std::cout << "BREAKING NEWS";
                break;
            }
            finalTrim += '\\';
        }
        std::cout << c << std::endl;
        finalTrim += c;
    }

    return finalTrim;
    
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
//MUST BE LOADED BEFORE loadConnections()!!!
bool Campus::loadBuildings(std::string path){
    int rej = 0;
    path += "buildings.txt";
    std::ifstream input(path);

    if (!input.is_open()){
        std::cout << "File " << path << " cannot be opened" << std::endl;
        return false;
    }

    std::string line;
    std::getline(input, line);
    int i = 0;
    while (std::getline(input, line)){
        i++;
        //Ignore empty lines
        if (line.size() == 0){
            std::cout << "Line " << i << " of file " << path << " is empty" << std::endl;
            rej++;
            continue;
        }
        //Ignore comments in the data files
        if (line.at(0) == '#'){
            rej++;
            continue;
        }

        line = trimName(line);

        //Ignore duplicates
        std::list<std::string> plain;
        for (std::string x : buildings){
            plain.push_back(lowercase(x));
        }
        if (find(plain.begin(), plain.end(), lowercase(line)) != plain.end()){
            std::cout << "Line " << i << " of file " << path << " is a duplicate" << std::endl;
            rej++;
            continue;
        }

        
        connections[line];
        buildings.push_back(line);
        
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
        std::cout << "File " << path << " cannot be opened" << std::endl;
        return false;
    }
    if (buildings.size() == 0){
        std::cout << "Becuse buildings have not been loaded, connections will not attempt to load" << std::endl;
        return false;
    }
    
    int lineNum = 0;
    std::string line;
    while (std::getline(input, line)){
        lineNum += 1;
        
        //Ignore empty lines
        if (line.size() == 0){
            std::cout << "Line " << lineNum << " of file " << path << " is empty" << std::endl;
            rej++;
            continue;
        }

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
            
            if (i > 1){
                overflew = true;
                break;
            }
            data[i] += c;
        }

        //ignore too many arguments
        if (overflew){
            std::cout << "Line " << lineNum << " of file " << path << " has too many arguments" << std::endl;
            rej++;
            continue;
            
        }

        data[0] = trimName(data[0]);
        data[1] = trimName(data[1]);
        if (data[0] == data[1]){
            std::cout << "Line " << lineNum << " of file " << path << " is a self connection" << std::endl;
            rej++;
            continue;
        }
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

        

        
        connections[data[1]].push_back(data[0]);
        connections[data[0]].push_back(data[1]);
        paths += 1;

        
    }

    input.close();
    std::cout << "Finished loading \"" << path << "\" into buildings" << std::endl << "-" << lineNum - rej << " Files accepted, " << rej << " Rejected" << std::endl;
    return true;
}

//Prints the adjacency list in order of each being added, specifying if there are no connections
void Campus::printAdjacencyList(){
    if (buildings.size() == 0){
        std::cout << "There are no buildings" << std::endl;
        return;
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
    if (buildings.size() == 0){
        std::cout << "There are no buildings" << std::endl;
        return 0;
    }
    return connections.at(building).size();
}

//Prints the out-degree of each building
void Campus::printDegrees(){
    if (buildings.size() == 0){
        std::cout << "There are no buildings" << std::endl;
        return;
    }
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
    if (buildings.size() == 0){
        std::cout << "There are no buildings" << std::endl;
        return;
    }
    for (std::string x : buildings){
        std::cout << "-" << x << std::endl;
    }
}

//Runs a Breadth First Search from the input, printing out every reachable building and its distance form the input, as well as the input (at distance 0)
//Will cancel if the input does not match any element in buildings (case-insensitive, whitespace trimmed)
void Campus::printWalkability(std::string building){
    if (buildings.size() == 0){
        std::cout << "There are no buildings" << std::endl;
        return;
    }
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

void Campus::printShortestPath(std::string start, std::string end){
    std::string trimmedStart = lowercase(trimName(start));
    std::string trimmedEnd = lowercase(trimName(end));
    if ((buildings.size() == 1 && trimmedStart != trimmedEnd) || buildings.size() == 0){
        std::cout << "There are not enough buildings to run this BFS search" << std::endl;
        return;
    }
    if (trimmedEnd == trimmedStart){
        std::cout << "The shortest path from \"" << start << "\" to \"" << end << "\" has a distance of 0, as both locations are the same building" << std::endl;
        return;
    }
    std::unordered_map<std::string, std::pair<int, std::string>> buildings2;
    
    bool knownStart, knownEnd = false;
    std::string recognizedStart, recognizedEnd;
    for (std::string i : buildings){
        if (lowercase(i) == trimmedStart){
            buildings2[i] = {0, i};
            knownStart = true;
            recognizedStart = i;
            continue;
        }
        if (lowercase(i) == trimmedEnd){
            buildings2[i] = {-1, ""};
            knownEnd = true;
            recognizedEnd = i;
            continue;
        }
        buildings2[i] = {-1, ""};
    }

    if (!knownEnd || !knownStart){
        if (!knownStart){
            std::cout << "Starting building not recognized" << std::endl;
        }
        if (!knownEnd){
            std::cout << "Destination building not recognized" << std::endl;
        }
        return;
    }

    int distance = 0;
    std::queue<std::string> q;
    q.push(recognizedStart);

    while (!q.empty()){
        std::queue<std::string> tracking = q;
        q = std::queue<std::string>();

        while (!tracking.empty()){
            std::string i = tracking.front();
            for (std::string adj : connections.at(i)){
                if (buildings2.at(adj).first == -1){
                    q.push(adj);
                    buildings2.at(adj) = {distance + 1, i};
                }
            }
            tracking.pop();
        }
        distance++;
    }

    if (buildings2[recognizedEnd].first != -1){
        std::string prev = buildings2[recognizedEnd].second;
        std::stack<std::string> path;
        path.push(recognizedEnd);
        while (prev != recognizedStart){
            path.push(prev);
            prev = buildings2[prev].second;
        }
        path.push(recognizedStart);
        std::cout << "The shortest path from \"" << start << "\" to \"" << end << "\" has a distance of " << buildings2[recognizedEnd].first << " and can be traced by the following traversals:" << std::endl;
        while (path.size() != 1){
            std::cout << path.top() << " -> ";
            path.pop();
            std::cout << path.top() << std::endl;
        }
    }else{
        std::cout << "\"" << start << "\" is not connected to \"" << end << "\", no path exists" << std::endl;
        return;
    }


}


void Campus::printConnectivityReport(){
    if (buildings.size() == 0){
        std::cout << "There are no buildings" << std::endl;
        return;
    }
    std::cout << "Buildings: " << std::endl;
    printBuildings();
    std::cout << std::endl << "Paths: " << paths << std::endl << std::endl;
    int max = 0;
    std::list<std::string> highest;
    std::list<std::string> unconnected;
    for (std::string i : buildings){
        if (connections.at(i).size() == max){
            highest.push_back(i);
        }
        if (connections.at(i).size() > max){
            max = connections.at(i).size();
            highest = std::list<std::string>();
            highest.push_back(i);
        }
        if (connections.at(i).size() == 0){
            unconnected.push_back(i);
        }
    }
    std::cout << "The building(s) with the highest degree (" << max << ") is/are:" << std::endl;
    for (std::string i : highest){
        std::cout << "  -" << i << std::endl;
    }
    std::cout << std::endl;
    if (unconnected.size() == 0){
        std::cout << "There are no unconnected buildings" << std::endl;
    }
    else{
        std::cout << "The unconnected building(s) is/are:" << std::endl;
        for (std::string i : unconnected){
            std::cout << "  -" << i << std::endl;
        }
    }

    std::cout << "There are " << componentCount(std::unordered_map<std::string,bool>()) << " connected components in the graph" << std::endl;


   
}

int Campus::componentCount(std::unordered_map<std::string, bool> current){
    if (current.size() == 0){
        for (std::string build: buildings){
            current[build] = false;
        }
    }
    std::string start = "";
    bool incomplete = false;
    for (std::pair<std::string, bool> build : current){
        if (build.second == false){
            start = build.first;
            incomplete = true;
            break;
        }
    }

    if (!incomplete){
        return 0;
    }
    std::queue<std::string> q;
    q.push(start);
    current.at(start) = true;
    while (!q.empty()){
        std::queue<std::string> tracking = q;
        q = std::queue<std::string>();
        while (!tracking.empty()){
            std::string i = tracking.front();
            for (std::string adj : connections.at(i)){
                if (!current.at(adj)){
                    q.push(adj);
                    current.at(adj) = true;
                }
            }
            tracking.pop();
        }
    }
    return componentCount(current) + 1;
}