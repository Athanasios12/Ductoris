#ifndef COMMANDER_H
#define COMMANDER_H
#include "Person.h"
#include <QObject>
#include <memory>
#include "Soldier.h"
#include "skilltree.h"

class Commander : public Person
{
    enum CommanderType
    {
        Roman,
        Macedon,
        Gallic
    };
public:
    Commander();
    virtual ~Commander();

    void addExp(uint16_t exp);
    void changeArmor(Armor armor);
    void addWeapon(Weapon weapon);

    bool addSoldier(Soldier *soldier); //add reference to new soldier in army
protected:
    CommanderType m_cmdType;
    uint16_t m_soldierLimit;
    std::vector<Person*> m_army;
};

#endif // COMMANDER_H
