#include "commander.h"
#include <utility>

Commander::Commander()
{

}

Commander::~Commander()
{

}

Commander::Commander(const Commander &other):
    Person(other),
    m_soldierLimit(other.m_soldierLimit),
    m_army(other.m_army)
{

}

Commander& Commander::operator=(const Commander &other)
{
    if (this != &other)
    {
        Person::operator =(other);
        m_soldierLimit = other.m_soldierLimit;
        m_army = other.m_army;
    }
    return *this;
}

Commander::Commander(Commander &&other):
    Person(std::forward<Commander&&>(other)),
    m_soldierLimit(other.m_soldierLimit)
{
    other.m_soldierLimit = 0;
    m_army = std::move(other.m_army);
}

Commander& Commander::operator=(Commander &&other)
{
    if (this != &other)
    {
        Person::operator =(std::forward<Commander&&>(other));
        m_soldierLimit = other.m_soldierLimit;
        other.m_soldierLimit = 0;
        m_army = std::move(other.m_army);
    }
    return *this;
}

bool Commander::addSoldier(std::shared_ptr<Soldier> &soldier)
{
    bool added = false;
    if (soldier)
    {
        if (m_type == soldier->getPersonArmyType())
        {
            if (m_army.size() < m_soldierLimit)
            {
                m_army.push_back(soldier);
                added = true;
            }
        }
    }
    return added;
}
