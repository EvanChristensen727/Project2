#include "Campus.cpp"
using namespace std;
int main(){
  Campus campus_map;
  
  campus_map.loadBuildings();
  campus_map.loadConnections();

  campus_map.printAdjacencyList();
  
  return 0;
}
