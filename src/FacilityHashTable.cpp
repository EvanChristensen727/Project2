#include "../include/FacilityHashTable.h"

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

    if (index = -1)
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
            collisions++;
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