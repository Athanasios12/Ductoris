#include "Person.h"
#include "armyfactory.h"
#include <algorithm>
#include <cstdlib>
#include <QQmlProperty>

Person::Person()
{

}

Person::Person(const Person &other):
    m_type(other.m_type),
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
        m_type = other.m_type,
        m_stats = other.m_stats;
        m_exp = other.m_exp;
        m_level = other.m_level;
        m_armor = other.m_armor;
        m_weapons = other.m_weapons;
    }
    return *this;
}

Person::Person(Person &&other):
    m_type(other.m_type),
    m_stats(other.m_stats),
    m_exp(other.m_exp),
    m_level(other.m_level)
{
    other.m_stats = Stats();
    other.m_exp = 0;
    other.m_level = 0;
    m_armor = std::move(other.m_armor);
    m_weapons = std::move(other.m_weapons);
}

Person &Person::operator=(Person &&other)
{
    if(this != &other)
    {
        m_type = other.m_type,
        m_stats = other.m_stats;
        m_exp = other.m_exp;
        m_level = other.m_level;
        other.m_stats = Stats();
        other.m_exp = 0;
        other.m_level = 0;
        m_armor = std::move(other.m_armor);
        m_weapons = std::move(other.m_weapons);
    }
    return *this;
}

Person::~Person()
{

}

bool Person::setUiItem(std::unique_ptr<QQuickItem> &uiItem)
{
    bool uiSet = false;
    if(uiItem)
    {
        m_uiItem = std::move(uiItem);
        //connect to signals and slots of ui component
        connect(this, SIGNAL(updatePersonMovementData(QVariant, QVariant, QVariant, QVariant)), m_uiItem.get(), SLOT(onUpdateMovementData(QVariant, QVariant, QVariant, QVariant)));
        connect(this, SIGNAL(updatePersonMovementStats(QVariant,QVariant)), m_uiItem.get(), SLOT(onUpdateMovementStats(QVariant, QVariant)));
        connect(m_uiItem.get(), SIGNAL(positionChanged(int, int, int)), this, SLOT(onPositionChanged(int,int,int)));
        //get uiItem properities values
        m_uiItemWidth = QQmlProperty::read(m_uiItem.get(), "width").toUInt();
        m_uiItemHeight = QQmlProperty::read(m_uiItem.get(), "height").toUInt();
        m_rotation = QQmlProperty::read(m_uiItem.get(), "rotation").toInt();
        m_position.setX(QQmlProperty::read(m_uiItem.get(), "x").toInt());
        m_position.setY(QQmlProperty::read(m_uiItem.get(), "y").toInt());
        m_connectedToUi = true;
        uiSet = true;
    }
    return uiSet;
}

void Person::setPosition(uint32_t x, uint32_t y)
{
    m_position.setX(x);
    m_position.setY(y);
}

QPoint Person::getPosition() const
{
    return m_position;
}

quint16 Person::getWidth() const
{
    return m_uiItemWidth;
}

quint16 Person::getHeight() const
{
    return m_uiItemHeight;
}

DuctorisTypes::ArmyType Person::getPersonArmyType() const
{
    return m_type;
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

void Person::changeArmor(Armor &armor)
{
    m_armor = std::move(armor);
}

void Person::addWeapon(const Weapon &weapon)
{
    m_weapons.push_back(weapon);
}

void Person::move(int newX, int newY)
{
    if(m_uiItem && m_connectedToUi)
    {
        auto x = m_position.x();
        auto y = m_position.y();

        //get this  - perosn width and height from the property of ui qmlItem
        newX = newX - static_cast<int>(m_uiItemWidth / 2);
        newY = newY - static_cast<int>(m_uiItemHeight / 2);

        //replace with person member items
        auto timeX = static_cast<int>(abs(newX - x) * m_stats.m_speed);
        auto timeY = static_cast<int>(abs(newY - y) * m_stats.m_speed);
        int time = std::max(timeX, timeY);
        //rotation calculation
        auto X_g = static_cast<double>(newX); //X in global coordinates
        auto Y_g = static_cast<double>(newY); //Y in global coordinates
        //transform to person coordinate system orientation
        //custom rotation angle calculation for coordinates system with
        // o------> x
        // '
        // '
        // v y
        auto Phi = static_cast<double>(m_rotation);
        auto X_p = ((X_g * cos((Phi / 180) * M_PI)) + (Y_g * sin((Phi / 180) * M_PI))); //x in local coordinates
        auto Y_p = ((-X_g * sin((Phi / 180) * M_PI)) + (Y_g * cos((Phi / 180) * M_PI))); //y in local coordinates
        int rotationAngle = 0;
        if(X_p >= 0)
        {
            rotationAngle = static_cast<int>(180 - ((atan2(X_p, Y_p) * 180) / M_PI));
        }
        else
        {
            rotationAngle = static_cast<int>(-180 - ((atan2(X_p, Y_p) * 180) / M_PI));
        }
        //signal data change
        updatePersonMovementData(newX, newY, time, rotationAngle);
    }
}

void Person::attack()
{

}

void Person::setActiveEnemy(std::shared_ptr<Person> &enemyUnit)
{

}

void Person::onPositionChanged(int x, int y, int rotation)
{
    m_position.setX(x - static_cast<int>(m_uiItemWidth / 2));
    m_position.setY(y - static_cast<int>(m_uiItemHeight / 2));
    m_rotation = rotation;
}
