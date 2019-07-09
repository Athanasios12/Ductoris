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
    if(other.m_uiItem)
    {
        m_uiItem.reset(new QQuickItem);
        //add coping manually properties of others uiWidget later on - sprite size , frame count and so on and
    }
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
    if(other.m_uiItem)
    {
        m_uiItem = std::move(other.m_uiItem);
    }
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
        if(other.m_uiItem)
        {
            m_uiItem.reset(new QQuickItem);
        }
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
        if(other.m_uiItem)
        {
            m_uiItem = std::move(other.m_uiItem);
        }
    }
    return *this;
}

Weapon::~Weapon()
{

}

bool Weapon::setUiItem(std::unique_ptr<QQuickItem> &uiItem)
{
    if(uiItem)
    {
        m_uiItem = std::move(uiItem);
    }
}

bool Weapon::checkIfEnemyInWeaponRange(const QQuickItem *enemyUiItem) const
{
    if(m_uiItem && enemyUiItem)
    {
        uint16_t weaponWidth = static_cast<uint16_t>(m_uiItem->width());
        uint16_t weaponHeight = static_cast<uint16_t>(m_uiItem->height());

        for(int x_weapon = 0; x_weapon < weaponWidth; x_weapon++)
        {
            for(int y_weapon = 0; y_weapon < weaponHeight; y_weapon++)
            {
                auto weaponPosInEnemyCoords = m_uiItem->mapToItem(enemyUiItem, QPoint{x_weapon, y_weapon}).toPoint();
                if(enemyUiItem->contains(weaponPosInEnemyCoords))
                {
                    return true;
                }
            }
        }

    }
    return false;
}
