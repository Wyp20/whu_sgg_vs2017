#ifndef STUDENT_H_
#define STUDENt_H_

#include "Human.h"

class Student : public Human
{
public:
    std::string _code;
    std::string _school;

public:
    Student(const std::string &name,
        int age,
        bool gender,
        const std::string &birthPlace) : Human(name, age, gender, birthPlace)
    {
        std::cout << "Student::Student()" << std::endl;
    }

    ~Student() { std::cout << "Student::~Student()" << std::endl; }

    void study() 
    { 
        std::cout << "Student::study() ------- start" << std::endl; 
        std::cout << "I'm " << _name << ", I can get _humanProtected: " << _humanProtected << std::endl;
        std::cout << "Student::study() ------- end" << std::endl;

        //std::cout << _humanPrivate << std::endl;
    }
};


#endif // !STUDENT_H_
