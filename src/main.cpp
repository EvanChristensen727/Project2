#include "../include/Campus.h"
#include "../include/DepartmentTree.h"
#include "../include/DepartmentNode.h"
#include "../include/FacilityHashTable.h"
using namespace std;
int main(int argc, char* argv[]){
  Campus campus_map;
  DepartmentTree department;
  FacilityHashTable facilities;
  //Logic for handling the command line argument for the data path
  string dataPath = "../data/";
  if (argc > 1){
    dataPath = argv[1];
  }

  campus_map.loadBuildings(dataPath);
  campus_map.loadConnections(dataPath);
  department.loadDepartment(dataPath + "departments.txt");
  facilities.LoadBuildings(campus_map.copyBuildings()); //take the buildings that have been loaded in from line 16 <3
  facilities.LoadFacilities(dataPath + "facilities.txt");

  cout << endl;
  string choice = "0";
  int num = 439;
  while (num != 0 && num != 18){

    cout << endl << "Please choose an option from the directory: \n1) View all facilities\n2) Search facility by ID \n3) Search facility by name \n4) Search facility by category \n5) View campus graph \n6) Display graph counts and degrees" << endl;
    cout << "7) Find reachable buildings (BFS) \n8) Find shortest path (BFS) \n9) Add department \n10) Search Department \n11) Display department hierarchy \n12) Preorder traversal \n";
    cout << "13) Postorder traversal \n14) Level-order traversal \n15) Department statistics \n16) Facility category report \n17) Graph connectivity report \n18) Exit\n";
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
        facilities.PrintTable();
        break;
      case 2:
        //Search facilities by ID
        {
        string fId;
        cout << "Enter facility ID (F followed by 3 numbers):";
        getline(cin, fId);
        facilities.DataInTable(fId, false, true);
        }
        break;
      case 3:
        //Search Facility by name
        break;
      case 4:
        //Search facility by category
      case 5:
        //View Campus Graph
        campus_map.printAdjacencyList();
        break;
      case 6:
        //Display graph counts and degrees
        cout << "Number of paths: " << campus_map.getPaths() << endl;
        cout << "Number of buildings: " << campus_map.copyBuildings().size() << endl;
        cout << "Degrees: " << endl;
        campus_map.printDegrees();
        break;
      case 7:
        //Find Reachable buildings (BFS)
        {
          string building;
          cout << "Enter a building to search for other reachable buildings: ";
          getline(cin, building);
          campus_map.printWalkability(building);

        }  
        break;
      case 8:
        //Find shortest path (BFS)
        {
          string start, end;
          cout << "Enter the starting building: ";
          getline(cin, start);
          cout << "Enter the destination building: ";
          getline(cin, end);
          cout << endl;
          campus_map.printShortestPath(start, end);

        }  
        break;
      case 9:{
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
      case 10:{
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
      case 11:
	department.displayHierarchy();
        //Display department Hierarchy
        break;
      case 12:
        //Run preorder traversal
	department.preorderTraversal();
        break;
      case 13:
       //Run postorder traversal
        break;
      case 14:
        //Level order traversal
        break;
      case 15:
        //Department Statistics
        break;
      case 16:
        //Facility Category Report
        break;
      case 17:
        //Graph connectivity report
        campus_map.printConnectivityReport();
        break;
      case 18:
        //exit
        break;
      case 0:
        //second exit? It was mentioned in the rubric, so I'm not taking chances
        break;
    }
  }
  return 0;
}
