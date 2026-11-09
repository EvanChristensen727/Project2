#include "../include/FacilityHashTable.h"
#include <fstream>
#include <sstream>

FacilityHashTable::FacilityHashTable()
{
    table.resize(HASHTABLE_SIZE);
    collisions = 0;
}

int FacilityHashTable::HashFunc(string s) //done
{
    //length check at start to ensure no index OoB
    if ((s.length() != 4) || (toupper(s.at(0)) != 'F') || !isdigit(s.at(1)) || !isdigit(s.at(2)) || !isdigit(s.at(3)))
    {
        return -1;
    }
    //get value to hash
    int val = toupper(s.at(0));
    val += stoi(s.substr(1,3));
    //hash it
    int index = val % HASHTABLE_SIZE;
    return index;
}

bool FacilityHashTable::DataInTable(string f, bool c, bool m) //done
{
    //straight up reused code from an old AddData cut down.
    int index = HashFunc(f); 
    bool equal;
    int count = 0;

    if (index == -1)
    {
        cout << "Invalid Facility ID" << endl;
        return false;
    }
    
    if ( table.at(index).empty() )
    {
        if (m)
        {
            cout << "ID Not Found" << endl;
        }
        return false; //end here
    }

    
    for (list<Facility>::iterator it = table.at(index).begin(); it != table.at(index).end(); it++)
    {
        if (c)
        {
            count++;
        }
        
        if ((*it).GetFacilityID().length() == f.length()) //save some time doing comparisons
        {
            equal = true;
            for (int i = 0; i < (*it).GetFacilityID().length(); i++)
            {
                if (toupper((*it).GetFacilityID()[i]) != toupper(f[i]))
                {
                    equal = false;
                    break; //saves more time on comparisons
                }
            }
            if (equal)
            {
                if (m)
                {
                    cout << "ID Found" << endl;
                }
                return true;
            }
        }
    }
    if (m)
    {
        cout << "ID Not Found" << endl;
    }
    collisions += count; //because if we are counting collisions, we should reach this area to confirm that we are adding a new id
    return false;
}

void FacilityHashTable::AddData(Facility d) //done
{
    int index = HashFunc(d.GetFacilityID());
    bool equal;
    if (!DataInTable(d.GetFacilityID(), true, false)) //if the data is not in the table (count collisions), then add it
    {
        table.at(index).push_back(d);
        cout << "\"" << d.GetFacilityID() << "\" added to hash table at index " << index << endl;
        return; //end here
    }
    cout << "ERROR: " << d.GetFacilityID() << " already exists in this hash table." << endl;
    return;
}

void FacilityHashTable::PrintTable() //done
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {   
        cout << "Bucket " << i << ":\n"; 
        if (table.at(i).empty())
        {
            cout << "\tEMPTY" << endl;
        }
        else
        {
            for (list<Facility>::iterator it = table.at(i).begin(); it != table.at(i).end(); it++)
            {
                cout << "\t";
                (*it).Print();
            }
        }
        cout << endl;
    }
    cout << "Collisions: " << collisions << endl;
}

bool FacilityHashTable::ReadFacilities(string fileName)
{
    ifstream inputFile; //reusing some stuff from a teammate, thank you Blair <3
	string line;
    int counter = 0;
    int accepted = 0;
    int rejected = 0;

    inputFile.open(fileName);

    if(!inputFile.is_open())
    {
		cout << fileName << " failed to open!" << endl;
		return false;
	}

    while(getline(inputFile, line))
    {
		string f, n, b, c; //facilityID, facility name, building, category
		//line = Campus::trimName(line);
		stringstream ss(line);
		counter++;

		if (line.empty() || line[0] == '#')
        {
			continue;
		}
		else
        {
			if(line.find('|') == std::string::npos)
            {
				std::cout << "WARNING! " << fileName << " at " << counter << " too few fields." <<std::endl;
				rejected++;
				continue;
			}

			getline(ss, f, '|');
            getline(ss, n, '|');
            getline(ss, b, '|');
			getline(ss, s);
			//departmentName = Campus::trimName(departmentName);
			//parentName = Campus::trimName(parentName);
            /*
			if (departmentName.empty() || parentName.empty())
            {
				std::cout << "WARNING " << fileName << " at " << counter << " has empty fields." << std::endl;
				rejected++;
				continue;
			}
			if(parentName.find('|') != std::string::npos)
            {
				std::cout << "WARNING! " << fileName << " at " << counter << " contains too many fields." << std::endl;
				rejected++;
				continue;
			}
			if (root == nullptr)
            {
				if (lowerCase(parentName) != "none"){
					std::cout << "WARNING: " << fileName <<" Root parent must be NONE at: " << counter << std::endl;
					rejected++;
					continue;
				}
			}
			else if(lowerCase(parentName) == "none")
            {
				std::cout << "WARNING:" << fileName << " another root is not allowed at: " << counter << std::endl;
				rejected++;
				continue;
			}
			if(addDepartment(departmentName, parentName))
            {
				accepted++;
			}
			else
            {
				rejected++;
				if (SearchTree(departmentName))
                {
					std::cout << "Warning! " << fileName << " at " << counter << " duplicate department" << std::endl;
				}
				else
                {
					std::cout << "Warning! " << fileName << " at " << counter << " Unknown parent: " << parentName << std::endl;
				}
			}
            */
		}
	}

	cout << "Facilities loaded: " << accepted << endl;
	cout << "Facilities rejected: " << rejected << endl;

	return true;
}