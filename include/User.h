#ifndef USER_H
#define USER_H

#include <string>

struct User
{
    int id;
    std::string name;
    int age;
    std::string city;

    User();
    User(int id,
         const std::string& name,
         int age,
         const std::string& city);
};

#endif