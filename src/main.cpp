#include "../include/Campus.h"
#include "../include/DepartmentTree.h"
#include "../include/DepartmentNode.h"
using namespace std;
int main(int argc, char* argv[]){
  Campus campus_map;
  DepartmentTree department;
  //Logic for handling the command line argument for the data path
  string dataPath = "../data/";
  if (argc > 1){
    dataPath = argv[1];
  }

  campus_map.loadBuildings(dataPath);
  campus_map.loadConnections(dataPath);
  department.loadDepartment(dataPath + "departments.txt");

  cout << endl;
  string choice = "0";
  int num = 439;
  while (num != 0 && num != 10){

    cout << endl << "Please choose an option from the directory: \n1) View all facilities\n2) Search facilities by ID \n3) View campus graph \n4) Display graph counts and degrees \n5) Find reachable buildings (BFS)" <<endl;
    cout << "6) Add department \n7) Search department \n8) Display department hierarchy \n9) Run preorder traversal \n10) Exit\n\n";
    getline(cin, choice);
    cout << endl;
    try
    {
      num = stoi(choice);
    }
    catch(exception e)
    {
      cout << "Please select a valid option\n";
      continue;
    }
    
    switch(num){
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
      case 6:{
		string departmentName, parentName;
		
		cout << "Enter department name: ";
		getline(cin, departmentName);
	     
		if (!department.isEmpty()) {
			cout << "Enter parent department: ";
			getline(cin, parentName);
		}
		else{
			parentName = "NONE";
		}
		if(department.addDepartment(departmentName, parentName)){
			cout << "success" << endl;
	     	}
		else{
			cout << "failed to add department" << endl;
		}
		break;
	}
        //Add department
        break;
      case 7:{
		string departmentName;
		cout << "Enter department name to search: ";
		getline(cin, departmentName);
		DepartmentNode* result = department.SearchTree(departmentName);
		if(result != nullptr){
			department.displayDepartment(result);
			break;
		}
		else{
			cout << "No department found!" << endl;
			break;
		}
	     }
        //Search department
        break;
      case 8:
	department.displayHierarchy();
        //Display department Hierarchy
        break;
      case 9:
        //Run preorder traversal
	department.preorderTraversal();
        break;
      case 10:
        //exit
        break;
      case 0:
        //second exit? It was mentioned in the rubric, so I'm not taking chances
        break;
    }
  }
  return 0;
}
