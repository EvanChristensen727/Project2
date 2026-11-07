#include "Campus.cpp"
using namespace std;
int main(int argc, char* argv[]){
  Campus campus_map;
  

  string dataPath = "../data/";
  if (argc > 1){
    dataPath = argv[1];
  }

  campus_map.loadBuildings(dataPath);
  campus_map.loadConnections(dataPath);

  
  
  return 0;
}
