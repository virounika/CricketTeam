#include "CricketTeam.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    CricketTeam cricketers;
      cricketers.addCricketer("Sachin", "Tendulkar", 100);
      cricketers.addCricketer("Virat", "Kohli", 120);
      cricketers.addCricketer("Rahul", "Dravid", 90);

       // Test with a valid position
       std::string firstName, lastName;
       CricketType value;
       bool found = cricketers.checkTeamForCricketer(1, firstName, lastName, value);
       assert(found);
       assert(firstName == "Virat");
       assert(lastName == "Kohli");
       assert(value == 120);

       // Test with the first position
       found = cricketers.checkTeamForCricketer(0, firstName, lastName, value);
       assert(found);
       assert(firstName == "Rahul");
       assert(lastName == "Dravid");
       assert(value == 90);

       // Test with the last position
       int lastPosition = cricketers.cricketerCount() - 1;
       found = cricketers.checkTeamForCricketer(lastPosition, firstName, lastName, value);
       assert(found);
       assert(firstName == "Sachin");
       assert(lastName == "Tendulkar");
       assert(value == 100);

       // Test with an invalid position (out of bounds)
       found = cricketers.checkTeamForCricketer(3, firstName, lastName, value);
       assert(!found);

       // Test with an empty team
       CricketTeam emptyTeam;
       found = emptyTeam.checkTeamForCricketer(0, firstName, lastName, value);
       assert(!found);


    cout << "Passed all tests" << endl;
    return 0;
}
