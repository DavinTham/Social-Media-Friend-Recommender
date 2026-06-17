#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User
{
private:
    int id;
    string name;
    int age;
    string school;
    string major;
    string location;
    vector<string> interests;

public:
    // needed so users can be stored in a map
    User();
    User(int id, string name, int age, string school, string major, string location);

    // getters
    int getID() const;
    string getName() const;
    int getAge() const;
    string getSchool() const;
    string getMajor() const;
    string getLocation() const;
    vector<string> getInterests() const;

    void addInterest(string interest);
    void display() const;
};

#endif