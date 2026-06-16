#include "User.h"
#include <iostream>

using namespace std;

// empty user
User::User()
{
    this->id = -1;
    this->age = 0;
}

User::User(int id, string name, int age, string school, string major, string location)
{
    this->id = id;
    this->name = name;
    this->age = age;
    this->school = school;
    this->major = major;
    this->location = location;
}

int User::getID() const
{
    return id;
}

string User::getName() const
{
    return name;
}

int User::getAge() const
{
    return age;
}

string User::getSchool() const
{
    return school;
}

string User::getMajor() const
{
    return major;
}

string User::getLocation() const
{
    return location;
}

vector<string> User::getInterests() const
{
    return interests;
}

void User::addInterest(string interest)
{
    interests.push_back(interest);
}

// print the profile
void User::display() const
{
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "School: " << school << endl;
    cout << "Major: " << major << endl;
    cout << "Location: " << location << endl;

    cout << "Interests: ";
    for (int i = 0; i < (int)interests.size(); i++)
    {
        string interest = interests[i];
        cout << interest << " ";
    }
    cout << endl;
}
