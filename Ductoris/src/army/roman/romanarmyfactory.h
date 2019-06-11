#ifndef ROMANARMYFACTORY_H
#define ROMANARMYFACTORY_H
#include "armyfactory.h"

class RomanArmyFactory : public ArmyFactory
{
public:
    RomanArmyFactory();
    ~RomanArmyFactory();

    Commander* createLeader();
    Soldier* createSoldier(Soldier::SoldierType soldierType);
    Officer* createOfficer();
};

#endif // ROMANARMYFACTORY_H
