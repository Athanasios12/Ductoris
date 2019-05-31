#include "Person.h"
#include "abstractarmyfactory.h"

Person::Person()
{

}

Person::Person(const Person &other):
    m_stats(other.m_stats),
    m_exp(other.m_exp),
    m_level(other.m_level),
    m_maxLevel(other.m_maxLevel),
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
        m_maxLevel = other.m_maxLevel;
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
