#ifndef FACILITY_H
#define FACILITY_H
    #include <string>
    #include <iostream>
    
    using namespace std;

    class Facility
    {
        public:
            //constructors
            Facility();
            Facility(string f, string n, string b, string c);
            //accessors
            string GetFacilityID();
            string GetFacilityName();
            string GetBuildingName();
            string GetCategory();
            //mutators, dont think they'll be used in the program tbh
            void SetFacilityID(string f);
            void SetFacilityName(string n);
            void SetBuildingName(string b);
            void SetCategory(string c);
            //print
            void Print();
        private:
            string facID, facName, bldngName, category;
    }; 

#endif