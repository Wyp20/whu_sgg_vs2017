#ifndef HUMAN_H_
#define HUMAN_H_

#include <string>
#include <iostream>

class Human
{
public:
    std::string _name;
    int _age;
    int _gender;
    std::string _birthPlace;

protected:
    int _humanProtected;

private:
    int _humanPrivate;

public:
    Human(const std::string &name,
        int age,
        int gender,
        const std::string &birthPlace) : _name(name), _age(age), _gender(gender), _birthPlace(birthPlace), _humanProtected(0), _humanPrivate(0)
    {
        std::cout << "Human::Human()" << std::endl;
    }

    ~Human() { std::cout << "Human::~Human()" << std::endl; }

    void sleep() { std::cout << "Human::sleep()" << std::endl; }
    void eat() { std::cout << "Human::eat()" << std::endl; }
};


#endif
