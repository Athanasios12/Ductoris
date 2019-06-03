#include "commander.h"

Commander::Commander()
{

}

Commander::~Commander()
{

}

Commander::Commander(Commander &&other):
    Person(other),
    m_soldierLimit(other.m_soldierLimit)
{
    other.m_soldierLimit = 0;
    m_army = std::move(other.m_army);
}

Commander &Commander::operator=(Commander &&other)
{
    if(this != &other)
    {
        Person::operator =(other);
        m_soldierLimit = other.m_soldierLimit;
        other.m_soldierLimit = 0;
        m_army = std::move(other.m_army);
    }
    return *this;
}

bool Commander::addSoldier(Soldier *soldier)
{
    bool added = false;
    if(soldier)
    {
        if(m_skillTree->getArmyType() == soldier->m_skillTree->getArmyType())
        {
            if(m_army.size() < m_soldierLimit)
            {
                m_army.push_back(soldier);
                added = true;
            }
        }
    }
    return added;
}
