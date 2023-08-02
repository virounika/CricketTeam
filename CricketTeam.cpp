//  CricketTeam.cpp

#include "CricketTeam.h"
#include <iostream>
using namespace std;

// Create an empty CricketTeam list: constructor
CricketTeam::CricketTeam(): head(nullptr), tail(nullptr), count(0) {
}

// Destructor, should destroy all nodes on a CricketTeam
CricketTeam::~CricketTeam() {
    Node* current = head;
    while (current != nullptr)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

// copy constructor
// other is the one being copied
CricketTeam::CricketTeam(const CricketTeam& other) {
    head = nullptr;
    tail = nullptr;
    count = 0;
    Node* current = other.head;
    while (current != nullptr) {
        addCricketer(current->firstName, current->lastName, current->value);
        current = current->next;
    }
}

// Assignment operator
const CricketTeam& CricketTeam::operator=(const CricketTeam& other) {
    if (this == &other)
    return *this;
    
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current->next;
        delete current;
        current = temp;
    }
    head = tail = nullptr;
    count = 0;
    
    current = other.head;
    while (current != nullptr) {
        addCricketer(current->firstName, current->lastName, current->value);
        current = current->next;
    }
    return *this;
}

// Return true if the CricketTeam list is empty, otherwise false.
bool CricketTeam::noTeam() const {
    if (head == nullptr)
        return true;
    else
        return false;
}

// Return the number of matches (players) on the CricketTeam list.
int CricketTeam::cricketerCount() const {
    return count;
}

// If the full name (both the first and last name) is not equal
// to any full name currently in the list then add it and return
// true. Elements should be added according to their last name.
// Elements with the same last name should be added according to
// their first names. Otherwise, make no change to the list and
// return false (indicating that the name is already in the
// list).
bool CricketTeam::addCricketer(const std::string& firstName, const std::string& lastName, const CricketType& value) {
    // check if full name is already on the team
    Node* current = head;           // tracking current cricketer
    while (current != nullptr) {
        if (current->firstName == firstName && current->lastName == lastName) {
            return false;
        } else
            current = current->next;
    }
    
    Node* newNode = new Node;
    newNode->firstName = firstName;
    newNode->lastName = lastName;
    newNode->value = value;
    
    if (noTeam()) {
        head = newNode;
        tail = newNode;
    } else {
        current = head;
        while (current != nullptr) {
            // find correct position
            if (current->lastName > newNode->lastName ||
                (current->lastName == newNode->lastName && current->firstName > newNode->firstName))
                break; // position found
            else
                current = current->next; // if end is reached, current will be nullptr
        }
        // inserting at the end
        if (current == nullptr) {
            newNode->prev = tail;   // tail used to point to final Node
            tail->next = newNode;   // previous final Node points to newNode
            tail = newNode;         // tail points to last node
        }
        else {
        // inserting newNode before current: nodeA   newNode  current
            newNode->prev = current->prev;
            newNode->next = current;
            if (current->prev != nullptr) { // if current is not the first
                current->prev->next = newNode;  // links current's old prev to newNode
            }
            else {
                head = newNode; // if inserted to beginning
            }
            current->prev = newNode;
        }
    }
    count++;
    return true;
}

// If the full name is equal to a full name currently in the
// list, then make that full name no longer map to the value it
// currently maps to, but instead map to the value of the third
// parameter; return true in this case. Otherwise, make no
// change to the list and return false.
bool CricketTeam::substituteCricketer(const std::string& firstName, const std::string& lastName, const CricketType & value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->firstName == firstName && current->lastName == lastName) {
            current->value = value;
            return true;
        } else
        current = current->next;    // continue checking
    }
    return false;
}

// If full name is equal to a name currently in the list, then
// make that full name no longer map to the value it currently
// maps to, but instead map to the value of the third parameter;
// return true in this case. If the full name is not equal to
// any full name currently in the list then add it and return
// true. In fact, this function always returns true.
bool CricketTeam::addOrSubstitute(const std::string& firstName, const std::string& lastName, const CricketType& value) {
    if (substituteCricketer(firstName, lastName, value)) {
        return true; // substitution worked
    }
    else return addCricketer(firstName, lastName, value); // substitution failed -> addCricketer evalutes to true
}

// If the full name is equal to a full name currently in the
// list, remove the full name and value from the list and return
// true. Otherwise, make no change to the list and return
// false.
bool CricketTeam::releaseCricketer(const std::string& firstName, const std::string& lastName) {
    Node* current = head;
    while (current != nullptr) {
        if (current->firstName == firstName && current->lastName == lastName) {
            // Check if the cricketer is the head or tail node
            if (current == head) {
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                } else {
                    tail = nullptr;
                }
            } else if (current == tail) {
                tail = current->prev;
                tail->next = nullptr;
            } else {
                // Cricketer is in the middle of the list
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            count--;
            return true;
        }

        current = current->next; // cricketer not found yet
    }

    return false; // Cricketer not found
}

// Return true if the full name is equal to a full name
// currently in the list, otherwise false.
bool CricketTeam::rosteredOnCricketTeam(const std::string& firstName, const std::string& lastName) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->firstName == firstName && current->lastName == lastName) {
            return true;
        }
        else
            current = current->next;
    }
    return false;
}
 
// If the full name is equal to a full name currently in the
// list, set value to the value in the list that that full name
// maps to, and return true. Otherwise, make no change to the
// value parameter of this function and return false.
bool CricketTeam::searchForCricketer(const std::string& firstName, const std::string& lastName, CricketType& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->firstName == firstName && current->lastName == lastName) {
            value = current->value ; // setting value
            return true;
        }
        else
            current = current->next;
    }
    return false;   // no match found
}

// If 0 <= i < size(), copy into firstName, lastName and value
// parameters the corresponding information of the element at
// position i in the list and return true. Otherwise, leave the
// parameters unchanged and return false. (See below for details
// about this function.)
bool CricketTeam::checkTeamForCricketer(int i, std::string& firstName, std::string& lastName, CricketType & value) const {
    if (i < 0 || i >= count)
        return false;
    Node* current = head;
    // i is the index of node we want
        for (int pos = 0; pos < i; pos++) {
        current = current->next;    // advancing current until reaches i
    }
    firstName = current->firstName;
    lastName = current->lastName;
    value = current->value;
    return true;
}

// Exchange the contents of this list with the other one.
void CricketTeam::tradeCricketTeams(CricketTeam& other) {
    Node* tempHead = head; // storing original team's head ptr
    Node* tempTail = tail;  // storing original team's tail ptr
    int tempCount = count;  // storing original team's # of players
    
    head = other.head;
    tail = other.tail;
    count = other.count;
    
    other.head = tempHead;
    other.tail = tempTail;
    other.count = tempCount;
}

// if a full name appears in only odOne or odTwo, odJoined must contain that element
//   if a name appears in both with the same values, it will appear
// if a name appears in both with different values, function returns false
// if odJoined is empty good, odJoined can be equal to odOne or odTwo, could already have values
bool mergeCricketers(const CricketTeam& odOne, const CricketTeam& odTwo, CricketTeam& odJoined) {
    if (&odOne == &odTwo) {
        odJoined = odTwo; // ao called
        return true;
    }
    bool result = true; // only set to false if merge fails on one match
    CricketTeam tempJoined;
    // Check if odJoined is empty
    if (!odJoined.noTeam()) {
        // check for aliasing
        if (&odJoined != &odOne && &odJoined != &odTwo)
        odJoined.releaseCricketer("", ""); // clear
    }
    // if odJoined is empty -> nodes stores in empty tempJoined team
// at this point
        // odJoined is either empty
        // it is equal to odOne or odTwo, in which case tempJoined is a copy for appending the missing values
    
    // Iterate over odOne and add cricketers to odJoined
    for (int i = 0; i < odOne.cricketerCount(); i++) {
        std::string firstName, lastName;
        CricketType value;
        odOne.checkTeamForCricketer(i, firstName, lastName, value);
        // Check if the full name is present in odTwo
        bool foundInTwo = odTwo.rosteredOnCricketTeam(firstName, lastName);
        if (foundInTwo) {
            // If the full name is present in both teams, check if the values are the same
            CricketType valueTwo;
            odTwo.searchForCricketer(firstName, lastName, valueTwo);
            if (value != valueTwo) // if found and not equal
                result = false;
            else                    // if found and equal
                tempJoined.addCricketer(firstName, lastName, value);
        }
        // if not found
        else
            tempJoined.addCricketer(firstName, lastName, value);
    }

    // Iterate over odTwo and add cricketers to odJoined
    for (int i = 0; i < odTwo.cricketerCount(); i++) {
        std::string firstName, lastName;
        CricketType value;
        odTwo.checkTeamForCricketer(i, firstName, lastName, value);
        // Check if the full name is already present in odJoined
        bool foundInJoined = tempJoined.rosteredOnCricketTeam(firstName, lastName);
        bool foundInOne = odOne.rosteredOnCricketTeam(firstName, lastName);
        // check if it is not in odJoined and not in odOne
        if (!foundInJoined && !foundInOne) {
            // If the full name is not already present, add the cricketer to odJoined
            tempJoined.addCricketer(firstName, lastName, value);
        }
    }
    // Swap the contents of the temp with odJoined
    odJoined = tempJoined;
    return result;
}

void checkCricketers (const std::string& fsearch, const std::string& lsearch, const CricketTeam& odOne, CricketTeam& odResult) {
    // ensure odResult is empty; otherwise clear it
    // check for aliasing
    if (!odResult.noTeam() && &odResult != &odOne) {
        odResult.releaseCricketer("", "");
    }
    CricketTeam tempResult;
    for (int i = 0; i < odOne.cricketerCount(); i++) {
        string firstName;
        string lastName;
        CricketType value;
        // Get information
        odOne.checkTeamForCricketer(i, firstName, lastName, value);
        bool matchFirstName = (fsearch == "*" || firstName == fsearch);
        bool matchLastName = (lsearch == "*" || lastName == lsearch);
          // Repeat for each player on the team
          if (matchFirstName && matchLastName) {
              tempResult.addCricketer(firstName, lastName, value);
          }
      }
      // Swap the contents of the temp with odResult
    odResult = tempResult;
  }
 






