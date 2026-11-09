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
                    (*it).Print();
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
    if (!DataInTable(d.GetFacilityID(), true, false) && index != -1) //if the data is not in the table (count collisions), then add it
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
        if (!table.at(i).empty())
        {
            for (list<Facility>::iterator it = table.at(i).begin(); it != table.at(i).end(); it++)
            {
                (*it).Print();
            }
        }
        cout << endl;
    }
    //cout << "Collisions: " << collisions << endl;
}

//taken from campus to make life easier for me
string FacilityHashTable::StrTrim(string name)
{
    string halfTrim = "";
    string fullTrim = "";

    //starting trim
    bool start = false;
    for (char c : name)
    {
        if (!start)
        {
            if (!start && c != ' ')
            {
                halfTrim += c;
                start = true;
            }
        }
        else
        {
            halfTrim += c;
        }
    }

    //ending trim
    std::string heldSpace = "";
    for (char c : halfTrim)
    {
        if (c == ' ')
        {
            heldSpace += c;
        }
        else
        {
            fullTrim += heldSpace + c;
            heldSpace = "";
        }
    }
   
    return fullTrim;
}

bool FacilityHashTable::LoadFacilities(string fileName)
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
		line = StrTrim(line);
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
			getline(ss, c);
			f = StrTrim(f);
			n = StrTrim(n);
            b = StrTrim(b);
            c = StrTrim(c);
            
			if (f.empty() || n.empty() || b.empty() || c.empty())
            {
				std::cout << "WARNING " << fileName << " at " << counter << " has empty fields." << std::endl;
				rejected++;
				continue;
			}
			if(c.find('|') != std::string::npos)
            {
				std::cout << "WARNING! " << fileName << " at " << counter << " contains too many fields." << std::endl;
				rejected++;
				continue;
			}
			if (HashFunc(f) == -1)
            {
				cout << "WARNING! " << fileName << " at " << counter << " has invalid FacilityID." << endl;
                rejected++;
				continue;
			}
			if(!DataInTable(f, false, false))
            {
                Facilty fac(f,n,b,c);
                AddData(fac);
				accepted++;
			}
			else
            {
				rejected++;
				if (DataInTable(f, false, false))
                {
					std::cout << "WARNING! " << fileName << " at " << counter << " duplicate facility ID" << std::endl;
				}
				else
                {
					std::cout << "WARNING! " << fileName << " at " << counter << " Unknown Error" << std::endl;
				}
			}
            
		}
	}

	cout << "Facilities loaded: " << accepted << endl;
	cout << "Facilities rejected: " << rejected << endl;

	return true;
}