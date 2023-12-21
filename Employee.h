#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

class Employee {
public:
    std::string name;
    std::string position;
    int age;

    Employee(const std::string& n, const std::string& pos, int a) : name(n), position(pos), age(a) {}
};

std::ostream& operator<<(std::ostream &os, const Employee &e)
{
	os << e.name << ", " << e.position << ", " << e.age;
	return os;
}



#endif // EMPLOYEE_H
