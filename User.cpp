#include "User.h"
#include <iostream>

using namespace std;

User::User(int id, string name, int age, string location)
{
    this->id = id;
    this->name = name;
    this->age = age;
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

void User::display() const
{
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Location: " << location << endl;

    cout << "Interests: ";
    for (int i = 0; i < interests.size(); i++)
    {
        string interest = interests[i];
        cout << interest << " ";
    }
    cout << endl;
}
