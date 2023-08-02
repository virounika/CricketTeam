//  CricketTeam.h

#ifndef CricketTeam_h
#define CricketTeam_h
#include <string>

typedef int CricketType; // This can change to other types

class CricketTeam
{
public:
    CricketTeam();
    ~CricketTeam();
    CricketTeam(const CricketTeam& other);
    const CricketTeam& operator=(const CricketTeam& other);
    bool noTeam() const;
    int cricketerCount() const;
    bool addCricketer(const std::string& firstName, const std::string& lastName, const CricketType& value);
    bool substituteCricketer(const std::string& firstName, const std::string& lastName, const CricketType & value);
    bool addOrSubstitute(const std::string& firstName, const std::string& lastName, const CricketType& value);
    bool releaseCricketer(const std::string& firstName, const std::string& lastName);
    bool rosteredOnCricketTeam(const std::string& firstName, const std::string& lastName) const;
    bool searchForCricketer(const std::string& firstName, const std::string& lastName, CricketType& value) const;
    bool checkTeamForCricketer(int i, std::string& firstName, std::string& lastName, CricketType& value) const;
    void tradeCricketTeams(CricketTeam& other);
   
private:
    struct Node
    {
        std::string firstName;
        std::string lastName;
        CricketType value;
        Node* prev;
        Node* next;
        Node(): firstName(""), lastName(""), prev(nullptr), next(nullptr) {}
    };
    
    // will be used by the CricketTeam class
    Node* head;
    Node* tail;
    int count;
};

bool mergeCricketers(const CricketTeam & odOne, const CricketTeam & odTwo, CricketTeam & odJoined);
void checkCricketers(const std::string& fsearch, const std::string& lsearch, const CricketTeam& odOne, CricketTeam& odResult);

#endif /* CricketTeam_h */
