#ifndef FACILITY_HASHTABLE_H
#define FACILITY_HASHTABLE_H

    #include <iostream>
    #include <vector>
    #include <list>
    #include "Facility.h"
    #include <cctype>

    const int HASHTABLE_SIZE = 50;
    using namespace std;

    class FacilityHashTable
    {
        public:
            FacilityHashTable();
            int HashFunc(string s);                     // hash function for input string
            bool DataInTable(string f, bool c, bool m); // f is facID to search for, c is if collisions are to be counted, m controls if messages should be printed
            void AddData(Facility d);                   // d is data to add
            void PrintTable();                          // more of a "verify it worked" thing rn
            string StrTrim(string name);                // function taken from campus to make ReadFacilities easier
            bool LoadFacilities(string fileName);       // read facilities into hashmap from file
            bool CheckBuildings(string bld);            // check if building exists
            void LoadBuildings(list<string> l);         // read buildings from a pre-existing list of strings
        private:
            vector<list<Facility>> table;
            int collisions;
            list<string> buildings;                     // list of buildings taken from Campus, makes sure that building actually exists.
    };


#endif
