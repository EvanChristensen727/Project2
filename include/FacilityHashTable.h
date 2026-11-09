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
            int HashFunc(string s);             // hash function for input string
            bool DataInTable(string f, bool c, bool m); // f is facID to search for, c is if collisions are to be counted, m controls if messages should be printed
            void AddData(Facility d);           // d is data to add
            void PrintTable();                  // more of a "verify it worked" thing rn
            bool ReadFacilities(string fileName);
        private:
            vector<list<Facility>> table;
            int collisions;
    };


#endif
