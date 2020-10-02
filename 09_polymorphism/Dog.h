#ifndef DOG_H_
#define DOG_H_

#include "Animal.h"
#include <iostream>

class Dog : public Animal
{
public:
    virtual void bark()
    {
        std::cout << _name << "wang wang?" << std::endl;
    }

    virtual ~Dog()
    {
        std::cout << "Dog::~Dog()" << std::endl;
    }
};

#endif
