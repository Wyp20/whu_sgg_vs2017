#include "Animal.h"
#include "Cat.h"
#include "Dog.h"

int main(void)
{
    Animal animal, a2;

    animal.bark();

    Cat cat;

    cat.bark();

    Animal *p = new Dog;
    p->bark();
    delete p;


    return 0;
}