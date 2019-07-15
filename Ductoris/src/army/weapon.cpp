#include "weapon.h"
#include <iostream>
#include <stdio.h>

Weapon::Weapon()
{

}

Weapon::Weapon(uint8_t level, uint16_t attackBonus, uint16_t defenceBonus, uint16_t staminaDrain, uint16_t speed):
    m_level(level),
    m_attackBonus(attackBonus),
    m_defenceBonus(defenceBonus),
    m_staminaDrain(staminaDrain),
    m_speed(speed)
{

}

Weapon::Weapon(const Weapon &other):
    m_level(other.m_level),
    m_attackBonus(other.m_attackBonus),
    m_defenceBonus(other.m_defenceBonus),
    m_staminaDrain(other.m_staminaDrain),
    m_speed(other.m_speed)
{
}

Weapon::Weapon(Weapon &&other):
    m_level(other.m_level),
    m_attackBonus(other.m_attackBonus),
    m_defenceBonus(other.m_defenceBonus),
    m_staminaDrain(other.m_staminaDrain),
    m_speed(other.m_speed)
{
    other.m_level = 0;
    other.m_attackBonus = 0;
    other.m_defenceBonus = 0;
    other.m_staminaDrain = 0;
    other.m_speed = 0;
}

Weapon& Weapon::operator=(const Weapon &other)
{
    if(this != &other)
    {
        m_level = other.m_level;
        m_attackBonus = other.m_attackBonus;
        m_defenceBonus = other.m_defenceBonus;
        m_staminaDrain = other.m_staminaDrain;
        m_speed = other.m_speed;
    }
    return *this;
}

Weapon& Weapon::operator=(Weapon &&other)
{
    if(this != &other)
    {
        other.m_level = 0;
        other.m_attackBonus = 0;
        other.m_defenceBonus = 0;
        other.m_staminaDrain = 0;
        other.m_speed = 0;
    }
    return *this;
}

Weapon::~Weapon()
{

}

void Weapon::setSize(const QSize &size)
{
    m_weaponSize = size;
}

QSize Weapon::getSize() const
{
    return m_weaponSize;
}

QString Weapon::getSpriteImgSource() const
{
    return m_spriteImgSource;
}

uint16_t Weapon::getLevelCap() const
{
    return m_level;
}

uint16_t Weapon::getAttackBonus() const
{
    return m_attackBonus;
}

uint16_t Weapon::getDefenceBonus() const
{
    return m_defenceBonus;
}

uint16_t Weapon::getStaminaDrain() const
{
    return m_staminaDrain;
}

uint16_t Weapon::getSpeed() const
{
    return m_speed;
}

bool Weapon::isRanged() const
{
    return m_isRanged;
}
