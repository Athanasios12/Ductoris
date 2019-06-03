#ifndef ABSTRACTARMYFACTORY_H
#define ABSTRACTARMYFACTORY_H
#include "Soldier.h"
#include "commander.h"
#include "officer.h"

class AbstractArmyFactory
{
public:
    AbstractArmyFactory();
    virtual ~AbstractArmyFactory();

    virtual Commander* createLeader() = 0;
    virtual Soldier* createSoldier(Soldier::SoldierType soldierType) = 0;
    virtual Officer* createOfficer() = 0;
};

#endif // ABSTRACTARMYFACTORY_H
