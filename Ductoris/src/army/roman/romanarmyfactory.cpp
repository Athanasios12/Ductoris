#include "romanarmyfactory.h"
#include "rLeader.h"
#include "rofficer.h"
#include "soldier.h"
#include "rspearman.h"
#include "rarcher.h"
#include "rskirmisher.h"
#include "rhorseman.h"
#include "rswordsman.h"

RomanArmyFactory::RomanArmyFactory()
{

}

RomanArmyFactory::~RomanArmyFactory()
{

}

Commander* RomanArmyFactory::createLeader()
{
    return new RLeader;
}

Soldier* RomanArmyFactory::createSoldier(Soldier::SoldierType soldierType)
{
    Soldier *soldier = nullptr;
    switch(soldierType)
    {
    case Soldier::SoldierType::Swordsman:
        soldier = new RSwordsman;
        break;
    case  Soldier::SoldierType::Spearman:
        soldier = new RSpearman;
        break;
    case Soldier::SoldierType::Archer:
        soldier = new RArcher;
        break;
    case Soldier::SoldierType::Skirmisher:
        soldier = new RSkirmisher;
        break;
    case Soldier::SoldierType::Horseman:
        soldier = new RHorseman;
        break;
    default:
        break;
    }
    return soldier;
}

Officer* RomanArmyFactory::createOfficer()
{
    return new ROfficer;
}
