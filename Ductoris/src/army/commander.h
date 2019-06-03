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
    Commander(Commander &&other);
    Commander &operator=(Commander &&other);

    virtual bool addSoldier(Soldier *soldier); //add reference to new soldier in army
private:
    Commander(const Commander &other) = delete;
    Commander &operator=(const Commander &other) = delete;
protected:
    uint16_t m_soldierLimit;
    std::vector<Person*> m_army;
};

#endif // COMMANDER_H
