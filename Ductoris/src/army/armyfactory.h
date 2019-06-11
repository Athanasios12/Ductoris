#ifndef ARMYFACTORY_H
#define ARMYFACTORY_H
#include "Soldier.h"
#include "commander.h"
#include "officer.h"

class ArmyFactory
{
public:
    ArmyFactory();
    virtual ~ArmyFactory();

    virtual Commander* createLeader() = 0;
    virtual Soldier* createSoldier(Soldier::SoldierType soldierType) = 0;
    virtual Officer* createOfficer() = 0;
};

#endif // ARMYFACTORY_H
