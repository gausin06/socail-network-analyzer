#include "D:/DSA Projects/Social Network/include/User.h"

User::User()
{
    id = 0;
    age = 0;
}

User::User(int id,
           const std::string& name,
           int age,
           const std::string& city)
{
    this->id = id;
    this->name = name;
    this->age = age;
    this->city = city;
}