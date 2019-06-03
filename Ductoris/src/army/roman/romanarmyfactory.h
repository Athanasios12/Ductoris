#ifndef ROMANARMYFACTORY_H
#define ROMANARMYFACTORY_H
#include "abstractarmyfactory.h"

class RomanArmyFactory : public AbstractArmyFactory
{
public:
    RomanArmyFactory();
    ~RomanArmyFactory();

    Commander* createLeader();
    Soldier* createSoldier(Soldier::SoldierType soldierType);
    Officer* createOfficer();
};

#endif // ROMANARMYFACTORY_H
