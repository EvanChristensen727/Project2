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
  cout << endl;
  string choice = "0";
  
  while (stoi(choice) != 10){
    cout << endl << "Please choose an option from the directory: \n1) View all facilities\n2) Search facilities by ID \n3) View campus graph \n4) Display graph counts and degrees \n5) Find reachable buildings (BFS)" <<endl;
    cout << "6) Add department \n7) Search department \n8) Display department hierarchy \n9) Run preorder traversal \n10) Exit\n\n";
    getline(cin, choice);
    cout << endl;
    switch(stoi(choice)){
      default:
        cout << "Command not recognized, please try again";
        break;
      case 1:
        //View all Facilities
        break;
      case 2:
        //Search facilities by ID
        break;
      case 3:
        //View Campus Graph
        campus_map.printAdjacencyList();
        break;
      case 4:
        //Display graph counts and degrees
        cout << "Number of paths: " << campus_map.getPaths() << endl;
        cout << "Number of buildings: " << campus_map.copyBuildings().size() << endl;
        cout << "Degrees: " << endl;
        campus_map.printDegrees();
        break;
      case 5:
        //Find Reachable buildings (BFS)
        {
          string building;
          cout << "Enter a building to search for other reachable buildings: ";
          getline(cin, building);
          campus_map.printWalkability(building);

        }  
        break;
      case 6:
        //Add department
        break;
      case 7:
        //Search department
        break;
      case 8:
        //Display department Hierarchy
        break;
      case 9:
        //Run preorder traversal
        break;
      case 10:
        //exit
        break;
    }
  }
  return 0;
}
