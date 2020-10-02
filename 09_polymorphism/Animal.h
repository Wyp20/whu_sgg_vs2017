#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <string>
#include <iostream>

class Animal
{
public:
    std::string _name;

public:
    virtual void bark()
    {
        std::cout << "Which animal?" << std::endl;
    }

    //virtual void bark() = 0;

    virtual ~Animal()
    {
        std::cout << "Animal::~Animal()" << std::endl;
    }
};

#endif
