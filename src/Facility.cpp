#include "Facility.h"

//constructors
Facility::Facility()
{
    facID = "FacilityID";
    facName = "FacilityName";
    bldngName = "BuildingName";
    category = "Category";
}

Facility::Facility(string f, string n, string b, string c)
{
    //probs do a validity check before this
    facID = f;
    facName = n;
    bldngName = b;
    category = c;
}

//accessors
string Facility::GetFacilityID() {return facID;}
string Facility::GetFacilityName() {return facName;}
string Facility::GetBuildingName() {return bldngName;}
string Facility::GetCategory() {return category;}

//useless mutators again
void Facility::SetFacilityID(string f) {facID = f;}
void Facility::SetFacilityName(string n) {facName = n;}
void Facility::SetBuildingName(string b) {bldngName = b;}
void Facility::SetCategory(string c) {category = c;}

//print
void Facility::Print()
{
    cout << facID << " | " << facName << " | " << bldngName << " | " << category << endl;
}