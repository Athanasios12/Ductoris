#include "RomanArmyFactoryTests.h"
#include "romanarmyfactory.h"
#include "armyfactory.h"
#include "commander.h"

void RomanArmyFactoryTests::TestCase_CreateRomanLeader()
{
    std::unique_ptr<AbstractArmyFactory> romanFactory(new RomanArmyFactory);
    std::unique_ptr<Commander> romanLeader(romanFactory->createLeader());
    QVERIFY(romanLeader);
}

void RomanArmyFactoryTests::TestCase_CreateRomanOfficer()
{
    std::unique_ptr<AbstractArmyFactory> romanFactory(new RomanArmyFactory);
    std::unique_ptr<Commander> romanOfficer(romanFactory->createOfficer());
    QVERIFY(romanOfficer);
}

void RomanArmyFactoryTests::TestCase_CreateRomanSwordsman()
{
    std::unique_ptr<AbstractArmyFactory> romanFactory(new RomanArmyFactory);
    std::unique_ptr<Soldier> Swordsman(romanFactory->createSoldier(Soldier::SoldierType::Swordsman));
    QVERIFY(Swordsman);
}

void RomanArmyFactoryTests::TestCase_CreateRomanSpearman()
{
    std::unique_ptr<AbstractArmyFactory> romanFactory(new RomanArmyFactory);
    std::unique_ptr<Soldier> Spearman(romanFactory->createSoldier(Soldier::SoldierType::Spearman));
    QVERIFY(Spearman);
}

void RomanArmyFactoryTests::TestCase_CreateRomanArcher()
{
    std::unique_ptr<AbstractArmyFactory> romanFactory(new RomanArmyFactory);
    std::unique_ptr<Soldier> Archer(romanFactory->createSoldier(Soldier::SoldierType::Archer));
    QVERIFY(Archer);
}

void RomanArmyFactoryTests::TestCase_CreateRomanSkirmisher()
{
    std::unique_ptr<AbstractArmyFactory> romanFactory(new RomanArmyFactory);
    std::unique_ptr<Soldier> Skirmisher(romanFactory->createSoldier(Soldier::SoldierType::Skirmisher));
    QVERIFY(Skirmisher);
}

void RomanArmyFactoryTests::TestCase_CreateRomanHorseman()
{
    std::unique_ptr<AbstractArmyFactory> romanFactory(new RomanArmyFactory);
    std::unique_ptr<Soldier> Horseman(romanFactory->createSoldier(Soldier::SoldierType::Horseman));
    QVERIFY(Horseman);
}

