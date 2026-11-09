#include "FacilityHashTable.h"

FacilityHashTable::FacilityHashTable()
{
    table.resize(HASHTABLE_SIZE);
    collisions = 0;
}

int FacilityHashTable::HashFunc(string s) //done
{
    //get value to hash
    int val = toupper(s.at(0));
    val += stoi(s.substr(1,3));
    //hash it
    int index = val % HASHTABLE_SIZE;
    return index;
}

bool FacilityHashTable::DataInTable(string f, bool c) //done
{
    //straight up reused code from an old AddData cut down.
    int index = HashFunc(f); 
    bool equal;

    if ( table.at(index).empty() )
    {
        return false; //end here
    }

    
    for (list<Facility>::iterator it = table.at(index).begin(); it != table.at(index).end(); it++)
    {
        if (c)
        {
            collisions++;
        }
        
        if (*it.GetFacilityID.length() == f.length()) //save some time doing comparisons
        {
            equal = true;
            for (int i = 0; i < *it.GetFacilityID.length(); i++)
            {
                if (toupper(*it.GetFacilityID[i]) != toupper(d[i]))
                {
                    equal = false;
                    break; //saves more time on comparisons
                }
            }
            if (equal)
            {
                return true;
            }
        }
    }
    return false;
}

void FacilityHashTable::AddData(Facility d) //done
{
    int index = HashFunc(d.GetFacilityID);
    bool equal;
    if (!DataInTable(d.GetFacilityID, true)) //if the data is not in the table (count collisions), then add it
    {
        table.at(index).push_back(d);
        cout << "\"" << d.GetFacilityID << "\" added to hash table at index " << index << endl;
        return; //end here
    }
    cout << "ERROR: " << d.GetFacilityID << " already exists in this hash table." << endl;
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
            for (list<Facility>::iterator it = table.at(index).begin(); it != table.at(index).end(); it++)
                cout << "\t" << *it.Print() << endl;
        }
        cout << endl;
    }
    cout << "Collisions: " << collisions << endl;
}