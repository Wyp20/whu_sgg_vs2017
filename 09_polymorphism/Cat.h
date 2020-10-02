#ifndef CAT_H_
#define CAT_H_

#include "Animal.h"
#include <iostream>

class Cat : public Animal
{
public:
    virtual void bark()
    {
        std::cout << _name << "miao?" << std::endl;
    }

    ~Cat()
    {
        std::cout << "Cat::~Cat()" << std::endl;
    }
};


#endif // !CAT_H_
