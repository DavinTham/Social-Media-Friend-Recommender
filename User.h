#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User {
private:
    int id;
    string name;
    int age;
    vector<string> interests;
    string location;

public:
    // constructor
    User(int id, string name, int age, string location);

    // getters
    int getID() const;
    string getName() const;
    int getAge() const;
    string getLocation() const;
    vector<string> getInterests() const;

    // set interests
    void addInterest(string interest);

    // display user info
    void display() const;
};

#endif // USER_H