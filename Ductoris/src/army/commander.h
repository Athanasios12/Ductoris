#ifndef COMMANDER_H
#define COMMANDER_H
#include "Person.h"
#include <QObject>
#include <memory>
#include "Soldier.h"
#include "skilltree.h"

class Commander : public Person
{
public:
    Commander();
    virtual ~Commander();
    Commander(const Commander &other);
    Commander &operator=(const Commander &other);
    Commander(Commander &&other);
    Commander &operator=(Commander &&other);

    virtual bool addSoldier(std::shared_ptr<Soldier> &soldier); //add reference to new soldier in army
private:

protected:
    uint16_t m_soldierLimit;
    std::vector<std::weak_ptr<Person>> m_army;
};

#endif // COMMANDER_H
