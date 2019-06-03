#include "Person.h"
#include "abstractarmyfactory.h"

Person::Person()
{

}

Person::Person(const Person &other):
    m_stats(other.m_stats),
    m_exp(other.m_exp),
    m_level(other.m_level),
    m_armor(other.m_armor),
    m_weapons(other.m_weapons)
{
    //add m_skillTree copying - skillTree factory or skill tree builder
}

Person &Person::operator=(const Person &other)
{
    if(this != &other)
    {
        m_stats = other.m_stats;
        m_exp = other.m_exp;
        m_level = other.m_level;
        m_armor = other.m_armor;
        m_weapons = other.m_weapons;
    }
    return *this;
}

Person::~Person()
{

}

void Person::setPosition(uint32_t x, uint32_t y)
{
    m_position = std::make_pair(x, y);
}

std::pair<uint32_t, uint32_t> Person::getPosition() const
{
    return m_position;
}

bool Person::addExp(uint16_t exp)
{
    bool levelUp = false;
    //later on add perk check for
    if(m_skillTree)
    {
        if(m_level < m_skillTree->getMaxLevel())
        {
            m_exp += exp;
            if(m_skillTree->checkIfThresholdReached(m_exp))
            {
                m_stats.addBonus(m_skillTree->getLevelBonus(++m_level));
                levelUp = true;
            }
        }
    }
    return levelUp;
}

void Person::changeArmor(Armor &&armor)
{
    m_armor = armor;
}

void Person::addWeapon(const Weapon &weapon)
{
    m_weapons.push_back(weapon);
}
