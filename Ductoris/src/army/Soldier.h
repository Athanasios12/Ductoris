#ifndef SOLDIER_H
#define SOLDIER_H
#include "Person.h"

class Soldier : public Person
{
public:
    enum SoldierType
    {
        Swordsman,
        Archer,
        Skirmisher,
        Spearman,
        Horseman
    };
    Soldier();
    virtual ~Soldier();
};

#endif // SOLDIER_H
